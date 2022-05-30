#pragma once
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Stack {
public:
	struct Node {
		T value;
		Node* next;
	};

	Stack();
	~Stack();
	Stack(const Stack<T>& other);
	Stack(Stack<T>&& other);
	Stack(const std::initializer_list<T>& list);

	void push(const T& value);
	void pop();
	void swap(Stack<T>& other);
	void merge(Stack<T>& other);
	T& get() const;

	bool empty() const;
	size_t Size() const;

	bool operator==(const Stack<T>& rhs) const;
	bool operator!=(const Stack<T>& rhs) const;

	Stack<T>& operator=(const Stack<T>& rhs) noexcept;
	Stack<T>& operator=(Stack<T>&& other);
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void New_Node(T value, Node* onhead);
};

template <typename T>
Stack<T>::Stack() = default;

template <typename T>
Stack<T>::~Stack() {
	while (size != 0) {
		pop();
	}
}

template <typename T>
Stack<T>::Stack(const Stack<T>&other) {
	*this = other;
}

template <typename T>
Stack<T>::Stack(Stack<T> && other) {
	head = other.head;
	tail = other.tail;
	size = other.size;
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>&list) {
	for (T element : list) {
		push(element);
	}
}

template <typename T>
void Stack<T>::push(const T & value) {
	New_Node(value, head);
	if (size == 1) {
		tail = head;
	}
}

template <typename T>
void Stack<T>::pop() {
	if (size == 0) {
		throw std::out_of_range("The size is equal to zero");
	}
	else {
		Node* temp = head->next;
		delete head;
		head = temp;
		if (head == nullptr) {
			tail = head;
		}
		size--;
	}
}

template <typename T>
void Stack<T>::swap(Stack<T>&other) {
	std::swap(head, other.head);
	std::swap(tail, other.tail);
	std::swap(size, other.size);
}

template <typename T>
void Stack<T>::merge(Stack<T>&other) {
	tail->next = other.head;
	tail = other.tail;
	size = size + other.size;
	other.tail = nullptr;
	other.head = nullptr;
	other.size = 0;
}

template <typename T>
T& Stack<T>::get() const {
	if (head == nullptr) {
		throw std::out_of_range("The size is equal to zero");
	}
	return head->value;
}

template <typename T>
bool Stack<T>::empty() const {
	return size == 0;
}

template <typename T>
size_t Stack<T>::Size() const {
	return size;
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>&rhs) const {
	if (size != rhs.size) {
		return false;
	}
	Node* first = head;
	Node* second = rhs.head;
	while (first != nullptr) {
		if (first->value != second->value) {
			return false;
		}
		first = first->next;
		second = second->next;
	}
	return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack<T>&rhs) const {
	return !operator==(rhs);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>&rhs) noexcept {
	if (rhs.size >= size) {
		Node* first = head;
		Node* second = rhs.head;
		int add = rhs.size - size;
		for (int i = 0; i < add; i++) {
			push(second->value);
		}
	}
	else {
		int count = size - rhs.size;
		for (int i = 0; i < count; i++) {
			pop();
		}
	}
	Node* first = head;
	Node* second = rhs.head;
	while (first != nullptr) {
		first->value = second->value;
		first = first->next;
		second = second->next;
	}
	size = rhs.size;
	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> && other) {
	head = other.head;
	tail = other.tail;
	size = other.size;
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
	return *this;
}

template <typename T>
void Stack<T>::New_Node(T value, Node* onhead) {
	head = new Node{ value, onhead };
	++size;
}
