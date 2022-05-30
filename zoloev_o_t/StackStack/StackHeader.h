#pragma once

#include <iostream>
#include <initializer_list>
//#include <functional>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Stack {

public:

    struct Node{
            T value = 0;
            Node* next;
    };

    Stack() = default;
    Stack(const Stack& st);
    Stack(const std::initializer_list<T>& list);
    Stack(Stack<T>&& st);
    ~Stack();

    void Push(const T& value);
    //создать место под новый Node
    void Pop();
    T& GetHead() const;
    inline bool Empty() const {
        return Stack_size == 0;
    }
	inline size_t Size() const {
		return Stack_size;
	}
	void Swap(Stack& some_stack);
	void Merge(Stack& some_stack);
	void Clear();

    bool operator==(const Stack<T>& some_stack) const;
    bool operator!= (const Stack<T>& some_stack) const;
    void operator= (const Stack<T>& some_stack);

private:
    //элемент стека
    //указатель на хвост и вершину стека
    Node* head = nullptr;
    Node* tail = nullptr;
    //размер стека
    size_t Stack_size = 0;
};


template<typename T>
Stack<T>::Stack(const Stack& st) {
    *this = st;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& some_stack){
    head = some_stack.head;
    tail = some_stack.tail;
    Stack_size = some_stack.Stack_size;

    some_stack.head = nullptr;
    some_stack.tail = nullptr;
    some_stack.Stack_size = 0;
}

template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
    bool flag = true;
    for (auto i : list){
        head = new Node({i, head});
        if (flag){
            tail = head;
            flag = false;
        }
        ++Stack_size;
    }
}

template<typename T>
Stack<T>::~Stack() {
         Clear();
}

template<typename T>
void Stack<T>::Push(const T& value) {

    head = new Node{value, head};
    if (Stack_size == 0){
        tail = head;
    }

    Stack_size++;
}

template<typename T>
T& Stack<T>::GetHead() const {
    if (head == nullptr) {
        throw std::length_error("Stack is empty!");
    }

    return head->value;
}

template<typename T>
void Stack<T>::Pop() {
    if(Empty()){
        throw std::length_error("Stack is empty!");
    }

    Node* new_head = head->next;
    delete head;
    head = new_head;
    Stack_size--;
    if(Stack_size == 0) {
        tail = nullptr;
    }
}

template<typename T>
void Stack<T>::Clear() {
    while(Stack_size > 0) {
        Pop();
    }
}


template<typename T>
void Stack<T>::Swap(Stack<T>& some_stack){
    std::swap(head, some_stack.head);
    std::swap(tail, some_stack.tail);
    std::swap(Stack_size, some_stack.Stack_size);
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& some_stack) const {
    if (Stack_size != some_stack.Stack_size){
        return false;
    }

    Node* head_copy = head;
    Node* stackhead_copy = some_stack.head;
    while (head_copy != nullptr && head_copy->value == stackhead_copy->value){
        head_copy = head_copy -> next;
        stackhead_copy = stackhead_copy -> next;
    }
    return (head_copy == nullptr);
}


template<typename T>
bool Stack<T>::operator!= (const Stack<T>& some_stack) const {
    return !(*this == some_stack);
}

template <typename T>
void Stack<T>::Merge(Stack<T>& some_stack) {
    if(!some_stack.Empty()) {
        tail->next = some_stack.head;
        tail = some_stack.tail;
        Stack_size += some_stack.Stack_size;
        some_stack.head = nullptr;
        some_stack.tail = nullptr;
        some_stack.Stack_size = 0;
    }
}

template <typename T>
void Stack<T>::operator= (const Stack<T>& some_stack) {
    Clear();
    if (some_stack.Stack_size != 0) {
        head = new Node{ some_stack.head -> value, nullptr };
        Node* cur = some_stack.head -> next;
        Node* prev = head;
        while (cur != nullptr) {
            prev -> next = new Node{ cur -> value, nullptr };
            prev = prev -> next;
            cur = cur -> next;
        }
        tail = prev;
    }
    Stack_size = some_stack.Stack_size;
}









