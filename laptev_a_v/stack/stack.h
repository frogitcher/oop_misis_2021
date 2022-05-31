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
		for (auto el : list) {
			Push((T)el);
		}
	}
	~Stack() {
		Clear();
	}

	void Push(const T& value) {
		Set_Head(value, head);
		if (tail == nullptr) {
			tail = head;
		}
	}
	void Pop() {
		if (Empty()) {
			throw std::length_error("stack is empty!");
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
			throw std::length_error("stack is empty!");
		}
		return head->value;
	}
	inline bool Empty() const {
		return size == 0;
	}
	inline size_t Size() const {
		return size;
	}
	void Swap(Stack<T>& other) {
		std::swap(head, other.head);
		std::swap(tail, other.tail);
		std::swap(size, other.size);
	}
	void Merge(Stack<T>& other) {
		tail->next = other.head;
		tail = other.tail;
		size += other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}
	void Clear() {
		while (size > 0) {
			Pop();
		}
	}
	Stack<T>& operator=(const Stack<T>& rhs) {
		Clear();
		if (rhs.size != 0) {
			head = new Node{ rhs.head->value, nullptr };
			Node* cur = rhs.head->next;
			Node* prev = head;
			while (cur != nullptr) {
				prev->next = new Node{ cur->value, nullptr };
				prev = prev->next;
				cur = cur->next;
			}
			tail = prev;
		}
		size = rhs.size;
		return *this;
	}
	bool operator==(const Stack<T>& rhs) const {
		if (size != rhs.size) {
			return false;
		}
		Node* x = head;
		Node* y = rhs.head;
		while (x != nullptr) {
			if (x->value != y->value) {
				return false;
			}
			x = x->next;
			y = y->next;
		}
		return true;
	}
	inline bool operator!=(const Stack<T>& rhs) const {
		return !(*this == rhs);
	}

	inline friend Node* Get_Head(const Stack<T>& other) {
		return other.head;
	}
	inline friend Node* Get_Tail(const Stack<T>& other) {
		return other.tail;
	}

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void Set_Head(T value, Stack::Node* next) {
		head = new Node{ value, next };
		++size;
	}
}
