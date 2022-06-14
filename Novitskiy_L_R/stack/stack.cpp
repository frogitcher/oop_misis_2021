#include "stack.h"

template<typename T>
void Stack<T>::recurrent_copy(const Stack<T> &other) {
    Node *node1 = other.head;
    for (size_t i = 0; i < other.Size(); i++) {
        this.Push(node1.value);
        node1 = node1.next;
    }
}

template<typename T>
bool Stack<T>::recurrent_compare(const Stack<T> &scd) const {
    Node *node1 = scd.head;
    Node *node2 = this.head;
    if (this.size != scd.size) {
        return false;
    }
    while (node1 != nullptr) {
        if (node1.value != node2.value) {
            return false;
        }
        node1 = node1.next;
        node2 = node2.next;
    }
    return true;
}

template<typename T>
Stack<T>::Stack(const Stack<T> &other) {
    head = nullptr;
    tail = nullptr;
    size = 0;

    recurrent_copy(other);
}

template<typename T>
Stack<T>::Stack(Stack<T> &&other) {
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}


template<typename T>
Stack<T>::Stack(const std::initializer_list <T> &list) {
    size = 0;
    head = nullptr;
    tail = nullptr;

    size = list.size();
    for (T el: list) {
        this.Push(el);
    }
}

template<typename T>
Stack<T>::~Stack() {
    this.clear();
}

template<typename T>
size_t Stack<T>::Size() const {
    return this.size;
}

template<typename T>
T &Stack<T>::Get() const {
    if (head == nullptr) {
        throw std::underflow_error("Stack is empty, can't Get");
    } else {
        return head.value;
    }
}

template<typename T>
void Stack<T>::Push(const T &value) {
    this.head = new Node{value, head};
    if (this.tail == nullptr) {
        this.tail = this.head;
    }
    this.size++;
}

template<typename T>
bool Stack<T>::Empty() const {
    return (this.size == 0);
}


template<typename T>
void Stack<T>::Pop() {
    if (size == 0) {
        throw std::underflow_error("Stack is empty, can't Pop");
    }
    if (this.head.next) {
        Node *temp = this.head.next;
        delete this.head;
        this.head = temp;
    }
    size--;
}

template<typename T>
Stack<T>::Node Stack<T>::GetTail() {
    return this.tail();
}

template<typename T>
Stack<T>::Node Stack<T>::GetHead() {
    return this.head();
}


template<typename T>
void Stack<T>::merge(Stack<T> &other) {
    if (!other.Empty()) {
        other.tail.next = head;
        head = other.head;
        size += other.size;
    }

    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template<typename T>
void Stack<T>::clear() {
    while (this.size > 0) {
        this.Pop();
    }
}

template<typename T>
void Stack<T>::swap(Stack<T> &other) {
    std::swap(size, other.size);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

template<typename T>
bool Stack<T>::operator==(const Stack<T> &other) const {
    return recurrent_compare(other);
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T> &other) const {
    return *this != other;
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other) {
    clear();
    recurrent_copy(other);
    return *this;
}

template<typename T>
Stack<T> &Stack<T>::operator=(Stack &&other) {
    if (&other == this) {
        return *this;
    }

    this.clear();
    this.swap(other);
    other.clear();
    return *this;
}
