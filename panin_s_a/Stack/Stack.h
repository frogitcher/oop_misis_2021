#pragma once
#include <initializer_list>
#include <stdexcept>

template<class T>
class Stack {
    struct Node
    {
        T value;
        Node* next;
    };
public:
    Stack() = default;
    Stack(const Stack <T>& rhs);
    Stack(Stack<T>&& rhs);
    Stack(const std::initializer_list<T>& list);
    ~Stack();
    void Push(const T& value);
    void Pop();
    T& Get() const;
    bool Empty() const;
    std::size_t Size() const;
    void Swap(Stack <T> & rhs);
    void Merge(Stack<T>& rhs);
    void Clear();
    Stack<T>& operator=(const Stack<T>& rhs);
    bool operator==(const Stack<T>& rhs) const;
    bool operator!=(const Stack<T>& rhs) const;
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t size = 0;
};



template <typename T>
Stack<T>::Stack(const Stack <T>& rhs)
{
    *this = rhs;
}

template <typename T>
Stack<T>::Stack(Stack <T>&& rhs)
{
    head = rhs.head;
    tail = rhs.tail;
    size = rhs.size;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.size = 0;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& list)
{
    for (T item : list)
    {
        Push(item);
    }
}

template <typename T>
Stack<T>::~Stack()
{
    Clear();
}

template <typename T>
void Stack<T>::Push(const T& value)
{
    head = new Node{value, head};
    if (tail == nullptr)
    {
        tail = head;
    }
    ++size;
}

template <typename T>
void Stack<T>::Pop()
{
    if (size == 0)
    {
        throw std::length_error("trying pop from empty stack");
    }
    Node* next_head = head -> next;
    delete head;
    head = next_head;
    --size;
    if (size == 0)
    {
        tail = nullptr;
    }
}

template <typename T>
T& Stack<T>::Get() const
{
    return head -> value;
}

template <typename T>
bool Stack<T>::Empty() const
{
    return size == 0;
}

template <typename T>
std::size_t Stack<T>::Size() const
{
    return size;
}

template <typename T>
void Stack<T>::Swap(Stack<T>& rhs)
{
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    std::swap(size, rhs.size);
}

template <typename T>
void Stack<T>::Merge(Stack<T>& rhs) // putting rhs on self stack
{
    rhs.tail->next = head;
    head = rhs.head;
    size = size + rhs.size;
    rhs.size = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template <typename T>
void Stack<T>::Clear()
{
    while (size)
    {
        Pop();
    }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
    Clear();
    Node* prev_pointer = nullptr;
    head = new Node{rhs.head -> value, rhs.head -> next};
    tail = head;
    prev_pointer = head;
    ++size;
    for (Node* pointer = rhs.head -> next; pointer != nullptr; pointer = pointer->next)
    {
        prev_pointer -> next = pointer;
        tail = new Node{pointer -> value, pointer -> next};
        prev_pointer = tail;
        ++size;
    }
    return *this;
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& rhs) const
{
    if (size != rhs.size)
    {
        return false;
    }
    Node* pointer1 = head;
    Node* pointer2 = rhs.head;
    for (; pointer1 != nullptr; pointer1 = pointer1->next, pointer2 = pointer2->next)
    {
        if (pointer1->value != pointer2->value)
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack<T>& rhs) const
{
    return !(*this == rhs);
}


