#include "Dynamic.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>


DynamicArray::DynamicArray()
    : array_size(0)
    , array_capacity(1)
    , data (nullptr){
        data = new int[1];
}

DynamicArray::DynamicArray(size_t _size, int value)
    : array_size(_size)
    , array_capacity(_size)
    , data(nullptr){
        data = new int[array_size];
        std::fill(data, data + array_size, value);
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : array_size(other.array_size)
    , array_capacity(other.array_size)
    , data(nullptr){
        data = new int[array_size];
        std::copy(other.data, other.data + other.array_capacity, data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& input_list)
    : array_size(input_list.size())
    , array_capacity(input_list.size())
    , data(nullptr){
        data = new int[array_size];
        std::copy(input_list.begin(), input_list.end(), data);
}

void DynamicArray::create_data(size_t new_size){
    int new_capacity = new_size * 2;
    int* new_data = new int[new_capacity];
    for (int i=0; i<array_size; ++i){
        new_data[i] = data[i];
    }
    array_capacity = new_capacity;
    delete[]data;
    data = new_data;
}

void DynamicArray::Resize(size_t new_size){
    if (new_size > array_capacity){
        create_data(new_size);
    }
    if (new_size > array_size){
        std::fill(data+array_size, data+new_size, 0);
    }
    array_size = new_size;
}

DynamicArray::~DynamicArray(){
    delete[]data;
}

size_t DynamicArray::Size() const{
    return array_size;
}

size_t DynamicArray::Capacity() const{
    return array_capacity;
}

bool DynamicArray::Empty() const{
    return (array_size == 0);
}

bool DynamicArray::operator==(const DynamicArray& other) const{
    if (array_size == other.array_size){
        for (int i=0; i<array_size; ++i){
            if (other.data[i] != data[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

void DynamicArray::operator=(const DynamicArray& other){
    Resize(other.array_size);
    array_size = other.array_size;
    array_capacity = other.array_size;
    std::copy(other.data, other.data + other.array_capacity, data);
}

int& DynamicArray::At(size_t i) const{
    if(i >= array_size){
        throw std::invalid_argument("Incorrect index");
    }else {
        return data[i];
    }
}

int& DynamicArray::operator[](size_t i){
    At(i);
}

void DynamicArray::Push_back(int value){
    Resize(array_size + 1);
    data[array_size-1] = value;
}

void DynamicArray::Pop_back(){
    if (array_size == 0){
        throw std::invalid_argument("Array is empty");
    }else{
        --array_size;
    }
}

void DynamicArray::Clear(){
    array_size = 0;
}

void DynamicArray::Erase(size_t index){
    if (array_size == 0){
        throw std::invalid_argument("Array is empty");
    }
    if (index >= array_size){
        throw std::invalid_argument("Incorrect index");
    }
    for (int i=index; i<array_size; ++i){
        data[i] = data[i+1];
    }
    --array_size;
}

void DynamicArray::Insert(size_t index, int value){
    Resize(array_size + 1);
    if (index > array_size){
        throw std::invalid_argument("Incorrect index");
    }
    for (int i=array_size-1; i>index; --i){
        data[i] = data[i-1];
    }
    data[index] = value;
}

void DynamicArray::Swap(DynamicArray& other){
    if (other.array_size >= array_size){
        size_t save_size = array_size;
        Resize(other.array_size);
        int second_value;
        for (int i=0; i<other.array_size; ++i){
            second_value = other.data[i];
            other.data[i] = data[i];
            data[i] = second_value;
        }
        other.Resize(save_size);
    }else{
        size_t save_size = other.array_size;
        other.Resize(array_size);
        int second_value;
        for (int i=0; i<array_size; ++i){
            second_value = other.data[i];
            other.data[i] = data[i];
            data[i] = second_value;
        }
        Resize(save_size);
    }
}

void DynamicArray::Assign(size_t new_size, int value){
    Resize(new_size);
    array_size = new_size;
    std::fill(data, data+array_size, value);
}

int* DynamicArray::end(){
    return data+array_size;
}

int* DynamicArray::begin(){
    return data;
}
