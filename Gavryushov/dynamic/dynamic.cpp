
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "dynamic.h"


int& DynamicArray::operator[](int64_t i){
    return *(data+i);
}
int& DynamicArray::at(int64_t i) const{
    if (i>= size || i<0){
        throw "Index out of range";
    }
    return *(data+i);
}



DynamicArray::DynamicArray(const DynamicArray &other):size(other.size),capacity(other.capacity){
    data = new int[capacity];
    std::copy(other.data,other.data+other.size,data);

}

DynamicArray::DynamicArray(const std::initializer_list <int> &list):size(list.size()),capacity(list.size()){
    data = new int[capacity];
    std::copy(list.begin(),list.end(),data);
}

DynamicArray::DynamicArray(int64_t _size,int value):size(_size), capacity(_size){
    data = new int[capacity];
    std::fill(data,data+_size,value);
}

DynamicArray::~DynamicArray(){
    delete[] data;
}

int64_t DynamicArray:: Size() const{
    return size;
}

int64_t DynamicArray:: Capacity() const{
    return capacity;
}


bool DynamicArray:: Empty() const{
    return (size==0);
}

void DynamicArray:: Reallocate(int64_t new_capacity){
    if (new_capacity>capacity){
        capacity = new_capacity;
        int* new_data = new int[new_capacity];
        std::copy(data,data+size,new_data);
        delete[] data;
        data = new_data;
    }

}
void DynamicArray:: pop_back(){
    if (size==0){
        throw "Array is empty";
    }
    size--;
}

void DynamicArray:: clear(){
    size = 0;
}

void DynamicArray:: erase(int64_t index){
    if (index<0 || index>size-1){
        throw "Index out of range";
    }

    std::copy(data+index+1,data+size,data+index);
    size--;
}

void DynamicArray::resize(int64_t new_size){
    if (new_size<0){
        throw "Size must be >=0";
    }
    Reallocate(new_size);

    if (new_size>size){
        std::fill(data+size,data+new_size,0);
    }
    size = new_size;
}

int* DynamicArray::begin(){
    return data;
}

int* DynamicArray::end(){
    return data+size;
}

void DynamicArray::swap(DynamicArray& other){
    std::swap(data,other.data);
    std::swap(size,other.size);
    std::swap(capacity,other.capacity);
}

void DynamicArray::assign(int64_t new_size, int value){
    if (new_size<0){
        throw "Size must be >=0";
    }
    Reallocate(new_size);
    size = new_size;
    std::fill(data,data+size,value);
}

bool DynamicArray::operator==(const DynamicArray& other) const{
    for (int i=0;i<size;i++){
        if (data[i] != other.data[i]){
            return false;
        }
    }
    if (other.size>size){
        return false;
    }
    return true;
}

bool DynamicArray::operator!=(const DynamicArray& other) const{
    return !(*this==other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other){
    resize(other.size);
    std::copy(other.data,other.data+other.size,data);

    return *this;
}

void DynamicArray::insert(int64_t index, int value){
    if (index < 0 || index > size){
        throw "Array out of range";
    }
    resize(size+1);
    for (int i=size-1;i>index;i--){
        data[i] = data[i-1];
    }
    //std::copy(data+index,data+size-1,data+index+1);
    data[index] = value;
}
void DynamicArray::push_back(int value){
    if (size==capacity){
        Reallocate(capacity*2+1);
    }
    data[size++]=value;
}