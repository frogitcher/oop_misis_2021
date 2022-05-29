#pragma once

#include <initializer_list>
#include "stack.h"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <stddef.h>

template<typename T>
class Stack {
public:
    struct Node {
        T value;
        Node *next;
    };

    Stack() = default;

    Stack(const Stack<T> &other);

    Stack(Stack<T> &&other);

    Stack(const std::initializer_list <T> &list);

    ~Stack();

    size_t Size() const;

    T &Get() const;

    bool Empty() const;

    void Push(const T &value);

    void Pop();

    Node GetHead();

    Node GetTail();

    void clear();

    void merge(Stack<T> &other);

    void swap(Stack<T> &other);

    bool operator==(const Stack<T> &other) const;

    bool operator!=(const Stack<T> &other) const;

    Stack &operator=(const Stack<T> &other);

    Stack &operator=(Stack &&other);

private:
    void recurrent_copy(const Stack<T> &other);

    bool recurrent_compare(const Stack<T> &scd) const;

    size_t size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
};
