#include "stack.h"
#include <stdexcept>
#include <initializer_list>

using namespace std;
template<typename T>
Stack<T>::~Stack()
{
    Clear();
}
template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& list)
{
   for (T item : list) {
		(*this).Push(item);
	}
}
template <typename T>
Stack<T>::Stack(Stack<T>&& other)
{
    head = other.head;
    tail = other.tail;
    size = other.size;
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}
template <typename T>
Stack<T>::Stack(const Stack<T>& other)
{
    *this=other;
}

template <typename T>
void Stack<T>::Push(const T value)
{
    head = new Node {value, head};
    if (size == 0) {
        tail = head;
    }
    size++;
}
template <typename T>
void Stack<T>::Pop()
{
    if (size==0)
    {
        throw std::length_error("stack is already empty");
    }
    else
    {
        Node* _head = head -> next;
        delete head;
        head = _head;
        --size;
    }
}
template <typename T>
bool Stack<T>::Empty() const
{
    return (size==0);
}
template <typename T>
size_t Stack<T>::Size() const
{
    return size;
}
template <typename T>
void Stack<T>::Swap(Stack<T>& other)
{
    std::swap(size,other.size);
    std::swap(head,other.head);
    std::swap(tail,other.tail);

}
template <typename T>
void Stack<T>::Merge(Stack<T>& other)
{
    tail->next = other.head;
	tail = other.tail;
	size = size + other.Size();
	other.Clear();
}
template <typename T>
void Stack<T>::Clear()
{
    while (size!=0)
    {
        Pop();
    }
}
template <typename T>
T& Stack<T>::Get() const
{
    if (size==0)
    {
        throw std::length_error("Stack is empty");
    }
    return head->value;
}
template <typename T>
bool Stack<T>::operator==(const Stack<T>& other) const
{
    if (size!=other.size)
    {
        return false;
    }
    Stack<T> a = *this;
    Stack<T> b = other;
    while (size!=0)
    {
        if (a.Get()!=b.Get())
        {
            return false;
        }
        a.Pop();
        b.Pop();
    }
    return true;
}
template <typename T>
bool Stack<T>::operator!=(const Stack<T>& other) const
{
	return !(*this == other);
}
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    Node* a = head;
    Node* b = other.head;
    int add = other.size - size;
    for (int i = 0; i < add; i++)
    {
        Push(b->value);
        b = b->next;
    }
}
