#pragma once
#include <initializer_list>
#include <ostream>

class Q {
   public:
    struct Node {
        int v;
        Node* next;
    };

    Q() = default;
    ~Q() = default;

    Q(const Q& other);

    void NewNode(int v, Node* tail);

    void push(int v);
    void pop();
    int size(const Q&);
    bool empty();
    int get();

    Q& operator==(const Q& rhs);
    Q& operator!=(const Q& rhs);
    Q& operator=(const Q& rhs);

   private:
    int size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;
};

std::ostream& operator<<(std::ostream& os, const Q& q);