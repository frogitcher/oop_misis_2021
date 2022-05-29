#pragma once
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Stack {
	struct Node
	{
		T value;
		Node* next;
	};
public:
	Stack() = default;
	~Stack();
	Stack(const Stack<T>& st);
	Stack(Stack<T>&& st);
	Stack(const std::initializer_list<T>& list);

	void Push(const T& value);
	void Pop();
	T& Get() const;
	bool Empty() const;
	size_t Size() const;
	void swap(Stack<T>& st);
	bool operator==(const Stack<T>& st) const;
	bool operator!=(const Stack<T>& st) const;
	Stack<T>& operator=(const Stack<T>& st);
	void Merge(Stack<T>& st);
	void Clear();

private:
	size_t size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
};

template <typename T>
Stack<T>::Stack(const Stack<T>& st) {
	*this = st;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& st) {
	size = st.size;
	head = st.tail;
	tail = st.tail;

	st.Clear();
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
	size = 0;
	for (T i : list) {
		Push(i);
	}
}

template <typename T>
Stack<T>::~Stack() {
	Clear();
}

template <typename T>
size_t Stack<T>::Size() const {
	return size;
}

template <typename T>
bool Stack<T>::Empty() const {
	return size == 0;
}

template <typename T>
void Stack<T>::Pop() {
	if (Empty()) {
		throw std::domain_error("Pop on empty stack");
	}
	if (size == 1) {
		tail = nullptr;
	}
	Node* tmp = head->next;
	delete head;
	head = tmp;
	--size;
}

template <typename T>
void Stack<T>::Push(const T& value) {
	head = new Node{ value, head };
	if (tail == nullptr) {
		tail = head;
	}
	++size;
}

template <typename T>
T& Stack<T>::Get() const {
	if (Empty()) {
		throw std::domain_error("Trying to get value of an empty stack");
	}
	return head->value;
}

template <typename T>
void Stack<T>::Clear() {
	while (size != 0) {
		Pop();
	}
}

template <typename T>
void Stack<T>::swap(Stack<T>& st) {
	std::swap(head, st.head);
	std::swap(tail, st.tail);
	std::swap(size, st.size);
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& st) const {
	if (size != st.size) {
		return false;
	}
	Node* tmp_node_1 = head;
	Node* tmp_node_2 = st.head;
	for (int i = 0; i < size; ++i) {
		if ((tmp_node_1->value) != (tmp_node_2->value)) {
			return false;
		}
		tmp_node_1 = tmp_node_1->next;
		tmp_node_2 = tmp_node_2->next;
	}
	return true;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& st) {
	Clear();
	if (st.size > 0) {
		head = new Node{ st.head->value, nullptr };
		Node* tmp_1 = st.head->next;
		Node* tmp_2 = head;
		while (tmp_1 != nullptr) {
			tmp_2->next = new Node{ tmp_1->value, nullptr };
			tmp_2 = tmp_2->next;
			tmp_1 = tmp_1->next;
		}
		tail = tmp_2;
	}
	size = st.size;
	return *this;
}

template <typename T>
void Stack<T>::Merge(Stack<T>& st) {
	tail->next = st.head;
	tail = st.tail;
	size = size + st.Size();
	st.size = 0;
	st.head = nullptr;
	st.tail = nullptr;
}

template <typename T>
bool Stack<T>::operator!=(const Stack<T>& st) const {
	return !(*this == st);
}

