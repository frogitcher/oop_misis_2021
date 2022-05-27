#pragma once
#include <initializer_list>
#include <cstdint>

template<typename T>

class Stack {
public:
    Stack() = default;
    Stack(const Stack<T>& other);
    Stack(const std::initializer_list<T>& list);
    Stack(Stack<T>&& other);
    ~Stack();

    Stack<T>& operator=(const Stack<T>& other);

    void Push(const T value);
    void Pop();

    T& Get() const;

    bool Empty() const;
    size_t Size() const;

    void Swap(Stack<T>& other);
    void Merge(Stack<T>& other);

    void Clear();

    bool operator==(const Stack<T>& other) const;
    bool operator!=(const Stack<T>& other) const;

    struct Node {
        T value;
        Node* next = nullptr;
    };

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};

template<typename T>
size_t Stack<T>::Size() const{
    return size;
}
template<typename T>
bool Stack<T>::Empty() const{
    return size == 0;
}

template<typename T>
void Stack<T>::Clear(){
    while (size > 0) {
        Pop();
    }
}
template<typename T>
Stack<T>::~Stack(){
    Clear();
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other) {
    *this = other;
}
template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& list) {
    for (auto i : list) {
        Push(i);
    }
}
template<typename T>
Stack<T>::Stack(Stack<T>&& other) {
    size = other.Size();
    head = other.head;
    tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;
    other.size = nullptr;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    Clear();

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
}

template<typename T>
void Stack<T>::Push(const T value) {
    head = new Node{value, head};

    if (tail == nullptr) {
        tail = head;
    }

    size++;
}

template<typename T>
void Stack<T>::Pop() {
    if (size == 0) {
        throw "there is no items in Stack";
    } else {
        Node* temp = head->next;

        delete head;
        head = temp;

        size--;
    }
}

template<typename T>
T& Stack<T>::Get() const {
    if (size == 0) {
        throw "there is no items in Stack";
    } else {
        return head->value;
    }
}

template<typename T>
void Stack<T>::Swap(Stack<T>& other) {
    std::swap(size, other.Size());
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

template<typename T>
void Stack<T>::Merge(Stack<T>& other) {
    size = size + other.Size();
    other.tail->next = head;
    head = other.head;
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& other) const {
    if (size == other.Size()) {
        Node* first = head;
        Node* second = other.head;

        for (int i = 0; i < size; i++) {
            if (first->value != second->value) {
                return false;
            }

            first = first->next;
            second = second->next;
        }
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& other) const {
    return !(*this == other);
}