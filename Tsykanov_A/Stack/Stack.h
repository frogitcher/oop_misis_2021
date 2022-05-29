#pragma once
#include <initializer_list>
#include <cstddef>
#include <utility>
#include <stdexcept>
template<typename T>
class Stack
{
public:
    struct Node
    {
        T value;
        Node* next;
    };
    // конструкторы
    Stack();
    Stack(const Stack<T>& st);
    Stack(Stack<T>&& st);
    Stack(const std::initializer_list<T>& list);
    ~Stack();
    //методы
    void Push(const T& value);
    void Pop();
    T& Get() const;
    bool Empty() const;
    std::size_t Size() const;
    void Swap(Stack<T>& st);
    void Clean_up();
    void Merge(Stack<T>& st);
    Stack<T> operator=(const Stack<T>& other);
    bool operator==(const Stack<T>& st) const;
    bool operator!=(const Stack<T>& st) const;
    inline friend Node* Get_Head(const Stack<T>& st) {
        return st.head;
    }
    inline friend Node* Get_Tail(const Stack<T>& st) {
        return st.tail;
    }
    
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t size = 0;
};
template <typename T>
inline typename Stack<T>::Node* Get_Head(const Stack<T>& st);

template <typename T>
inline typename Stack<T>::Node* Get_Tail(const Stack<T>& st);

template <typename T>
Stack<T>::Stack(const Stack<T>& st){
    *this = st;
};
template <typename T>
Stack<T>::Stack(Stack<T>&& st){
    head = st.head;
    tail = st.tail;
    size = st.size;
    st.head = nullptr;
    st.tail = nullptr;
    st.size = 0;
};
template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& list){
    for (auto& element : list){
        Push((T)element);
    }
    size = list.size();
};
template <typename T>
Stack<T>::Stack() = default;
template <typename T>
Stack<T>::~Stack(){
    Clean_up();
};
// методы
template <typename T>
void Stack<T>::Push(const T& value){
    head = new Node{value, head};
    if(tail == nullptr){
        tail = head;
    }
    ++size;
};
template <typename T>
void Stack<T>::Pop(){
    if (Empty()) {
            throw std::length_error("Stack is empty!");
    }
    Node* upper = head;
    head = upper->next;
    delete upper;
    if (head == nullptr){
        tail = nullptr;
    }
    --size;
};
template <typename T>
T& Stack<T>::Get() const{
    if (Empty()) {
            throw std::length_error("Stack is empty!");
    }
    return head->value;
};
template <typename T>
bool Stack<T>::Empty() const{
    return size == 0;
};
template <typename T>
std::size_t Stack<T>::Size() const{
    return size;
};
template <typename T>
void Stack<T>::Swap(Stack<T>& st){
    std::swap(head, st.head);
    std::swap(tail, st.tail);
    std::swap(size, st.size);
};
template <typename T>
void Stack<T>::Merge(Stack<T>& st){
    tail->next = st.head;
    if (size != 0){
        tail = nullptr;
    }else{
        tail = st.tail;
    }
    size += st.size;
    st.size = 0;
    st.head = nullptr;
    st.tail = nullptr;
};
template <typename T>
void Stack<T>::Clean_up(){
    while(tail != nullptr){
        Pop();
    }
};
// Опрераторы
template <typename T>
Stack<T> Stack<T>::operator=(const Stack<T>& other) {
Clean_up();
if (other.Size() != 0) {
    head = new Node{ other.head->value, nullptr };
    Node* one = other.head->next;
    Node* two = head;
    while (one != nullptr) {
        two->next = new Node{ one->value, nullptr };
        two = two->next;
        one = one->next;
    }
    tail = two;
}
size = other.Size();
return *this;
};
template <typename T>
bool Stack<T>::operator==(const Stack<T>& st) const{
    if (st.size != size){
        return false;
    }
    else{
        Node *first = head;
        Node *second = st.head;
        while(first != nullptr){
            if (first->value != second->value){
                return false;
            }
            first = first->next;
            second = second->next;
        }
        return true;
    }
};
template <typename T>
bool Stack<T>::operator!=(const Stack<T>& st) const{
    return !(*this == st);
}