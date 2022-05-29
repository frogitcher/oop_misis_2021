#pragma once
#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <stdexcept>

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

template<typename T>
myStack<T>::myStack(const myStack<T>& st) {
    copy(st);
    st.head = nullptr;
    st.tail = nullptr;
    st.size = 0;
}

template <typename T>
myStack<T>::myStack(myStack<T>&& st) {
    head = st.head;
    tail = st.tail;
    size = st.size;

    st.head = nullptr;
    st.tail = nullptr;
    st.size = 0;
}

template <typename T>
myStack<T>::myStack(const std::initializer_list<T>& list) {
    for (auto& i : list) {
        push(i);
    }
}

template <typename T>
myStack<T>::~myStack() {
    clear();
}

template <typename T>
void myStack<T>::copy(const myStack<T>& st) {
    Node* n = st.head;
    for (size_t i = st.getSize() - 1; i >= 0; i--) {
        this->push(n->value);
        n = n->next;
    }
}

template <typename T>
void myStack<T>::push(const T& value) {
    head = new Node{ value, head };
    if (tail == nullptr) {
        tail = head;
    }
    size++;
}

template <typename T>
void myStack<T>::pop() {
    if (size == 0) {
        throw std::invalid_argument("Empty stack");
    }

    Node* new_head = head->next;
    delete head;
    head = new_head;
    size--;
    if (size == 0) {
        tail == nullptr
    }
}

template <typename T>
T& myStack<T>::get() const {
    if (head == nullptr) {
        throw std::invalid_argument("Empty stack");
    }
    else {
        return head->value;
    }
}

template <typename T>
size_t myStack<T>::getSize() const {
    return size;
}

template <typename T>
void myStack<T>::clear() {
    while (size > 0) {
        pop();
    }
}

template <typename T>
bool myStack<T>::empty() const {
    return size == 0;
}

template<typename T>
void myStack<T>::swap(myStack<T>& st) {
    std::swap(head, st.head);
    std::swap(tail, st.tail);
    std::swap(size, st.size);
}

template <typename T>
void myStack<T>::merge(myStack<T>& st) {
    st.tail->next = head;
    head = st.head;
    size += st.size;

    st.size = 0;
    st.head = nullptr;
    st.tail = nullptr;
}




template <typename T>
bool myStack<T>::operator==(const myStack<T>& st) const {
    if (size != st.size) {
        return false;
    }
    Node* new_head = head;
    Node* new_head_st = st.head;
    while (new_head != nullptr) {
        if (new_head->value != new_head_st->value) {
            return false;
        }
        new_head = new_head->next;
        new_head_st = new_head_st->next;
    }
    return true;
}

template<typename T>
bool myStack<T>::operator!=(const myStack<T>& st) const {
    return !(*this == st);
}

template <typename T>
myStack<T>& myStack<T>::operator=(const myStack<T>& st) {
    *this.clear();
    *this.copy(st);
    return *this;
}

template <typename T>
myStack<T>& myStack<T>::operator=(myStack<T>&& st) {
    *this.clear();
    *this.swap(st);
    return *this;
}