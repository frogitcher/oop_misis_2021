#pragma once

#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <stddef.h>

template<typename T>
class Stack {
public:
    struct Node {
        Node* next = nullptr;
        T value;
        explicit Node(const Node* from);
        Node(Node* _next, T _value);
    };

    Stack() = default;
    Stack(const Stack<T>& st);
    Stack(Stack<T>&& st) noexcept;
    Stack(const std::initializer_list<T>& list);
    ~Stack();
    void Push(const T& value);
    void Pop();
    T& Get() const;
    bool Empty() const;
    size_t Size() const;
    void Swap(Stack<T>& st);
    void Merge(Stack<T>& st);
    void Clear();

    Stack<T>& operator=(const Stack<T>& oth);
    Stack<T>& operator=(const std::initializer_list<T>& list);
    bool operator==(const Stack<T>& oth) const;
    bool operator==(const std::initializer_list<T>& list) const;
    bool operator!=(const Stack<T>& oth) const;
    bool operator!=(const std::initializer_list<T>& list) const;
    Stack<T>& operator+=(Stack<T>& oth);
    Stack<T> operator+(Stack<T>& oth);
private:
    void CopyFromOth(const Stack<T>& oth);
    void InitFromInitializerList(const std::initializer_list<T>& list);
private:
    size_t size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;
};