#pragma once

#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <stddef.h>

template<typename T>
class Stack {
public:
    struct Node {
        Node* next = nullptr;
        T value;
        explicit Node(const Node* from);
    };

    Stack() = default;
    Stack(const Stack<T>& st);
    Stack(Stack<T>&& st) noexcept;
    Stack(const std::initializer_list<T>& list);
    ~Stack();
    void Push(const T& value);
    void Pop();
    T& Get() const;
    bool Empty() const;
    size_t Size() const;
    void Swap(Stack<T>& st);
    void Merge(Stack<T>& st);
    void Clear();

    Stack<T>& operator=(const Stack<T>& oth);
    Stack<T>& operator=(const std::initializer_list<T>& list);
    bool operator==(const Stack<T>& oth) const;
    bool operator==(const std::initializer_list<T>& list) const;
    bool operator!=(const Stack<T>& oth) const;
    bool operator!=(const std::initializer_list<T>& list) const;
    Stack<T>& operator+=(Stack<T>& oth);
    Stack<T> operator+(Stack<T>& oth);
private:
    void CopyFromOth(const Stack<T>& oth);
    void InitFromInitializerList(const std::initializer_list<T>& list);
private:
    size_t size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;
};

template<typename T>
Stack<T>::Node::Node(Node* _next, T _value) : next(_next), value(_value)
{
}

template<typename T>
Stack<T>::Stack(const Stack<T>& st)
{
    if (this == &st) {
        return;
    }

    CopyFromOth(st);
}

template<typename T>
Stack<T>::Stack(Stack<T>&& st) noexcept
{
    if (this == &st){
        return;
    }

    head = st.head;
    tail = st.tail;
    size = st.size;
    
    st.head = nullptr;
    st.tail = nullptr;
    st.size = 0;
}

template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
    InitFromInitializerList(list);
}

template<typename T>
Stack<T>::~Stack()
{
    Clear();
}

template<typename T>
void Stack<T>::Push(const T& value) {
    if (size == 0) {
        head = new Node{ nullptr, value };
        tail = head;
    }
    else {
        head = new Node{ head, value };
    }
    ++size;
}

template<typename T>
void Stack<T>::Pop() {
    if (size == 0) {
        throw std::out_of_range("Cannot pop element from an empty stack");
    }
    else if (size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        --size;
        return;
    }
    Node* newHead = head->next;
    delete head;
    head = newHead;
    --size;
}

template<typename T>
T& Stack<T>::Get() const {
    if (size == 0) {
        throw std::out_of_range("Cannot get element from an empty stack");
    }
    return head->value;
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
void Stack<T>::Swap(Stack<T>& st) {
    std::swap(head, st.head);
    std::swap(tail, st.tail);
    std::swap(size, st.size);
}

template<typename T>
void Stack<T>::Merge(Stack<T>& st) {
    if (st.Empty()) {
        return;
    }

    tail->next = st.head;
    tail = st.tail;
    st.head = nullptr;
    st.tail = nullptr;
    size += st.size;
    st.size = 0;
}

template<typename T>
void Stack<T>::Clear() {
    while (size != 0) {
        Pop();
    }
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& oth) {
    if (this == &oth) {
        return *this;
    }
    Clear();
    if (oth.size == 0) {
        return *this;
    }
    CopyFromOth(oth);
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const std::initializer_list<T>& list) {
    Clear();
    InitFromInitializerList(list);
    return *this;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& oth) const
{
    if (size != oth.size) {
        return false;
    }
    Node* curNode = head;
    Node* curNodeOth = oth.head;
    while (curNode != nullptr) {
        if (curNode->value != curNodeOth->value) {
            return false;
        }
        curNode = curNode->next;
        curNodeOth = curNodeOth->next;
    }
    return true;
}

template<typename T>
bool Stack<T>::operator==(const std::initializer_list<T>& list) const
{
    if (size != list.size()) {
        return false;
    }
    if (size == 0 && list.size() == 0) {
        return true;
    }

    Node* curNode = head;
    for (const T& elem : list) {
        if (curNode->value != elem) {
            return false;
        }
        curNode = curNode->next;
    }
    return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& oth) const
{
    return !(*this == oth);
}

template<typename T>
bool Stack<T>::operator!=(const std::initializer_list<T>& list) const
{
    return !(*this == list);
}

template<typename T>
void Stack<T>::CopyFromOth(const Stack<T>& oth)
{
    if (oth.size == 0) {
        size = 0;
        return;
    }
    else if(oth.size == 1){
        Node* node = oth.head;
        head = node;
        tail = node;
        size = 1;
        return;
    }
    Node* curNodeOth = oth.head;
    Node* curNode = head;
    while (curNodeOth != nullptr) {
        curNode = new Node{nullptr, oth.head->value};
        curNodeOth = curNodeOth->next;
        curNode = curNode->next;
    }
    tail = curNode;
    size = oth.size;
}

template<typename T>
void Stack<T>::InitFromInitializerList(const std::initializer_list<T>& list) {
    if (empty(list)) {
        head = nullptr;
        tail = nullptr;
        return;
    }

    for(const T& elem : list){
        Push(elem);
    }
    size = list.size();
}

template<typename T>
Stack<T>& Stack<T>::operator+=(Stack<T>& oth) {
    Merge(oth);
    return *this;
}

template<typename T>
Stack<T> Stack<T>::operator+(Stack<T>& oth) {
    return Stack<T>(*this) += oth;
}
