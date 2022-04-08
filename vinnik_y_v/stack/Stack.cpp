#include "Stack.h"

template<typename T>
inline Stack<T>::Node::Node(const Node * from)
{
    value = from->value;
    if (from->next == nullptr) {
        return;
    }
    next = new Node(from->next);
}

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
        tail->next = new Node{ nullptr, value };
        tail = tail->next;
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
    Node* curNode = head;
    while (curNode->next != tail) {
        curNode = curNode->next;
    }
    delete tail;
    tail = curNode;
    --size;
}

template<typename T>
T& Stack<T>::Get() const {
    if (size == 0) {
        throw std::out_of_range("Cannot get element from an empty stack");
    }
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

    Node* curNode = st.head;
    while (curNode != nullptr) {
        Push(curNode->value);
        curNode = curNode->next;
    }
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
    Clear();
    if (oth.size == 0) {
        return;
    }
    Node* curNode = oth.head;
    while (curNode != nullptr) {
        Push(curNode->value);
        curNode = curNode->next;
    }
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