//
// Created by 11_11 on 09.04.2022.
//

#ifndef OOP_MISIS_2022_DINAMIC_ARRAY_H
#define OOP_MISIS_2022_DINAMIC_ARRAY_H

#include <cstdint>
#include <initializer_list>
#include <memory>


struct Node{
    int value;
    Node** up;
    Node();
};
class Iterator_Stable_Dynamic_Array;




class Stable_Dynamic_Array {
public:
    Stable_Dynamic_Array(size_t size = 0, int value = 0);
    Stable_Dynamic_Array(const Stable_Dynamic_Array& other);
    Stable_Dynamic_Array( Stable_Dynamic_Array&& other);
    Stable_Dynamic_Array(const std::initializer_list<int>& list);
    ~Stable_Dynamic_Array();

    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;

    void push_back(int value);
    void pop_back();
    void clear();
    void erase(size_t index);
    void resize(size_t new_size, int value = 0);
    void insert(size_t index, int value);
    void swap(Stable_Dynamic_Array& other);

    Iterator_Stable_Dynamic_Array begin();
    Iterator_Stable_Dynamic_Array end();

    int& operator[](size_t i) const;
    int& at(size_t i) const;

    Stable_Dynamic_Array& operator=(const Stable_Dynamic_Array& rhs);

    bool operator==(const Stable_Dynamic_Array& rhs) const;
    bool operator!=(const Stable_Dynamic_Array& rhs) const;

private:
    void relocate(int new_size);
    size_t size = 0;
    size_t capacity = 0;
    Node** data;

};
class Iterator_Stable_Dynamic_Array{
public:
    Iterator_Stable_Dynamic_Array(Iterator_Stable_Dynamic_Array const &array);

    int operator*();
    Iterator_Stable_Dynamic_Array operator+(int a) const;
    Iterator_Stable_Dynamic_Array operator+= (int a);
    Iterator_Stable_Dynamic_Array operator-(int a) const;
    Iterator_Stable_Dynamic_Array operator-= (int a);
    Iterator_Stable_Dynamic_Array operator++();
    Iterator_Stable_Dynamic_Array operator++(int a);
    Iterator_Stable_Dynamic_Array operator--();
    Iterator_Stable_Dynamic_Array operator--(int a);
    bool operator==(const Iterator_Stable_Dynamic_Array &other);
    bool operator!=(const Iterator_Stable_Dynamic_Array &other);
    friend Stable_Dynamic_Array;

private:
    Node* pos;
    Iterator_Stable_Dynamic_Array(Node* _pos);
};




#endif //OOP_MISIS_2022_DINAMIC_ARRAY_H
