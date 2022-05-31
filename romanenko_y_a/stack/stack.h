#pragma once
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Stack {

public:
    struct Node {
        T value;
        Node* next;
    };
    Stack() = default;
    Stack(const Stack<T>& st);
    Stack(Stack<T>&& st);
    Stack(const std::initializer_list<T>& list);
    ~Stack();
    void Copy(const Stack<T>& st);
    void Clear();
    void Push(const T& value);
    void Pop();
    void Swap(Stack<T>& st);
    void Merge(Stack<T>& st);
    bool Empty() const;
    T& Get() const;
    size_t Size() const;
    Stack<T>& operator=(Stack<T>&& st);
    Stack<T>& operator=(const Stack<T>& st);

    bool operator==(const Stack<T>& st) const;
    bool operator!=(const Stack<T>& st) const;
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};

template<typename T>
Stack<T>::Stack(const Stack<T>& st){
        Copy(st);
    }
template<typename T>
Stack<T>::Stack(Stack<T>&& st) {
    size = st.size;
    head = st.head;
    tail = st.tail;
    st.size = 0;
    st.head = nullptr;
    st.tail = nullptr;
}
template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
    for (auto& v: list) {
        Push(v);
    }
}
template<typename T>
Stack<T>::~Stack(){
    Clear();
}
template<typename T>
void Stack<T>::Copy(const Stack<T>& st) {
    Clear();
    if (st.size > 0) {
        head = new Node{st.head->value, nullptr};
        Node* cur = st.head->next;
        Node* prev = head;
        while (cur != nullptr) {
            prev->next = new Node{cur->value, nullptr};
            prev = prev->next;
            cur = cur->next;
        }
        tail = prev;
        size = st.size;
    }
}
template<typename T>
void Stack<T>::Clear() {
    while (size > 0) {
        Pop();
    }
}
template<typename T>
void Stack<T>::Push(const T& value) {
    head = new Node{value, head};
    if (tail == nullptr){
        tail = head;
    }
    ++size;
}
template<typename T>
void Stack<T>::Pop() {
    if (Empty()) throw std::length_error("stack is empty");
    Node* temp = head->next;
    delete head;
    head = temp;
    if (head == nullptr) tail = nullptr;
    --size;
}
template<typename T>
void Stack<T>::Swap(Stack<T>& st) {
    std::swap(head, st.head);
    std::swap(tail, st.tail);
    std::swap(size, st.size);
}
template<typename T>
void Stack<T>::Merge(Stack<T>& st) {
    tail->next = st.head;
    tail = st.tail;
    size += st.size;
    st.size = 0;
    st.head = 0;
    st.tail = 0;
}
template<typename T>
bool Stack<T>::Empty() const {
    return size == 0;
}
template<typename T>
T& Stack<T>::Get() const {
    if (Empty()) throw std::length_error("stack is empty");
    return head->value;
}
template<typename T>
size_t Stack<T>::Size() const {
    return size;
}
template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& st){
    Clear();
    Swap(st);
    st.Clear();
    return *this;
}
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& st) {
    Copy(st);
    return *this;
}
template<typename T>
bool Stack<T>::operator==(const Stack<T>& st) const {
    if (size != st.size) {
        return false;
    }
    Node* a = head;
    Node* b = st.head;
    while (a != nullptr) {
        if (a->value != b->value) {
            return false;
        }
        a = a->next;
        b = b->next;
    }
    return true;
}
template<typename T>
bool Stack<T>::operator!=(const Stack<T>& st) const {
    return !(*this == st);
}



/*
⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆ 
⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿ 
⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀ 
⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉
*/