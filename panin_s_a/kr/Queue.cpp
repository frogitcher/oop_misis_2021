#pragma once
#include <initializer_list>
#include <string>
#include <stdexcept>
#include <iostream>

class Queue {
    struct Node
    {
        Node *Prev;
        std::string Val;
        Node *Next;
    };
public:
    Queue() = default;

    Queue(std::initializer_list <std::string>& ar)
    {
        for (auto item : ar)
            Push(item);
    }

    Queue(const Queue& q)
    {
        *this = q;
    }

    ~Queue()
    {
        while (!Empty())
        {
            Pop();
        }
    }

    void Push(std::string st)
    {

        if (size == 0)
        {
            head = new Node{head, st, tail};
            tail->Next = head;
            tail->Prev = head;
            head->Prev = tail;
            
            head->Next = tail;
        }
        else {
            head = new Node{head,st,tail};
            head->Prev = tail;
            tail->Prev = head;
        }
        ++size;
       
    }

    void Pop()
    {
        if (size == 0)
        {
            throw std::length_error("Pop error");
        }
        else {
            Node* v1 = head->Prev;
            std::string val = head->Val;
            head->Prev = v1->Prev;
            head->Val = val;
            size--;
        }
    }

    std::size_t Size() const
    {
        return size;
    }

    bool Empty() const
    {
        return (size == 0);
    }
    std::string Get() const
    {
        return head->Val;
    }
    bool operator==(const Queue& rhs) const
    {
        return (size == rhs.size);
    }
    bool operator!=(const Queue& rhs) const
    {
        return (size != rhs.size);
    }
    bool operator=(const Queue& rhs)
    {

    }
private:
    Node* head = nullptr;
    std::size_t size = 0 ;
    Node* tail = nullptr;
};

int main()
{
    Queue q;
    q.Push("21");
    q.Push("41");
    q.Pop();
    // while (q.Size())
    // {
    //     auto val = q.Get();
    //     q.Pop();
    //     std::cout << val << '\n';
    // }
    return 0;
}