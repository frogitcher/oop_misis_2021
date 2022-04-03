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


/*template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& list)
{

}*/
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
	return this->size == 0;
}

template<typename T>
void Stack<T>::Push(const T& value)
{
	this->head = new Node{value, head};
	if (this->tail == nullptr) {
		this->tail = this->head;
	}
	this->size++;
}

template<typename T>
void Stack<T>::Pop()
{ 
	if (size==0) {
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
	this->size += other.size;
	other.tail->next = head;
	this->head = other.head;
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
	return false;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& other) const
{
	return false;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> other)
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