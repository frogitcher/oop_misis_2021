#pragma once
#include <initializer_list>
#include "stack.h"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <stddef.h>
template<typename T>
class Stack {
public:
	struct Node {
		T value;
		Node* next;
	};
	Stack() = default;
	Stack(const Stack<T>& other);
	Stack(Stack<T>&& other);
	Stack(const std::initializer_list<T>& list);
	~Stack();
	size_t Size() const;
	T& Get() const;
	bool Empty() const;
	void Push(const T& value);
	void Pop();
	void clear();
	void merge(Stack<T>& other);
	void swap(Stack<T>& other);
	bool operator==(const Stack<T>& other) const;
	bool operator!=(const Stack<T>& other) const;
	Stack& operator=(const Stack<T>& other);
	Stack& operator=(Stack&& other);

private:
	void recursive_copy(const Stack<T>& other);
	bool recursive_compare(const Stack<T>& scd) const;
	size_t size = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
};

template <typename T>
void Stack<T>::recursive_copy(const Stack<T>& other)
{
	Node* node1 = other.head;
	node1->next = nullptr;
	for (size_t i = 0; i < other.Size(); i++) {
		this->Push(node1->value);
		node1 = node1->next;
	}
}
template <typename T>
bool Stack<T>::recursive_compare(const Stack<T>& scd) const
{

	Node* node1 = scd.head;
	Node* node2 = this->head;
	if (this->size != scd.size) {
		return false;
	}
	while (node1 != nullptr) {
		if (node1->value != node2->value) {
			return false;
		}
		node1 = node1->next;
		node2 = node2->next;
	}
	return true;
}
template <typename T>
Stack<T>::Stack(const Stack<T>& other) {
	*this = st;
}

template<typename T>
Stack<T>::Stack(Stack<T>&& other)
{
	head = other.head;
	tail = other.tail;
	size = other.size;
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}


template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& list)
{
	size = 0;
	head = nullptr;
	tail = nullptr;
	size = list.size();
	for (T el : list) {
		this->Push(el);
	}
}
template<typename T>
Stack<T>::~Stack()
{
	this->clear();
}
template<typename T>
size_t Stack<T>::Size() const
{
	return this->size;
}

template<typename T>
T& Stack<T>::Get() const
{
	if (head == nullptr) {
		throw std::underflow_error("Stack is empty");
	}
	else
		return head->value;
}

template<typename T>
bool Stack<T>::Empty() const
{
	return (this->size == 0);
}

template<typename T>
void Stack<T>::Push(const T& value)
{
	this->head = new Node{ value, head };
	if (this->tail == nullptr) {
		this->tail = this->head;
	}
	this->size++;
}

template<typename T>
void Stack<T>::Pop()
{
	if (size == 0) {
		throw std::underflow_error("Stack is empty");
	}
	if (this->head->next) {
		Node* temp = this->head->next;
		delete this->head;
		this->head = temp;
	}
	else {
		delete this->head;
		this->head = nullptr;
		this->tail = nullptr;
	}
	size--;
}

template<typename T>
void Stack<T>::clear()
{
	while (this->size > 0) this->Pop();
}

template<typename T>
void Stack<T>::merge(Stack<T>& other)
{
	if (!other.Empty()) {
		other.tail->next = head;
		head = other.head;
		size += other.size;
	}
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}

template<typename T>
void Stack<T>::swap(Stack<T>& other)
{
	std::swap(size, other.size);
	std::swap(head, other.head);
	std::swap(tail, other.tail);
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& other) const
{
	return recursive_compare(other);
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& other) const
{
	return !(*this == other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	clear();
	if (other.size != 0) {
		head = new Node{ other.head->value, nullptr };
		Node* node1 = other.head->next;
		Node* node0 = head;
		while (node1 != nullptr) {
			node0->next = new Node{ node1->value, nullptr};
			node0 = node0->next;
			node1 = node1->next;
		}
		tail = prev;
	}
	size = other.size;
	return *this;
}
template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other)
{
	if (&other == this) return *this;
	this->clear();
	this->swap(other);
	other.clear();
	return *this;
}
