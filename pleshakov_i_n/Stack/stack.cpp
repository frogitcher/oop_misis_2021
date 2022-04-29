#include <algorithm>
#include <stdexcept>

#include "stack.h"

template<typename T>
Stack<T>::Stack(const Stack<T>& st){

    Node* sthead_copy = st.head;
    Node* st_copy = nullptr;

    while (sthead_copy != nullptr){
        st_copy = new Node({sthead_copy->value, st_copy});
        sthead_copy = sthead_copy->next;
    }

    while (st_copy != nullptr){
        head = new Node({st_copy->value, head});
        st_copy = st_copy->next;
        ++size;
    }
}

template <typename T>
Stack<T>::Stack(Stack<T>&& st){
    head = st.head;
    tail = st.tail;
    size = st.size;

    st.head = nullptr;
    st.tail = nullptr;
    st.size = 0;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& List){
    for (auto i : List){
        head = new Node({i, head});
        ++size;
    }
}

template <typename T>
Stack<T>::~Stack(){
    Clear();
}

template <typename T>
void Stack<T>::Push(const T& value){

    head = new Node{value, head};
    if (size == 0) tail = head;
    ++size;
}

template <typename T>
void Stack<T>::Pop(){
    if (size == 0) throw std::invalid_argument("Stack is empty");

    Node* new_head = head->next;
    delete head;
    head = new_head;
    --size;
}

template <typename T>
T& Stack<T>::Get() const{
    if (size == 0){
        throw std::invalid_argument("Stack is empty");
    }else{
        return head->value;
    }
}

template <typename T>
size_t Stack<T>::Size() const{
    return size;
}

template <typename T>
void Stack<T>::Clear(){
    while(size > 0){
        Pop();
    }
}

template <typename T>
bool Stack<T>::Empty() const{
    if (size) return false;
    return true;
}

template <typename T>
bool Stack<T>::operator==(const Stack<T>& st) const{
    bool flag = true;
    if (size != st.size) return false;

    Node* head_copy = head;
    Node* sthead_copy = st.head;
    int count = size;
    while (flag){
        if (count == 0) break;
        if (head_copy->value != sthead_copy->value){
            flag = false;
        }
        --count;
        head_copy = head_copy -> next;
        sthead_copy = sthead_copy -> next;
    }

    if (flag) return true;
    return false;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& st) const{
    return !(*this == st);
}

template<typename T>
void Stack<T>::Swap(Stack<T>& st){
    std::swap(head, st.head);
    std::swap(tail, st.tail);
    size_t a = st.size;
    st.size = size;
    size = a;
}

template <typename T>
void Stack<T>::operator=(const Stack<T>& st){
    Clear();
    Node* sthead_copy = st.head;
    Node* st_copy = nullptr;

    while (sthead_copy != nullptr){
        st_copy = new Node({sthead_copy->value, st_copy});
        sthead_copy = sthead_copy->next;
    }

    while (st_copy != nullptr){
        head = new Node({st_copy->value, head});
        st_copy = st_copy->next;
        ++size;
    }
}

template <typename T>
void Stack<T>::operator=(Stack<T>&& st){
    Swap(st);
    st.Clear();
}

template <typename T>
void Stack<T>::Merge(Stack<T>& st){
    Node* sthead_copy = st.head;
    Node* st_copy = nullptr;

    while (sthead_copy != nullptr){
        st_copy = new Node({sthead_copy->value, st_copy});
        sthead_copy = sthead_copy->next;
    }

    while (st_copy != nullptr){
        head = new Node({st_copy->value, head});
        st_copy = st_copy->next;
        ++size;
    }
}

