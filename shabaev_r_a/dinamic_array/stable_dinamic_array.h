//
// Created by 11_11 on 09.04.2022.
//

#ifndef OOP_MISIS_2022_DINAMIC_ARRAY_H
#define OOP_MISIS_2022_DINAMIC_ARRAY_H

#include <cstdint>
#include <initializer_list>
#include <memory>
#include "iterator"


struct Node{
    int value;
    Node** up;
    Node();
};
template<typename T>
class Iterator_Stable_Dynamic_Array;




class Stable_Dynamic_Array {
public:
    typedef int value_type;
    typedef Iterator_Stable_Dynamic_Array<int> iter;
    typedef Iterator_Stable_Dynamic_Array<const int> const_iter;
    typedef std::size_t size_type;
    typedef int& reference;
    typedef const int& const_reference;

    Stable_Dynamic_Array(size_t size = 0, int value = 0);
    Stable_Dynamic_Array(const Stable_Dynamic_Array& other);
    Stable_Dynamic_Array( Stable_Dynamic_Array&& other);
    Stable_Dynamic_Array(const std::initializer_list<int>& list);
    ~Stable_Dynamic_Array();

    size_type Size() const;
    size_type Capacity() const;
    bool Empty() const;

    void push_back(int value);

    void pop_back();
    void clear();
    void erase(size_t index);
    void resize(size_t new_size, int value = 0);
    void insert(size_t index, int value);
    void swap(Stable_Dynamic_Array& other);

    iter begin() ;
    iter end() ;
    const_iter begin() const;
    const_iter end() const;

    const_reference operator[](size_t i) const;
    const_reference at(size_t i) const;
    reference operator[](size_t i);
    reference at(size_t i);

    Stable_Dynamic_Array& operator=(const Stable_Dynamic_Array& rhs);

    bool operator==(const Stable_Dynamic_Array& rhs) const;

    bool operator!=(const Stable_Dynamic_Array& rhs) const;

private:
    void relocate(size_t new_size);
    size_t size = 0;
    size_t capacity = 0;
    Node** data;

};
template<typename T>
class Iterator_Stable_Dynamic_Array{
public:
    typedef std::random_access_iterator_tag  iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
    Iterator_Stable_Dynamic_Array(Iterator_Stable_Dynamic_Array const &array);
    reference operator*();
    ptrdiff_t operator-(const Iterator_Stable_Dynamic_Array &other);
    Iterator_Stable_Dynamic_Array operator+(int a) const;
    Iterator_Stable_Dynamic_Array operator+= (int a);
    Iterator_Stable_Dynamic_Array operator-(int a) const;
    Iterator_Stable_Dynamic_Array operator-= (int a);
    Iterator_Stable_Dynamic_Array operator++();
    Iterator_Stable_Dynamic_Array operator++(int a);
    Iterator_Stable_Dynamic_Array operator--();
    Iterator_Stable_Dynamic_Array operator--(int a);
    bool operator<(const Iterator_Stable_Dynamic_Array &rhs);
    bool operator<=(const Iterator_Stable_Dynamic_Array &rhs);
    bool operator>(const Iterator_Stable_Dynamic_Array &rhs);
    bool operator>=(const Iterator_Stable_Dynamic_Array &rhs);
    Iterator_Stable_Dynamic_Array operator=(const Iterator_Stable_Dynamic_Array &other);
    bool operator==(const Iterator_Stable_Dynamic_Array &other);
    bool operator!=(const Iterator_Stable_Dynamic_Array &other);
    friend Stable_Dynamic_Array;
private:
    Node* pos;
    Iterator_Stable_Dynamic_Array(Node* _pos);
};

template<typename T>
Iterator_Stable_Dynamic_Array<T>::Iterator_Stable_Dynamic_Array(const Iterator_Stable_Dynamic_Array &array) {
    pos=array.pos;
}

template<typename T>
typename Iterator_Stable_Dynamic_Array<T>::reference Iterator_Stable_Dynamic_Array<T>::operator*() {
    return pos->value;
}

template<typename T>
Iterator_Stable_Dynamic_Array<T> Iterator_Stable_Dynamic_Array<T>::operator+(int a) const {
    return {*(pos->up+a)};
}

template<typename T>
Iterator_Stable_Dynamic_Array<T> Iterator_Stable_Dynamic_Array<T>::operator+=(int a) {
    pos=*(pos->up+a);
    return *this;
}

template<typename T>
Iterator_Stable_Dynamic_Array<T> Iterator_Stable_Dynamic_Array<T>::operator-(int a) const {
    Iterator_Stable_Dynamic_Array it=*this;
    it.pos = *((pos->up)-a);
    return it;
}

template<typename T>
Iterator_Stable_Dynamic_Array<T> Iterator_Stable_Dynamic_Array<T>::operator-=(int a) {
    this->pos=*((pos->up)-a);
    return *this;
}

template<typename T>
Iterator_Stable_Dynamic_Array<T> Iterator_Stable_Dynamic_Array<T>::operator++() {
    return *this+=1;
}

template<typename T>
Iterator_Stable_Dynamic_Array<T> Iterator_Stable_Dynamic_Array<T>::operator++(int a) {
    auto it=*this;
    ++(*this);
    return it;
}

template<typename T>
Iterator_Stable_Dynamic_Array<T> Iterator_Stable_Dynamic_Array<T>::operator--() {
    return *this-=1;
}

template<typename T>
Iterator_Stable_Dynamic_Array<T> Iterator_Stable_Dynamic_Array<T>::operator--(int a) {
    auto it=*this;
    --(*this);
    return it;
}

template<typename T>
bool Iterator_Stable_Dynamic_Array<T>::operator==(const Iterator_Stable_Dynamic_Array &other) {
    return pos == other.pos;
}

template<typename T>
bool Iterator_Stable_Dynamic_Array<T>::operator!=(const Iterator_Stable_Dynamic_Array &other) {
    return !((*this) == other);
}

template<typename T>
Iterator_Stable_Dynamic_Array<T>::Iterator_Stable_Dynamic_Array(Node *_pos):pos(_pos) {}

template<typename T>
Iterator_Stable_Dynamic_Array<T> Iterator_Stable_Dynamic_Array<T>::operator=(const Iterator_Stable_Dynamic_Array &other){
    pos=other.pos;
}

template<typename T>
ptrdiff_t Iterator_Stable_Dynamic_Array<T>::operator-(const Iterator_Stable_Dynamic_Array &other) {
    return pos->up - other.pos->up;
}

template<typename T>
bool Iterator_Stable_Dynamic_Array<T>::operator<(const Iterator_Stable_Dynamic_Array &rhs) {
    return (*(this)-rhs)<0;
}

template<typename T>
bool Iterator_Stable_Dynamic_Array<T>::operator<=(const Iterator_Stable_Dynamic_Array &rhs) {
    return (*(this)-rhs)<=0;
}

template<typename T>
bool Iterator_Stable_Dynamic_Array<T>::operator>(const Iterator_Stable_Dynamic_Array &rhs) {
    return (*(this)-rhs)>0;
}

template<typename T>
bool Iterator_Stable_Dynamic_Array<T>::operator>=(const Iterator_Stable_Dynamic_Array &rhs) {
    return (*(this)-rhs)>=0;
}


#endif //OOP_MISIS_2022_DINAMIC_ARRAY_H
