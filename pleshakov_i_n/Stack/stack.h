#include <initializer_list>
#include <algorithm>
#include <stdexcept>

#pragma once

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

template<typename T>
Stack<T>::Stack(const Stack<T>& st){
    *this = st;
}

template <typename T>
Stack<T>::Stack(Stack<T>&& st){
    head = st.head;
    tail = st.tail;
    size = st.size;

    st.head = nullptr;
    st.tail = nullptr;
    st.size = 0;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& List){
    bool flag = true;
    for (auto i : List){
        head = new Node({i, head});
        if (flag){
            tail = head;
            flag = false;
        }
        ++size;
    }
}

template <typename T>
Stack<T>::~Stack(){
    Clear();
}

template <typename T>
void Stack<T>::Push(const T& value){

    head = new Node{value, head};
    if (size == 0) tail = head;
    ++size;
}

template <typename T>
void Stack<T>::Pop(){
    if (size == 0) {
        throw std::invalid_argument("Stack is empty");
    }

    Node* new_head = head->next;
    delete head;
    head = new_head;
    --size;
}

template <typename T>
T& Stack<T>::Get() const{
    if (size == 0){
        throw std::invalid_argument("Stack is empty");
    }else{
        return head->value;
    }
}

template <typename T>
size_t Stack<T>::Size() const{
    return size;
}

template <typename T>
void Stack<T>::Clear(){
    while(size > 0){
        Pop();
    }
}

template <typename T>
bool Stack<T>::Empty() const{
    if (size) return false;
    return true;
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& st) const{
    if (size != st.size) return false;

    Node* head_copy = head;
    Node* sthead_copy = st.head;
    while (head_copy != nullptr && head_copy->value == sthead_copy->value){
        head_copy = head_copy -> next;
        sthead_copy = sthead_copy -> next;
    }
    return (head_copy == nullptr);
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& st) const{
    return !(*this == st);
}

template<typename T>
void Stack<T>::Swap(Stack<T>& st){
    std::swap(head, st.head);
    std::swap(tail, st.tail);
    std::swap(size, st.size);
}

template <typename T>
void Stack<T>::operator=(const Stack<T>& st){
    Clear();
    if (st.size != 0) {
        head = new Node{ st.head -> value, nullptr };
        Node* cur = st.head -> next;
        Node* prev = head;
        while (cur != nullptr) {
            prev -> next = new Node{ cur -> value, nullptr };
            prev = prev -> next;
            cur = cur -> next;
        }
        tail = prev;
    }
    size = st.size;
}

template <typename T>
void Stack<T>::operator=(Stack<T>&& st){
    Swap(st);
    st.Clear();
}

template <typename T>
void Stack<T>::Merge(Stack<T>& st){
    tail->next = st.head;
    tail = st.tail;
    size += st.size;
    st.Clear();
}


