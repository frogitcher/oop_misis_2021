#include <iostream>
#include "Stack.h"
#include <initializer_list>

template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
    for (T l : list) {
        push(l);
    }
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other) {
    *this = other;
}

template<typename T>
Stack<T>::Stack(Stack<T>&& other) {
    size = other.size;
    head = other.head;
    tail = other.tail;
    other.size = 0;
    other.head = nullptr;
    other.tail = nullptr;
}

template<typename T>
Stack<T>::~Stack() {
    this->clear();
}

template<typename T>
void Stack<T>::push(const T value) {
    head = new Node(value, head);
    if (tail == nullptr) {
        tail = head;
    }
    size++;
}

template<typename T>
void Stack<T>::pop() {
    if (size == 0) {
        throw std::logic_error("Stack is empty");
    }
    Node* next = head->next;
    delete head; 
    head = next;
    size--;
}

template<typename T>
T& Stack<T>::get_front() const {
    return head->value;
}

template<typename T>
T& Stack<T>::get_back() const {
    return tail->value;
}

template<typename T>
bool Stack<T>::Empty() const {
    return size == 0;
}

template<typename T>
size_t Stack<T>::Size() const {
    return size;
}

template<typename T>
void Stack<T>::merge(Stack<T>& other) {
    if (size == 0) {
        *this = other;
    }
    else {
        tail->next = other.head;
        tail = other.tail;
        size += other.size;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
}

template<typename T>
void Stack<T>::swap(Stack<T>& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}

template<typename T>
void Stack<T>::clear() {
    while (!this->Empty()) {
        pop();
    }
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& other) const {
    if (size != other.size) {
        return false;
    }
    else {
        Node* _this = head;
        Node* _other = other.head;
        while (_this != nullptr) {
            if(_this->value != _other->value) return false;
            _this = _this->next;
            _other = _other->next;
        }
    }
    return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& other) const {
    return !(* this == other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if(other.size != 0){
        clear();
        head = new Node(other.head->value, nullptr);
        Node* current = other.head->next;
        Node* previous = head;
        while (current != nullptr)
        {
            previous->next = new Node(current->value, nullptr);
            previous = previous->next;
            current = current->next;
        }
        tail = previous;
        size = other.size;
    }
    return *this;
}

template<typename T>
Stack<T>::Node::Node(T _value, Node* _next) {
    value = _value;
    next = _next;
}
