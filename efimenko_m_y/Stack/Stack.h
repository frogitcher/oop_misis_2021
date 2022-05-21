#pragma once
#include <initializer_list>
#include <cstddef>
#include <utility>
#include <stdexcept>

template<typename T>
class Stack {
	struct Node {
		T value;
		Node* next;
	};

public:
	Stack() = default;
	~Stack() {
		while (!(Empty())) {
			Pop();
		}
	}
	Stack(const Stack<T>& other) {
		*this = other;
	}
	Stack(Stack<T>&& other) {
		head = other.head;
		tail = other.tail;
		size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	Stack(const std::initializer_list<T>& list) {
		for (auto& el : list) {
			Push((T)el);
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
		if (Empty()) {
			throw std::invalid_argument("Invalid size");
		}
		Node* cur = head;
		head = cur->next;
		delete cur;
		if (head == nullptr) {
			tail == nullptr;
		}
		--size;
	}
	T& Get() const {
		if (head == nullptr) {
			throw std::length_error("Stack is empty!");
		}
		return head->value;
	}
	void Swap(Stack<T>& st) {
		std::swap(head, st.head);
		std::swap(tail, st.tail);
		std::swap(size, st.size);
	}
	void Merge(Stack<T>& st) {
		if (!st.Empty()) {
			st.tail->next = head;
			head = st.head;
			size += st.size;
		}
		st.head = nullptr;
		st.tail = nullptr;
		st.size = 0;
	}

	inline bool Empty() const {
		return size == 0;
	}
	inline size_t Size() const {
		return size;
	}



	Stack<T>& operator=(const Stack<T>& st) {
		while (!(Empty())) {
			Pop();
		}
		if (st.size != 0) {
			head = new Node{ st.head->value, nullptr };
			Node* now = st.head->next;
			Node* then = head;
			while (now != nullptr) {
				then->next = new Node{ now->value, nullptr };
				then = then->next;
				now = now->next;
			}
			tail = then;
		}
		size = st.size;
		return *this;
	}
	Stack<T>& operator=(Stack<T>&& st) {
		return *this = Stack<T>(st);
	}

	bool operator==(const Stack<T>& st) const {
		if (size != st.size) {
			return false;
		}
		Node* first = head;
		Node* second = st.head;
		while (head != nullptr) {
			if (first != second) { return false; }
			first = head->next;
			second = st.head->next;

		}
		return true;
	}
	inline bool operator!=(const Stack<T>& st) const {
		return !(*this == st);
	}

	inline friend Node* GetHead(const Stack<T>& st) {
		return st.head;
	}
	inline friend Node* GetTail(const Stack<T>& st) {
		return st.tail;
	}

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

};

template <typename T>
inline typename Stack<T>::Node* GetHead(const Stack<T>& st);

template <typename T>
inline typename Stack<T>::Node* GetTail(const Stack<T>& st);
