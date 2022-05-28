#include "stack.h"
#include <stdexcept>

template<typename T>
Stack<T>::~Stack() {
	while (!Empty()) {
		Pop();
	}
}

template<typename T>
Stack<T>::Stack(const Stack<T>& st) {
	Node* cur = st.head;
	head = cur;
	while (cur != nullptr) {
		tail = new Node(*cur);
		cur = cur->next;
	}
	size = st.size;
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
	for (auto& it : list) {
		Push(it);
	}
}

template<typename T>
void Stack<T>::Push(const T& value) {
	head = new Node{ value, head };
	if (tail == nullptr) {
		tail = head;
	}
	size++;
};

template<typename T>
void Stack<T>::Pop() {
	if (size == 0) {
		throw std::underflow_error("Stack is already empty!");
	}
	Node* temp = head->next;
	delete head;
	head = temp;
	if (head == nullptr) {
		tail = nullptr;
	}
	size--;
};

template<typename T>
T& Stack<T>::Get() const {
	if (Empty()) {
		throw std::out_of_range("Can't Get from empty Stack")
	}
	return head->value;
}

template<typename T>
bool Stack<T>::Empty() const {
	return size == 0;
}

template<typename T>
size_t Stack<T>::Size() const {
	return size;
}

template<typename T>
Stack<T>::Node* Stack<T>::GetHead() const {
	return head;
}

template<typename T>
Stack<T>::Node* Stack<T>::GetTail() const {
	return tail;
}

template<typename T>
void Stack<T>::Swap(Stack<T>& st) {
	std::swap(head, st.head);
	std::swap(tail, st.tail);
	std::swap(size, st.size);
}

template<typename T>
void Stack<T>::Merge(Stack<T>&st) {
	if (!st.Empty()) {
		st.tail->next = head;
		head = st.head;
		size += st.size;
	}
	st.head = nullptr;
	st.tail = nullptr;
	st.size = 0;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& st) const {
	if (size != st.size) return false;
	Node* cur1 = head;
	Node* cur2 = st.head;
	while (cur1 != nullptr) {
		if (cur1->value != cur2->value) return false;
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& st) const {
	return !(*this == st);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& st) {
	while (!Empty()) {
		Pop();
	}
	Node* cur = st.head;
	head = cur;
	while (cur != nullptr) {
		tail = new Node(cur);
		cur = cur.next;
	}
	size = st.size;
	return *this;
}