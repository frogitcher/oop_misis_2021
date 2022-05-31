#pragma once
#include <initializer_list>
#include <stdexcept>
#include <cstdint>

template <typename T>
class Stack {
public:
    struct Node
    {
        T value;
        Node* next;
    };
    Stack() = default;
    Stack(const std::initializer_list<T>& list);
    Stack(const Stack<T>& other);
    Stack(Stack<T>&& other);
    ~Stack();
    void Push(const T value);
    void Pop();
    bool Empty() const;
    size_t Size() const;
    void Swap(Stack<T>& other);
    void Merge(Stack<T>& other);
    void Clear();
    T& Get() const;
    bool operator==(const Stack<T>& other) const;
    bool operator!=(const Stack<T>& other) const;
    Stack<T>& operator=(const Stack<T>& other);

private:
    size_t size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;
};

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
        if (size==1)
        {
            tail=head;
        }
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
    if (other.Size()!=0)
    {
    tail->next = other.head;
	tail = other.tail;
	size = size + other.Size();
	other.size=0;
	other.head=nullptr;
	other.tail=nullptr;
    }
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
    Node* temp_this = head;
	Node* temp_other = other.head;
	for (size_t i = 0; i < size; ++i) {
		if ((temp_this->value) != (temp_other->value)) {
			return false;
		}
		temp_this = temp_this->next;
		temp_other = temp_other->next;
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
    Clear();
    size=other.size();
    if (other.head==nullptr)
    {
        return *this;
    }
    Node* a = new Node({other.head->value, nullptr});
	head = a;
	Node* temp = head;
	Node* other_temp = other.head->next;
	for (size_t i = 1; i < other.size; ++i) {
		a = new Node({other_temp->value, nullptr});
		temp->next = a;
		temp = temp->next;
		other_temp = other_temp->next;
	}
	tail = a;
	size=other.size;
	return *this;
}
