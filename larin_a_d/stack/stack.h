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
	Stack(const Stack<T>& st);
	Stack(Stack<T>&& st);
	Stack(const std::initializer_list<T>& list);

	void Push(const T& value);
	void Pop();
	T& Get() const;
	inline bool Empty() const {
		return size == 0;
	}
	inline size_t Size() const {
		return size;
	}
	void Swap(Stack<T>& st);
	void Merge(Stack<T>& st);
	void Clear();

	Stack<T>& operator=(const Stack<T>& st);

	bool operator==(const Stack<T>& st) const;
	inline bool operator!=(const Stack<T>& st) const {
		return !(*this == st);
	}

	inline friend Node* Get_Head(const Stack<T>& st) {
		return st.head;
	}
	inline friend Node* Get_Tail(const Stack<T>& st) {
		return st.tail;
	}
	~Stack();

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void Set_Head(T value, Node* next);
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
Stack<T>::Stack(const std::initializer_list<T>& list) {
	for (auto el : list) {
		Push((T)el);
	}
}

template<typename T>
void Stack<T>::Push(const T& value) {
	Set_Head(value, head);
	if (tail == nullptr) {
		tail = head;
	}
}

template<typename T>
void Stack<T>::Pop() {
	if (Empty()) {
		throw std::length_error("Stack empty!");
	}
	Node* cur = head;
	head = cur->next;
	delete cur;
	if (head == nullptr) {
		tail == nullptr;
	}
	size--;
}

template<typename T>
T& Stack<T>::Get() const {
	if (head == nullptr) {
		throw std::length_error("Stack empty!");
	}
	return head->value;
}

template<typename T>
void Stack<T>::Swap(Stack<T>& st) {
	std::swap(head, st.head);
	std::swap(tail, st.tail);
	std::swap(size, st.size);
}

template<typename T>
void Stack<T>::Merge(Stack<T>& st) {
	tail->next = st.head;
	tail = st.tail;
	size += st.size;
	st.head = nullptr;
	st.tail = nullptr;
	st.size = 0;
}

template<typename T>
void Stack<T>::Clear() {
	while (size > 0) {
		Pop();
	}
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& st) {
	Clear();
	if (st.size != 0) {
		head = new Node{ st.head->value, nullptr };
		Node* cur = st.head->next;
		Node* prev = head;
		while (cur != nullptr) {
			prev->next = new Node{ cur->value, nullptr };
			prev = prev->next;
			cur = cur->next;
		}
		tail = prev;
	}
	size = st.size;
	return *this;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& st) const {
	if (size != st.size) {
		return false;
	}
	Node* a = head;
	Node* b = st.head;
	while (a != nullptr) {
		if (a->value != b->value) {
			return false;
		}
		a = a->next;
		b = b->next;
	}
	return true;
}

template<typename T>
void Stack<T>::Set_Head(T value, Stack::Node* next) {
	head = new Node{ value, next };
	size++;
}

template<typename T>
Stack<T>::~Stack() {
	Clear();
}

template <typename T>
inline typename Stack<T>::Node* Get_Head(const Stack<T>& st);

template <typename T>
inline typename Stack<T>::Node* Get_Tail(const Stack<T>& st);