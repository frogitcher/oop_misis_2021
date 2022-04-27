#pragma once

template <typename T>
class Stack {
public:
    struct Node {
        T value;
        Node* next = nullptr;
        Node(T _value, Node* _next);

    };
    Stack() = default;
    Stack(const std::initializer_list<T>& list);
    Stack(const Stack<T>& other);
    Stack(Stack<T>&& other);
    ~Stack();
    void push(const T value);
    void pop();
    T& get_front() const;
    T& get_back() const;
    bool Empty() const;
    size_t Size() const;
    void swap(Stack<T>& other);
    void merge(Stack<T>& other);
    void clear();
    bool operator==(const Stack<T>& other) const;
    bool operator!=(const Stack<T>& other) const;
    Stack<T>& operator=(const Stack<T>& other);

private:
    size_t size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;
};
