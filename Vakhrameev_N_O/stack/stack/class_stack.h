#pragma once
#include <initializer_list>
#include <stdexcept>
template<typename T>
class Stack
{
public:
	struct Node
	{
		T value;
		Node* next;
	};
    Stack() = default;
    Stack(const Stack<T>& other);
	Stack(Stack<T>&& other);
	Stack(const std::initializer_list<T>& list);
	~Stack();
	void Push(const T& elem);
	void Pop();
	bool Empty() const;
	size_t Size() const;
	void Clear();
	void Swap(Stack<T>& other);
	Stack<T>& operator=(const Stack<T>& other);
	bool operator==(const Stack<T> other) const;
    bool operator!=(const Stack<T> other) const;
	void Merge(Stack<T>& other);
	T& Get() const;
private:
	size_t size = 0;
	Node* first = nullptr;
	Node* last = nullptr;
};

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
{
	*this = other;
}
template<typename T>
Stack<T>::Stack(Stack<T>&& other)
{
	first = other.first;
	last = other.last;
	size = other.size;
	other.first = nullptr;
	other.last = nullptr;
	other.size = 0;
}
template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& list)
{
	for (T elem : list)
	{
		Push(elem);
	}
}
template<typename T>
Stack<T>::~Stack()
{
	while (size > 0)
	{
		Pop();
	}
}
template<typename T>
void Stack<T>::Push(const T& elem)
{
	first = new Node{ elem,first };
	if (last == nullptr)
	{
		last = first;
	}
	size++;
}
template<typename T>
void Stack<T>::Pop()
{
	if (size == 0)
	{
		throw std::out_of_range("stack contains no attributes");
	}
	else
	{
		Node* temp = first->next;
		delete first;
		first = temp;
		if (first == nullptr)
		{
			last = first;
		}
		size--;
	}
}
template<typename T>
bool Stack<T>::Empty() const
{
	return (size == 0);
}
template<typename T>
T& Stack<T>::Get() const
{
	if (first == nullptr)
	{
		throw std::out_of_range("Size is equal to zero");
	}
	return first->value;
}
template<typename T>
size_t Stack<T>::Size() const
{
	return size;
}
template<typename T>
void Stack<T>::Clear()
{
	while (size > 0)
	{
		Pop();
	}
}
template<typename T>
void Stack<T>::Swap(Stack<T>& other)
{
	Node* temp = first;
	first = other.first;
	other.first = temp;
	temp = last;
	last = other.last;
	other.last = temp;
	size_t s = size;
	size = other.size;
	other.size = s;
}
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	while (!Empty())
	{
		Pop();
	}
	if (!(other.Empty()))
	{
		first = new Node{ other.first->value, nullptr };
		Node* current = other.first->next;
		Node* previous = first;
		while (current != nullptr)
		{
			previous->next = new Node{ current->value, nullptr };
			previous = previous->next;
			current = current->next;
		}
		last = previous;
		size = other.size;
	}
	return *this;
}
template<typename T>
bool Stack<T>::operator==(const Stack<T> other) const
{
	if (size != other.size)
	{
		return false;
	}
	Node* elem1 = first;
	Node* elem2 = other.first;
	while (elem1 != nullptr)
	{
		if (elem1->value != elem2->value)
		{
			return false;
		}
		elem1 = elem1->next;
		elem2 = elem2->next;
	}
	return true;
}
template<typename T>
bool Stack<T>::operator!=(const Stack<T> other) const
{
	return !(*this == other);
}
template<typename T>
void Stack<T>::Merge(Stack<T>& other)
{
	last->next = other.first;
	last = other.last;
	size += other.size;
	other.last = nullptr;
	other.first = nullptr;
	other.size = 0;
}
