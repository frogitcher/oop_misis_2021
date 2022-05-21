#include "queue.h"
#include <stdexcept>

Queue::Queue(const std::initializer_list<std::string>& list)
    : size(list.size()) {
        for (auto element : list) {
            Push(element);
        }
}

Queue::~Queue() {
    while (!Empty()) {
        Pop();
    }
}

void Queue::Push(const std::string& s) {
    tail = new Node{s, tail, nullptr};
    if (head == nullptr) {
        head = tail;
    }
    ++size;
}

void Queue::Pop() {
    if (head == nullptr) {
        throw std::invalid_argument("Pop on empty queue!");
    }
    Node* cur = head;
    head->next = head->prev;
    head = head->next;
    delete cur;
    if (head == nullptr) {
        tail = nullptr;
    }
    --size;
}

bool Queue::operator==(const Queue& q) const {
    if (size != q.size) {
        return false;
    }
    Node* a = head;
    Node* b = q.head;
    while (a->next != nullptr) {
        if (a->value != b->value) {
            return false;
        }
        a = a->next;
        b = b->next;
    }
    return true;
}

bool Queue::operator!=(const Queue& q) const {
    return !(*this == q);
}
