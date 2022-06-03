#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "test.h"
#include <iostream>

	Stack::Stack(int size_, int value): size(size_), capacity(size_), data(new int[size_]){
        data= new int[size_];
        for (int i=0;i < size;i++)
        {
            Push(value);
        }
    }
    Stack::Stack(Stack& other):size(other.size), capacity(other.capacity), data(new int[other.size])
    {
        *this=other;
    }
    Stack& Stack:: operator=(const Stack& other)
    {
        Reallocate(other.capacity);
        std::copy(other.data, other.data+other.size, data);
        return *this;
    }
    bool Stack:: operator==(const Stack& other)
    {
        if (size==other.size)
        {
            return std::equal(data, data+size, other.data, other.data+other.size);
        }
        return false;
    }
    bool Stack:: operator!=(const Stack& other)
    {
        return (!(*this==other));
    }
    Stack::~Stack(){
        while (!Empty())
        {
            Pop();
        }
    }
    int Stack::Get()
    {
        return *data;
    }
    int Stack::Size()
    {
        return size;
    }
    bool Stack::Empty()
    {
        return size==0;
    }
   void Stack::Pop()
    {
        std::copy(data+1, data+size, data);
        size--;
    }
    void Stack::Clear()
    {
        size=0;
    }
    void Stack::Push(int value)
    {
        Reallocate(size+1);
        std::copy(data, data+size, data+1);
        *data=value;
        size++;
    }
    void Stack::Reallocate(int new_capacity)
    {
        if (new_capacity>capacity){
       int* new_data = new int [new_capacity*2+1];
        std::copy(data, data+size,new_data);
         delete[] data;
         data=new_data;
         capacity=new_capacity;
        }
    }




















/*
git init
git remote add origin ссылка https://github.com/frogitcher/oop_misis_2022
gir fetch(перекинуть свою  папку фамилия подальше)
git checkout "bOrOdKiNa_M_a))))))"
git add 
git commit -m ""
git push origin "bOrOdKiNa_M_a))))))"
*/