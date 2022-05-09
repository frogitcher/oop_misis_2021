#pragma once
#include <cstdint>
#include <initializer_list>

template <typename T>
class Stack {
    struct Node {
        T value;
        Node* next;
    };
    public:
    Stack() = default;
    ~Stack()
    {
        Clear();
    }
  void  Clear()
    {
         while (!Empty()){
            Pop();
            }
    }
    Stack(const Stack<T>& stack)
    {
        *this=stack;
    }
    Stack(Stack<T>&& stack)
    {
        head = stack.head;
        tail = stack.tail;
        size = stack.size;
        stack.head = nullptr;
        stack.tail = nullptr;
        stack.size = 0;
    }
    Stack(const std:: initializer_list<T>& list)
    {
      //  for (int i = 0; i < list.size(); i++)
        for (auto i : list)
        {
            Push(i);
        }
    }
    
    void Pop()
    {
        if (size > 0)
        {
            size--;
            Node* new_head = head->next;
            delete head;
            head=new_head;
            if (size == 0){ 
                tail = nullptr;
            }

        } else { throw "there are no elements in the stack";}
    }
    void Push(const T& value)
    {
        head = new Node {value, head};
        if (tail == nullptr)
        {
            tail = head;
        }
        size = size + 1;
    }
    T& Get() const
    {
        if (size == 0){
        throw "there are no elements in the stack";
        }
        return head->value;
    }
   /* Node Get_head()
    {
        return head;
    }*/
    bool Empty() const
    {
        return size == 0;
    }
    size_t Size() const
    {
        return size;
    }
    void Swap(Stack<T>& stack)
    {
        Stack <T> a=stack;
        stack=*this;
        *this=a;
    }
    //void Move();
    void Merge(Stack<T>& stack)
    {
        tail->next=stack.head;
        tail = stack.tail;
        size = stack.size+size;
        stack.head = nullptr;
        stack.tail = nullptr;
        stack.size = 0;
    }

     Stack<T>& operator=(const Stack<T>& stack)
    {
        Clear();
        if (stack.size > 0){
            head = new Node {stack.head->value, nullptr};
            Node* a = stack.head->next;
            Node* b = head;
            for (int i = 0; i<stack.size-1; i++){
                b->next = new Node { a->value, nullptr};
                b = b->next;
                a = a->next;
            }
            tail = b;
        }
        size=stack.size;
        return *this;
    }
    Stack<T>& operator=(const Stack<T>&& stack){
        head = stack.head;
        tail = stack.tail;
        size = stack.size;
        stack.head = nullptr;
        stack.tail = nullptr;
        stack.size = 0;
        return *this;
    }

    bool operator==(const Stack<T>& stack) const
    {
        if (stack.size == size){
            Node* a = head;
            Node* b = stack.head;
            for (int i = 0; i < size; i++){
                if (a->value != b->value) {return false;}
                a = a->next;
                b = b->next;
            }
            return true;
        } else
        {return false;}
    }
    bool operator!=(const Stack<T>& stack) const
    {
        return (!(stack == *this));
    }

    private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
        
};

