#pragma once
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <cstddef>

template<typename T>
class Stack {

public:

	Stack() = default;

	Stack(const Stack<T>& st) {
		*this = st;
	}

	Stack(Stack<T>&& st) {
		*this = st;
		st.head = nullptr;
		st.tail = nullptr;
		st.size = 0;
	}

	Stack(const std::initializer_list<T>& List) {
		for (T value : List) {
			Push((T) value);
		}
	}

	~Stack() {
		while (!(Empty())) {
			Pop();
		}
	}

	void Push(const T& value) {
		head = new Node{ value, head };
		if (tail == nullptr) {
			tail = head;
		}
		size++;
	}

	void Pop() {
		if (size == 0) {
			throw std::length_error("Pop Error");
		}
		head = head->next;
		if (head == nullptr) {
			tail = nullptr;    //if 1-element stack
		}
		size--;
	}

	T& Get() const {
		if (size == 0) {
			throw std::length_error("Get Error");
		}
		return head->value;
	}

	bool Empty() const {
		return (size == 0);
	}

	size_t Size() const {
		return size;
	}
	
	void Swap(Stack<T>& st) {
		std::swap(head, st.head);
		std::swap(tail, st.tail);
		std::swap(size, st.size);
	}

	bool operator==(const Stack<T>& st) {
		if (size != st.size) {
			return false;
		}
		Node* x = head;
		Node* y = st.head;
		while (x != nullptr) {
			if (x->value == y->value) {
				x = x->next;
				y = y->next;
			}
			else {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Stack<T>& st) {
		return (!(*this == st));
	}

	Stack<T>& operator=(const Stack<T>& st) {
		while (head != nullptr) {
			Pop();
		}
		if (st.size > 0) {
			head = new Node{ (st.head)->value, nullptr };
			Node* x = (st.head)->next;
			Node* y = head;
			while (x != nullptr) {
				y->next = new Node{ x->value, nullptr };
				y = y->next;
				x = x->next;
			}
			tail = y;
		}
		size = st.size;
		return *this;
	}

	void Merge(Stack<T>& st) {

		if (Empty()) {
			tail = st.tail;
			head = st.head;
		}
		else {
			tail->next = st.head;
			tail = st.tail;
		}
		size += st.size;
		st.head = nullptr;
		st.tail = nullptr;
		st.size = 0;
	}

	struct Node {
		T value;
		Node* next;
	};

	Node* head = nullptr;
	Node* tail = nullptr;


private:
	size_t size = 0;
};

