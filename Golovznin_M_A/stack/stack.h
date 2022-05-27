#pragma once

#include <algorithm>
#include <initializer_list>
#include <cstdint>
#include <stdexcept>

template<typename T>
class Stack {

public:

    struct Node {
        T value;
        Node *next;
    };

    Stack() = default;

    Stack(const Stack<T> &rhs);

    Stack(Stack<T> &&rhs);

    Stack(const std::initializer_list<T> &List);

    ~Stack();

    void push(const T &value);

    T pop();

    int64_t getSize() const;

    T& getValue() const;

    bool empty() const;

    void swap(Stack<T> &rhs);

    void merge(Stack<T> &rhs);

    void clear();

    void operator=(const Stack<T> &rhs);

    bool operator==(const Stack<T> &rhs) const;

    bool operator!=(const Stack<T> &rhs) const;

private:

    Node *head = nullptr;
    Node *tail = nullptr;
    int64_t size = 0;

};

//конструкторы

template<typename T>
Stack<T>::Stack(const Stack<T> &rhs) {
    *this = rhs;
}

template<typename T>
Stack<T>::Stack(Stack<T> &&rhs) {
    head = rhs.head;
    tail = rhs.tail;
    size = rhs.size;

    rhs.head = nullptr;
    rhs.tail = nullptr;
    size = 0;
}

template<typename T>
Stack<T>::Stack(const std::initializer_list<T> &list) {
    for (T i: list) {
        head = new Node({i, head});
        if (empty()) {
            tail = head;
        }
        ++size;
    }
}

template<typename T>
Stack<T>::~Stack() {
    clear();
}

//методы класса

template<typename T>
void Stack<T>::push(const T &value) {
    head = new Node({value, head});
    if (empty()) tail = head;

    ++size;
}

template<typename T>
T Stack<T>::pop() {
    if (empty()) {
        throw std::invalid_argument("Stack is empty");
    }

    T value = head->value;
    Node* headNext = head->next;
    delete head;
    head = headNext;
    --size;

    return value;
}

template<typename T>
int64_t Stack<T>::getSize() const {
    return size;
}

template<typename T>
T& Stack<T>::getValue() const {
    if (empty()) throw std::invalid_argument("Stack is empty");

    return head->value;
}

template<typename T>
bool Stack<T>::empty() const {
    return size == 0;
}

template<typename T>
void Stack<T>::swap(Stack<T> &rhs) {
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    std::swap(size, rhs.size);
}

template<typename T>
void Stack<T>::merge(Stack<T> &rhs) {
    if(empty()) {
        *this = Stack(rhs);

    } else {
        tail->next = rhs.head;
        tail = rhs.tail;
        size += rhs.size;

        rhs.head = nullptr;
        rhs.tail = nullptr;
        rhs.size = 0;

    }
}

template<typename T>
void Stack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

//переопределённые операторы

template<typename T>
void Stack<T>::operator=(const Stack<T> &rhs) {
    clear();

    if (!rhs.empty()) {
        head = new Node{rhs.head->value, nullptr};
        Node *current = rhs.head->next;
        Node *prev = head;
        while (current != nullptr) {
            prev->next = new Node{current->value, nullptr};
            prev = prev->next;
            current = current->next;
        }
        tail = prev;
    }

    size = rhs.size;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T> &rhs) const {
    if (size != rhs.size) return false;

    Node *node = head;
    Node *rhsNode = rhs.head;

    while (node != nullptr) {
        if (node->value != rhsNode->value) return false;
        node = node->next;
        rhsNode = rhsNode->next;
    }

    return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T> &rhs) const {
    return !(*this == rhs);
}
