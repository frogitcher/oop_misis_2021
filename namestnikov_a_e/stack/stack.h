#pragma once
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Stack{
    struct Node{
        T value;
        Node* next;
    };

public:
    Stack() = default;
    ~Stack();
    Stack(const Stack<T>& st);
    Stack(Stack<T>&& st);
    Stack(const std::initializer_list<T>& list);

    void Push(const T& value);
    void Pop();
    T& Get() const;

    void Clear();

    bool Empty() const;
    std::size_t Size() const;

    void Swap(Stack<T>& st);
    void Merge(Stack<T>& st);

    bool operator==(const Stack<T>& st) const;
    bool operator!=(const Stack<T>& st) const;

    Stack<T>& operator=(const Stack<T>& st);
    Stack<T>& operator=(Stack<T>&& st);


private:
    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t size = 0;
};

template <typename T>
Stack<T>::~Stack() { while (size > 0) {Pop();}}
template <typename T>
Stack<T>::Stack(const Stack<T> &st) {*this = st;}
template <typename T>
Stack<T>::Stack(Stack<T> &&st) {
    Clear();
    head = st.head;
    tail = st.tail;
    size = st.size;
    st.head = nullptr;
    st.size = 0;
    st.tail = nullptr;
}
template <typename T>
Stack<T>::Stack(const std::initializer_list<T> &list) {for (auto i: list){ Push(i);}}

template <typename T>
void Stack<T>::Push(const T &value) {
    head = new Node{value, head};
    if (tail == nullptr)
    {
        tail = head;
    }
    size++;
}
template <typename T>
void Stack<T>::Pop() {
    if (size > 0)
    {
        Node* tmp_h = head -> next;
        delete head;
        head = tmp_h;
        size--;
        if (size == 0) {tail = nullptr;}
    } else{
        throw std::invalid_argument("You can't pop from an empty stack");
    }
}
template <typename T>
T& Stack<T>::Get() const {
    if (head == nullptr)
    {
        throw std::invalid_argument("You can't get from an empty stack");
    } else{
        return head->value;
    }
}

template<typename T>
void Stack<T>::Clear() { while (size > 0){Pop();}}

template <typename T>
bool Stack<T>::Empty() const{ return size == 0;}
template <typename T>
std::size_t Stack<T>::Size() const {return size;}

template <typename T>
void Stack<T>::Swap(Stack<T> &st) {
    std::swap(head,st.head);
    std::swap(tail,st.tail);
    std::swap(size,st.size);
}
template <typename T>
void Stack<T>::Merge(Stack<T> &st) {
    tail->next = st.head;
    tail = st.tail;
    size +=st.size;
    st.head = nullptr;
    st.tail = nullptr;
    st.size = 0;
}

template <typename T>
bool Stack<T>::operator==(const Stack<T> &st) const {
    if (size == st.size)
    {
        if (size == 0)
        {
            return true;
        }
    }
    else
    {
        return false;
    }
    if (head->value == st.head->value)
    {
        Node* tmp0 = head->next;
        Node* tmp1 = st.head->next;
        for (int i = 1; i < size; i++)
        {
            if (tmp0->value != tmp1->value)
            {
                return false;
            }
            tmp0 = tmp0->next;
            tmp1 = tmp1->next;
        }
    }
    else
    {
        return false;
    }
    return true;
}
template <typename T>
bool Stack<T>::operator!=(const Stack<T> &st) const {return !(*this == st);}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> &st) {
    Clear();
    if (st.size > 0)
    {
        head = new Node {st.head->value, nullptr};
        Node* tmp0 = st.head->next;
        Node* tmp1 = head;
        for (int i = 1; i < st.size; i++)
        {
            tmp1->next = new Node{tmp0->value, nullptr};
            tmp0 = tmp0->next;
            tmp1 = tmp1->next;
        }
        tail = tmp1;
    }
    size = st.size;
    return *this;
}
template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> &&st) {
    head = st.head;
    tail = st.tail;
    size = st.size;
    st.head = nullptr;
    st.size = nullptr;
    st.size = 0;
}