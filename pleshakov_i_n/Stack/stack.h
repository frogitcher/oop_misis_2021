#pragma once
#include <initializer_list>


template <typename T>
class Stack{

public:

    struct Node{
        T value;
        Node* next;
    };

    Stack() = default;
    Stack(const Stack<T>& st);
    Stack(Stack<T>&& st);
    Stack(const std::initializer_list<T>& List);
    ~Stack();

    void Push(const T& value);
    void Pop();
    size_t Size() const;
    T& Get() const;
    bool Empty() const;
    bool operator==(const Stack<T>& st) const;
    bool operator!=(const Stack<T>& st) const;
    void Swap(Stack<T>& st);
    void operator=(const Stack<T>& st);
    void operator=(Stack<T>&& st);

    void Merge(Stack<T>& st);
    void Clear();

private:

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;

};
