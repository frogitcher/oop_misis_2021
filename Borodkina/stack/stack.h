#pragma once
#include <cstdint>
#include <initializer_list>

template <typename T>
class Stack {
    struct Node {
        T value;
        Node* next;
    };
    public:
    Stack() = default;
    ~Stack();
    void  Clear();
    Stack(const Stack<T>& stack);
    Stack(Stack<T>&& stack);
    Stack(const std:: initializer_list<T>& list);
    void Pop();
    void Push(const T& value);
    T& Get() const;
    bool Empty() const;
    size_t Size() const;
    void Swap(Stack<T>& stack);
    void Merge(Stack<T>& stack);
    Stack<T>& operator=(const Stack<T>& stack);
    Stack<T>& operator=(const Stack<T>&& stack);
    bool operator==(const Stack<T>& stack) const;
    bool operator!=(const Stack<T>& stack) const;
    private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
        
};
template <typename T>
Stack<T>::~Stack()
{
    Clear();
}
template <typename T>
void Stack<T>::Clear()
{
        while (!Empty()){
        Pop();
        }
}
template <typename T>
Stack<T>::Stack(const Stack<T>& stack)
{
    Clear();
    *this=stack;
}
template <typename T>
Stack<T>::Stack(Stack<T>&& stack)
{
    head = stack.head;
    tail = stack.tail;
    size = stack.size;
    stack.head = nullptr;
    stack.tail = nullptr;
    stack.size = 0;
}
template <typename T>
Stack<T>::Stack(const std:: initializer_list<T>& list)
{
    for (auto i : list)
    {
        Push(i);
    }
}
template <typename T>
void Stack<T>::Pop()
{
    if (size > 0)
    {
        size--;
        Node* new_head = head->next;
        delete head;
        head=new_head;
        if (size == 0){ 
            tail = nullptr;
        }

    } else { throw "there are no elements in the stack";}
}
template <typename T>
void Stack<T>::Push(const T& value)
{
    head = new Node {value, head};
    if (tail == nullptr)
    {
        tail = head;
    }
    size = size + 1;
}
template <typename T>
T& Stack<T>::Get() const
{
    if (size == 0){
    throw "there are no elements in the stack";
    }
    return head->value;
}
template <typename T>
bool Stack<T>::Empty() const
{
    return size == 0;
}
template <typename T>
size_t Stack<T>::Size() const
{
    return size;
}
template <typename T>
void Stack<T>::Swap(Stack<T>& stack)
{
    std::swap(head, stack.head);
    std::swap(tail, stack.tail);
    std::swap(size, stack.size);
}
template <typename T>
void Stack<T>::Merge(Stack<T>& stack)
{
    tail->next=stack.head;
    tail = stack.tail;
    size = stack.size+size;
    stack.head = nullptr;
    stack.tail = nullptr;
    stack.size = 0;
}
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
    Clear();
    if (stack.size > 0){
        head = new Node {stack.head->value, nullptr};
        Node* a = stack.head->next;
        Node* b = head;
        for (int i = 0; i<stack.size-1; i++){
            b->next = new Node { a->value, nullptr};
            b = b->next;
            a = a->next;
        }
        tail = b;
    }
    size=stack.size;
    return *this;
}
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>&& stack){
    head = stack.head;
    tail = stack.tail;
    size = stack.size;
    stack.head = nullptr;
    stack.tail = nullptr;
    stack.size = 0;
    return *this;
}
template <typename T>
bool Stack<T>::operator==(const Stack<T>& stack) const
{
    if (stack.size == size){
        Node* a = head;
        Node* b = stack.head;
        for (int i = 0; i < size; i++){
            if (a->value != b->value) {
                return false;
            }
            a = a->next;
            b = b->next;
        }
        return true;
    } else
    {return false;}
}
template <typename T>
bool Stack<T>::operator!=(const Stack<T>& stack) const
{
    return (!(stack == *this));
}