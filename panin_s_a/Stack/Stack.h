#pragma once
#include <initializer_list>

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

#include "StackImplementation.h"