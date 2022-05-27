#pragma once
#include <initializer_list>

template <typename T>

class myStack {
public:
    struct Node {
        T value;
        Node* next;
    };

    myStack() = default;
    myStack(const myStack<T>& st);
    myStack(myStack<T>&& st);
    myStack(const std::initializer_list<T>& list);
    ~myStack();

    size_t getSize() const;
    T& get() const;
    bool empty() const;
    void push(const T& value);
    void pop();
    void swap(myStack<T>& st);
    void merge(myStack<T>& st);
    void clear();
    void copy(const myStack<T>& st);

    bool operator==(const myStack<T>& st) const;
    bool operator!=(const myStack<T>& st) const;
    myStack& operator=(const myStack<T>& st);
    myStack& operator=(myStack<T>&& st);
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};