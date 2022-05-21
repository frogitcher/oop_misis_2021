#include "queue.h"
#include <initializer_list>
#include <cstdint>

template<typename T>
Queue<T>::Queue(const Queue<T>& other) {
    this->Clear();

    this->size = other.Size();
    this->head = other->head;
    this->tail = other->tail;
}

template<typename T>
Queue<T>::Queue(const std::initializer_list<T>& list) {
    this->size = 0;

    for (auto i : list) {
        this->Push(i);
    }
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other) {
    this->Clear();

    this->size = other.Size();
    this->head = other->head;
    this->tail = other->tail;
}

template<typename T>
Queue<T>::Queue(Queue<T>&& other) {
    this->Empty();

    this->size = other.Size();
    this->head = other->head;
    this->tail = other->tail;
    other->size = nullptr;
    other->tail = nullptr;
    other->head = nullptr;
}

template<typename T>
Queue<T>::~Queue() {
    this->Clear();
}

template<typename T>
size_t Queue<T>::Size() const {
    return this->size;
}

template<typename T>
bool Queue<T>::Empty() const {
    return this->size == 0;
}

template<typename T>
void Queue<T>::Clear() {
    while (this->size > 0) {
        this->Pop();
    }
}

template<typename T>
T Queue<T>::Get() const {
    return this->tail->value;
}

template<typename T>
void Queue<T>::Push(T value) {
    this->head = new Node{value, head};
    if (this->tail == nullptr) {
        this->tail = this->head;
    }
    this->size++;
}

template<typename T>
void Queue<T>::Pop() {
    size_t s = this->size;
    *Node temp = this->head;

    while(s > 2) {
        temp = temp->next;

        s--;
    }

    this->tail = temp;
    delete this->tail->next;
    this->tail->next = nullptr;
    
    this->size--;
}

template<typename T>
bool Queue<T>::operator==(Queue<T>& other) {
    if (this->size == other->size) {
        Node* first = this->head;
        Node* second = this->head;

        for (int i = 0; i < other.Size(); i++) {
            if (first->value != second->value) {
                return false;
            }

            first = first->next;
            second = second->next;
        }

        return true
    } else {
        return false;
    }
}

template<typename T>
bool Queue<T>::operator!=(Queue<T>& other) {
    return !(*this == other);
}

template<typename T>
Queue<T> Queue<T>::operator=(Queue<T>& other) {
    this->Clear();

    this->size = other->Size();
    this->head = other->head;
    this->tail = other->tail;
}