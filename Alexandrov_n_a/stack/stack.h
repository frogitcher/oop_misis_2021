#pragma once
#include <iostream>
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
    Stack(const Stack<T>& st);
    Stack(Stack<T>&& st);
    Stack(const std::initializer_list<T>& List);
    void push(const T& value);
    void pop();
    T& get() const;
    bool empty() const;
    size_t Size() const;
    void swap(Stack<T>& st);
    bool operator== (const Stack<T>& st) const;
    bool operator!= (const Stack<T>& st) const;
    void operator= (const Stack<T>& st);
    void merge(Stack<T>& st);
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};
template<typename T>
bool Stack<T>::empty() const {
    return (size == 0);
}
template<typename T>
void Stack<T>::push(const T& value) {
    head = new Node {value, head};
    if (size == 0) {
        tail = head;
    }
    size++;
}
template<typename T>
void Stack<T>::pop() {
    if (size == 0) {
        throw "Size 0";
    }
    Node* new_head = head->next;
    delete head;
    head = new_head;
    size--;
}
template<typename T>
Stack<T>::~Stack() {
    while (size != 0) {
        pop();
    }
}
template<typename T>
Stack<T>::Stack(const Stack<T>& other) {
    push(other.head->value);
    Node* head_2 = head;
    Node* other_head_2 = other.head;
    for (int i = 0; i < other.Size(); i++) {            
        other_head_2 = other_head_2->next;
        head = new Node{ other.head->value, head };
    }
    size = other.size;
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
Stack<T>::Stack(const std::initializer_list<T>& List) {
    Stack<T> time_per;
    for (auto i : List) {
        time_per.push(i);
    }
    Node* head_2 = time_per.head;
    for (int i = 0; i < List.size(); i++) {
        push(head_2->value);
        head_2 = head_2->next;
    }
    while (time_per.size != 0) {
        time_per.pop();
    }   
}
template<typename T>
T& Stack<T>::get() const {
    if (size == 0) {
        throw "size 0";
    }
    return head->value;
}
template<typename T>
size_t Stack<T>::Size() const {
    return size;
}
template<typename T>
void Stack<T>::swap(Stack<T>& other) {
    std::swap(size, other.size);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}
template<typename T>
bool Stack<T>::operator== (const Stack<T>& other) const{
    int flag = 0;
    Node* head2 = head;
    Node* other_head_2 = other.head;
    if (size == other.size) {
        flag = 1;
        for (int i = 0; i < size; i++){
            if (head->value != other.head->value) {
                flag = 2;
                break;
            }
            else {
                head2 = head2->next;
                other_head_2 = other_head_2->next;
            }
        }
    }
    if (flag == 1) {
        return true;
    }
    else {
        return false;
    }
}
template<typename T>
bool Stack<T>::operator!= (const Stack<T>& other) const {
    return !(*this == other);
}
template<typename T>
void Stack<T>::operator= (const Stack<T>& other) {
    size = other.size;
    head = other.head;
    tail = other.tail;
}
template<typename T>
void Stack<T>::merge(Stack<T>& other) {
    tail = other.tail;
    tail->next = other.head;
    size += other.size;
}