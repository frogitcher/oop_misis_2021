#pragma once
#include <initializer_list>
#include <cstdint>

template<typename T>

class Queue {
public:
    Queue() = default;
    Queue(const Queue<T>& other);
    Queue(Queue<T>&& other);
    Queue(const std::initializer_list<T>& list);
    ~Queue();

    void Push(T value);
    void Pop();
    void Clear();
    size_t Size() const;
    bool Empty() const;
    T Get() const;

    bool operator==(Queue& other);
    bool operator!=(Queue& other);
    Queue<T> operator=(Queue& other);

    struct Node {
        Node* next = nullptr;
        T value;
    };
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};