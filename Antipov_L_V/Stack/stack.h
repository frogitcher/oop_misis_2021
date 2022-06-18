#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <initializer_list>
#include <memory>
#include <stdexcept>

template<class T>
class Stack {
public:
    Stack() = default;

    Stack(const Stack<T> &copy);

    Stack(Stack<T> &&copy);

    Stack(const std::initializer_list<T> &list);

    ~Stack();


    void Swap(Stack<T> &copy);

    void Merge(Stack<T> &copy);

    void Push(const T &value);

    void Pop();

    void Clear();

    bool Empty() const;

    T &Get() const;

    std::size_t Size() const;

    bool operator==(const Stack<T> &rhs) const;

    bool operator!=(const Stack<T> &rhs) const;

    Stack<T> &operator=(const Stack<T> &rhs);


private:

    struct Node {
        T data;
        Node *next;
    };

    Node *top = nullptr;
    Node *bottom = nullptr;
    std::size_t size = 0;
};

template<class T>
Stack<T>::Stack(const Stack<T> &copy) {
    *this = copy;
}

template<class T>
Stack<T>::Stack(Stack<T> &&copy) {
    size = copy.size;
    top = copy.top;
    bottom = copy.bottom;

    copy.size = 0;
    copy.top = nullptr;
    copy.bottom = nullptr;
}

template<class T>
Stack<T>::Stack(const std::initializer_list<T> &list) {
    for (T element: list) {
        Push(element);
    }
}

template<class T>
Stack<T>::~Stack() {
    Clear();
}

template<class T>
void Stack<T>::Clear() {
    while (!Empty()) Pop();
}


template<class T>
void Stack<T>::Swap(Stack<T> &copy) {
    std::swap(top, copy.top);
    std::swap(bottom, copy.bottom);
    std::swap(size, copy.size);
}

template<class T>
void Stack<T>::Merge(Stack<T> &copy) {
    size += copy.size;
    copy.bottom->next = top;
    top = copy.top;

    copy.size = 0;
    copy.top = nullptr;
    copy.bottom = nullptr;
}

template<class T>
void Stack<T>::Push(const T &value) {
    top = new Node{value, top};
    if (bottom == nullptr) {
        bottom = top;
    }

    size++;
}


template<class T>
bool Stack<T>::Empty() const {
    return size == 0;
}

template<class T>
void Stack<T>::Pop() {
    if (Empty()) {
        throw std::length_error("Stack is empty.");
    }

    Node *del_top = top->next;
    delete top;
    top = del_top;

    if (--size == 0) bottom = nullptr;
}

template<class T>
T &Stack<T>::Get() const {
    if (Empty()) {
        throw std::length_error("Stack is empty.");
    }
    return top->data;
}

template<class T>
std::size_t Stack<T>::Size() const {
    return size;
}

/*
 * Operators
 * */
template<class T>
bool Stack<T>::operator==(const Stack<T> &rhs) const {
    if (Size() != rhs.Size()) return false;

    for (Node *lhs_temp = top, *rhs_temp = rhs.top;
         lhs_temp != nullptr;
         lhs_temp = lhs_temp->next, rhs_temp = rhs_temp->next) {
        if (lhs_temp->data != rhs_temp->data) return false;
    }

    return true;
}

template<class T>
bool Stack<T>::operator!=(const Stack<T> &rhs) const {
    return !(*this == rhs);
}

template<class T>
Stack<T> &Stack<T>::operator=(const Stack<T> &rhs) {
    Clear();

    if (!rhs.Empty()) {
        top = new Node{rhs.top->data, nullptr};
        for (Node *lhs_temp = top, *rhs_temp = rhs.top->next;
             rhs_temp != nullptr;
             lhs_temp = lhs_temp->next, rhs_temp = rhs_temp->next) {
            lhs_temp->next = new Node{rhs_temp->data, nullptr};

            if (rhs_temp->next == nullptr) {
                bottom = lhs_temp->next;
            }
        }

        size = rhs.Size();
    }

    return *this;
}


#endif //STACK_STACK_H
