#pragma once
#include <string>
#include <cstddef>
#include <initializer_list>

class Queue {
    struct Node {
        std::string value;
        Node* prev;
        Node* next;
    };
    public:
        Queue() = default;
        Queue(const Queue& q);
        Queue(const std::initializer_list<std::string>& list);
        ~Queue();

        void Push(const std::string& s);
        void Pop();
        inline size_t Size() const {
            return size;
        }
        inline bool Empty() const {
            return size == 0;
        }

        inline std::string& Get() const {
            return tail->value;
        }

        bool operator==(const Queue& q) const;
        bool operator!=(const Queue& q) const;

        Queue& operator=(const Queue& q);

    private:
        Node* head = nullptr;
        Node* tail = nullptr;

        size_t size = 0;
};
