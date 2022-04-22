#pragma once
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Stack {

public:
    struct Node {
        T value;
        Node* next;
    };
    Stack() = default;
    Stack(const Stack<T>& st){
        Copy(st);
    }
    Stack(Stack<T>&& st) {
        size = st.size;
        head = st.head;
        tail = st.tail;
        st.size = 0;
        st.head = nullptr;
        st.tail = nullptr;
    }
    Stack(const std::initializer_list<T>& list) {
        for (auto& v: list) {
            Push(v);
        }
    }
    ~Stack(){
        Clear();
    }
    void Copy(const Stack<T>& st) {
        if (st.size == 0) {
            Clear();
        }
        else {
            head = new Node{st.head->value, nullptr};
        Node* cur = st.head->next;
        Node* prev = head;
        while (cur != nullptr) {
            prev->next = new Node{cur->value, nullptr};
            prev = prev->next;
            cur = cur->next;
        }
        tail = prev;
        size = st.size;
        }
    }
    void Clear() {
        while (size > 0) {
            Pop();
        }
    }
    void Push(const T& value) {
        head = new Node{value, head};
        if (tail == nullptr){
            tail = head;
        }
        ++size;
    }
    void Pop() {
        if (Empty()) throw std::length_error("stack is empty");
        Node* temp = head->next;
        delete head;
        head = temp;
        if (head == nullptr) tail = nullptr;
        --size;
    }
    void Swap(Stack<T>& st) {
        Node* sw = head;
        head = st.head;
        st.head = sw;

        sw = tail;
        tail = st.tail;
        st.tail = sw;

        size_t temp_size = size;
        size = st.size;
        st.size = temp_size;
    }
    void Merge(Stack<T>& st) {
        tail->next = st.head;
        tail = st.tail;
        size += st.size;
        st.size = 0;
        st.head = 0;
        st.tail = 0;
    }
    bool Empty() const {
        return size == 0;
    }
    T& Get() const {
        if (Empty()) throw std::length_error("stack is empty");
        return head->value;
    }
    size_t Size() const {
        return size;
    }
    Stack<T>& operator=(Stack<T>&& st){
        Clear();
        Swap(st);
        st.Clear();
        return *this;
    }
    Stack<T>& operator=(const Stack<T>& st) {
        Clear();
        Copy(st);
        return *this;
    }

    bool operator==(const Stack<T>& st) const {
        if (size != st.size) {
            return false;
        }
        Node* a = head;
        Node* b = st.head;
        while (a != nullptr) {
            if (a->value != b->value) {
                return false;
            }
            a = a->next;
            b = b->next;
        }
        return true;
    }
    bool operator!=(const Stack<T>& st) const {
        return !(*this == st);
    }
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
};




/*
⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆ 
⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿ 
⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀ 
⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉
*/