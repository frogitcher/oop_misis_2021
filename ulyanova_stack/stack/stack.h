#pragma once
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <cstddef>

template<typename T>
class Stack {

public:

	Stack() = default;
	Stack(const Stack<T>& st);
	Stack(Stack<T>&& st);
	Stack(const std::initializer_list<T>& List);
	~Stack();

	void Push(const T& value);
	void Pop();
	void Swap(Stack<T>& st);
	void Merge(Stack<T>& st);

	T& Get() const;
	bool Empty() const;
	size_t Size() const;

	bool operator==(const Stack<T>& st) const;
	bool operator!=(const Stack<T>& st) const;
	Stack<T>& operator=(const Stack<T>& st);

	struct Node {
		T value;
		Node* next;
	};

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

template<typename T>
Stack<T>::Stack(const Stack<T>& st) {
	*this = st;
}

template<typename T>
Stack<T>::Stack(Stack<T>&& st) {
	head = st.head;
	tail = st.tail;
	size = st.size;
	st.head = nullptr;
	st.tail = nullptr;
	st.size = 0;
}

template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& List) {
	for (T value : List) {
		Push(value);
	}
}

template<typename T>
Stack<T>::~Stack() {
	while (!(Empty())) {
		Pop();
	}
}

template<typename T>
void Stack<T>::Push(const T& value) {
	head = new Node{ value, head };
	if (tail == nullptr) {
		tail = head;
	}
	size++;
}

template<typename T>
void Stack<T>::Pop() {
	if (size == 0) {
		throw std::length_error("Pop Error");
	}
	Node* new_head = head->next;
	delete head;
	head = new_head;
	if (head == nullptr) {
		tail = nullptr;    //if 1-element stack
	}
	size--;
}

template<typename T>
T& Stack<T>::Get() const {
	if (size == 0) {
		throw std::length_error("Get Error");
	}
	return head->value;
}

template<typename T>
bool Stack<T>::Empty() const {
	return (size == 0);
}

template<typename T>
size_t Stack<T>::Size() const {
	return size;
}

template<typename T>
void Stack<T>::Swap(Stack<T>& st) {
	std::swap(head, st.head);
	std::swap(tail, st.tail);
	std::swap(size, st.size);
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& st) const {
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

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& st) const {
	return (!(*this == st));
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& st) {
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

template<typename T>
void Stack<T>::Merge(Stack<T>& st) {

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

template <typename T>
inline typename Stack<T>::Node* GetHead(const Stack<T>& st);

template <typename T>
inline typename Stack<T>::Node* GetTail(const Stack<T>& st);
