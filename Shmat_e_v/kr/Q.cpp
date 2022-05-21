#pragma once
#include "Q.h"

#include <initializer_list>

class Q::Q {
   private:
   public:
    Q();
    ~Q();
};

Q::Q(int size_, int v) {
    // :size(size_) {
    //     for (int i = 0; i < count; i++)
    //     {
    //         /* code */
    //     }

    // }
}

Q::~Q() {
    while (!empty()) {
        pop();
    }
}

void Q::push(int v) {
    if (head != nullptr) {
        /* code */
    }

    NewNode(v, tail);
    if (size == 1) {
        head = tail;
    }
}

bool Q::empty() {
    return size == 0;
}

void Q::NewNode(int v, Node* tail) {
    Node* temp = tail;
    tail = new Node(v, tail->next);

    size++;
    if (size == 1) {
        head = tail;
    }
}

void Q::pop() {
    Node* temp = head->next;
    int v = head->v;
    delete head;
}

int Q::get() {
    return head->v;
}
