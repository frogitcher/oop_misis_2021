//
// Created by 11_11 on 21.05.2022.
//

#ifndef UNTITLED11_STACK_H
#define UNTITLED11_STACK_H


#include <memory>
#include "dinamic_array.h"

template<class T=int, class Container=dinamic_array>
class Stack{
public:
    Stack();
    Stack(const Stack &other);
    Stack(Stack &&other) noexcept ;
    ~Stack()=default;
    void Push(const T& value);
    void Push(T&& value);
    void Pop();
    size_t Size();
    bool Empty();
    T get();
    bool operator==(const Stack& other);
    bool operator!=(const Stack& other);
    void operator=(const Stack& other);
    void operator=(Stack&& other);

private:
    Container a;


};

template<class T, class Container>
Stack<T, Container>::Stack(){}

template<class T, class Container>
Stack<T, Container>::Stack(const Stack &other):a(other) {}

template<class T, class Container>
Stack<T, Container>::Stack(Stack &&other) noexcept: a(std::forward<Container>(other)){
}

template<class T, class Container>
void Stack<T, Container>::Push(const T &value) {
    a.push_back(value);
}

template<class T, class Container>
void Stack<T, Container>::Push(T &&value) {
    a.push_back(std::forward<T>(value));
}

template<class T, class Container>
void Stack<T, Container>::Pop() {
    a.pop_back();
}

template<class T, class Container>
size_t Stack<T, Container>::Size() {
    return a.size();
}

template<class T, class Container>
bool Stack<T, Container>::Empty() {
    return a.size()==0;
}

template<class T, class Container>
T Stack<T, Container>::get() {
    return a.back();
}

template<class T, class Container>
bool Stack<T, Container>::operator==(const Stack &other) {
    return (a==other);
}

template<class T, class Container>
bool Stack<T, Container>::operator!=(const Stack &other) {
    return a!=other;
}

template<class T, class Container>
void Stack<T, Container>::operator=(const Stack &other) {
    a=other;
}

template<class T, class Container>
void Stack<T, Container>::operator=(Stack &&other) {
    a=std::forward<T>(other);
};


#endif //UNTITLED11_STACK_H
