#pragma once
#include <initializer_list>
#include <cstddef>
#include <utility>
#include <stdexcept>
template<typename T>
class Stack
{
public:
    struct Node
    {
        T value;
        Node* next;
    };
    // конструкторы
    Stack(const Stack<T>& st){
        *this = st;
    };
    Stack(Stack<T>&& st){
        head = st.head;
        tail = st.tail;
        size = st.size;
        st.head = nullptr;
        st.tail = nullptr;
        st.size = 0;
    };
    Stack(const std::initializer_list<T>& list){
        for (auto& element : list){
            Push((T)element);
        }
        size = list.size();
    };
    Stack() = default;
    ~Stack(){
        Clean_up();
    };
    // методы
    void Push(const T& value){
        head = new Node{value, head};
        if(tail == nullptr){
            tail = head;
        }
        ++size;
    };
    void Pop(){
        if (Empty()) {
				throw std::length_error("Stack is empty!");
        }
        Node* upper = head;
        head = upper->next;
        delete upper;
        if (head == nullptr){
            tail = nullptr;
        }
        --size;
    };
    T& Get() const{
        if (Empty()) {
				throw std::length_error("Stack is empty!");
        }
        return head->value;
    };
    bool Empty() const{
        return size == 0;
    };
    std::size_t Size() const{
        return size;
    };
    void Swap(Stack<T>& st){
        std::swap(head, st.head);
        std::swap(tail, st.tail);
        std::swap(size, st.size);
    };
    void Merge(Stack<T>& st){
        tail->next = st.head;
        tail = st.tail;
        size += st.size;
        st.size = 0;
        st.head = nullptr;
        st.tail = nullptr;
    };
    void Clean_up(){
        while(tail != nullptr){
            Pop();
        }
    };
    // Опрераторы
    Stack<T> operator=(const Stack<T>& other) {
    Clean_up();
    if (other.Size() != 0) {
        head = new Node{ other.head->value, nullptr };
        Node* one = other.head->next;
        Node* two = head;
        while (one != nullptr) {
            two->next = new Node{ one->value, nullptr };
            two = two->next;
            one = one->next;
        }
        tail = two;
	}
	size = other.Size();
    return *this;
    };
	bool operator==(const Stack<T>& st) const{
        if (st.size != size){
            return false;
        }
        else{
            Node *first = head;
            Node *second = st.head;
            while(first != nullptr){
                if (first->value != second->value){
                    return false;
                }
                first = first->next;
                second = second->next;
            }
            return true;
        }
    };
	bool operator!=(const Stack<T>& st) const{
        return !(*this == st);
    } 
    inline friend Node* Get_Head(const Stack<T>& st) {
			return st.head;
		}
    inline friend Node* Get_Tail(const Stack<T>& st) {
        return st.tail;
    }
    
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t size = 0;
};
template <typename T>
inline typename Stack<T>::Node* Get_Head(const Stack<T>& st);

template <typename T>
inline typename Stack<T>::Node* Get_Tail(const Stack<T>& st);