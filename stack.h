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
