#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "header.h"


DynamicArray::DynamicArray(int64_t _size, int value): size(_size) ,capacity(_size) {
    data = new int[capacity];
    std::fill(data,data+size,value);
}


DynamicArray::DynamicArray(DynamicArray& other): size(other.size), capacity(other.capacity) {
    data = new int[capacity];
    std::copy(other.data,other.data+other.size,data);
}


void DynamicArray::Insert(int64_t index, int value){
    Resize(size+1);
    for (int i =size-1;i>index;i--){
        data[i] = data[i-1];
    }

    data[index] = value;
}

DynamicArray::~DynamicArray(){
    delete[] data;
}

bool DynamicArray::Empty() const{
    return (size==0);
}

int DynamicArray::Size() const{
    return size;
}

int* DynamicArray::Begin() const{
    return data;
}
int* DynamicArray::End() const{
    return data+size;
}
void DynamicArray::Resize(int64_t new_size){
    if (size<0){
        throw "size can't be below zero";
    }
    if (new_size>size){
        capacity = new_size;
        int* new_data = new int[new_size];
        std::copy(data,data+size,new_data);
        std::fill(new_data+size,new_data+new_size,0);
        size = new_size;
        delete[] data;
        data = new_data;
    }
}

DynamicArray& DynamicArray::operator=(DynamicArray& other){
    Resize(other.capacity);
    std::copy(other.data,other.data+size,data);

    return *this;
}


Set::Set(Set& other): a(other.a){
    
}



void DynamicArray::Erase(int64_t index){
    if (index<0){
        throw "index can't be below zero";
    }

    std::copy(data+index+1,data+size,data+index);
}

int& DynamicArray::operator[](int64_t i){
    return *(data+i);
}

int Set::Size(){
    return a.Size();
}

void Set::Insert(int64_t index, int value){
    a.Insert(index, value);
    Sort();
}


void Set::Sort(){
    for (int i=0;i<a.Size();i++){
        for (int j=i+1;j<a.Size();j++){
            if (a[i]==a[j]){
                a.Erase(j);
            }
        }
    }

    for (int i=1;i<a.Size();i++){
        for (int j=1;j<a.Size();j++){
            if (a[i-1]>a[i]){
                std::swap(a[i-1],a[i]);
            }
        }
    }
}

// P.s. Не успел написать сет, из-за того что пришлось динамик писать :)))
/*
git init
git remote add origin ссылка https://github.com/frogitcher/oop_misis_2022
gir fetch(перекинуть свою  папку фамилия подальше)
git checkout "g4vrysh0v_g_m"
git add 
git commit -m ""
git push origin "g4vrysh0v_g_m"
*/
