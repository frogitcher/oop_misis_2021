#include "stack.h"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <stddef.h>
template<typename T>
void Stack<T>::recursive_copy(Node* other)
{
	if (!other) return;
	recursive_copy(other->next);
	Push(other->value);
}

template<typename T>
bool Stack<T>::recursive_compare(const Node* node1, const Node* node2) const
{
	if (node1==nullptr && node2 == nullptr) return true;
	recursive_compare(node1->next, node2->next);
	return (node1->value == node2->value);
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) {
	head = nullptr;
	tail = nullptr;
	size = 0;
	recursive_copy(other.head);
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
	Node* temp = this->head->next;
	delete this->head;
	this->head = temp;
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
	if (this->Empty()) {
		*this = other;
	}
	else {
		Stack<T> combined_stack(*this);
		combined_stack.recursive_copy(other.head);
		*this = combined_stack;
	}

}

template<typename T>
void Stack<T>::swap(Stack<T>& other)
{
	std::swap(size, other.size);
	std::swap(head, other.head);
	std::swap(tail, other.tail);
}
template<typename T>
T* Stack<T>::begin()
{
	return *head;
}

template<typename T>
T* Stack<T>::end()
{
	return *tail;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& other) const
{
	if (tail == nullptr)
		return false;
	if (size != other.size)
		return false;
	return recursive_compare(this->head,other.head);
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& other) const
{
	return !(*this==other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	if (&other == this) return *this;
	this->clear();
	head = nullptr;
	recursive_copy(other.head);
	return *this;
}
template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other)
{
	if (&other == this) return *this;
	this->clear();
	head = other.head;
	size = other.size;
	tail = other.tail;
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
	return *this;
}