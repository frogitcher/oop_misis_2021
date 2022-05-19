#pragma once
#include <ostream>
#include <initializer_list>

template<typename T>

class Stack {

public:
    struct Node {
        T value;
        Node* next;
    };
    Stack() = default;
    Stack(const Stack<T>& other) {
        Copy(other);
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    Stack(const std::initializer_list<T>& list) {
        for (auto& i: list) {
            Push(i);
        }
    }
    Stack(Stack<T>&& other) {
        size = other.size;
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    ~Stack() {
        Clear();
    }
    void Clear() {
        while (size > 0) {
            Pop();
        }
    }
    void Copy(const Stack<T>& other) {
        Node* n = other.head;
        for (size_t i = 0; i < other.Size(); i++) {
            this->Push(n->value);
            n = n->next;
        }
    }
    size_t Size() const {
        return size;
    }
    T& Get() const {
        if (head == nullptr) {
            throw std::underflow_error("Stack is empty");
        }
        else {
            return head->value;
        }
    }
    bool Empty() const{
        return (this->size == 0);
    }
    void Push(const T& value) {
        this->head = new Node{value, head};
        if (this->tail == nullptr) {
            this -> tail = this-> head;
        }
        this->size++;
    }
    void Pop() {
        if (size == 0)  {
            throw std::underflow_error("Stack is empty");
        }
        if (this->head->next) {
            Node* t = this->head->next;
            delete this->head;
            this->head = t;
        }
        size--;
    }
    void merge(Stack<T> other) {
        if (!other.Empty()) {
            other.tail->next = head;
            head = other.head;
            size += other.size;
        }
        other.size = 0;
        other.head = nullptr;
        other.tail = nullptr;
    }
    void Swap(Stack<T> other) {
        std::swap(size, other.size);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }
    Stack& operator=(const Stack<T>& other) {
        Clear();
        Copy(other);
        return *this;
    }
    Stack& operator=(Stack<T>&& other) {
        Clear();
        Swap(other);
        other.Clear();
        return *this;
    }
    bool operator==(const Stack<T>& other) const {
        if (size != other.size) {
            return false;
        }
        Node* lhs = head;
        Node* rhs = other.head;
        while (lhs != nullptr) {
            if (lhs->value != rhs->value) {
                return false;
            }
            lhs = lhs->next;
            rhs = rhs->next;
        }
        return true;
    }
    bool operator!=(const Stack<T>& other) const {
        return !(*this == other);
    }

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};
