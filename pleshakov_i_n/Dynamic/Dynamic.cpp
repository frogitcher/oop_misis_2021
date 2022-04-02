#include "Dynamic.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>


DynamicArray::DynamicArray()
    : array_size(0)
    , array_capacity(1)
    , data (nullptr){
}

DynamicArray::DynamicArray(size_t _size, int value)
    : array_size(_size)
    , array_capacity(_size)
    , data(nullptr){
        if (array_size < 0){
            throw std::invalid_argument("size can't be < 0");
        }else{
            data = new int[array_size];
            std::fill(data, data + array_size, value);
        }
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : array_size(other.array_size)
    , array_capacity(other.array_size)
    , data(nullptr){
        if (array_size == 0){
            data = nullptr;
        }else{
            data = new int[array_size];
            for (int i=0; i<array_size; ++i){
                data[i] = other.data[i];
            }
        }
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

void DynamicArray::resize(size_t new_size){
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
    resize(other.array_size);
    array_size = other.array_size;
    array_capacity = other.array_size;
    for (int i=0; i<array_size; ++i){
        data[i] = other.data[i];
    }
}

int& DynamicArray::at(int i) const{
    if (i < 0 && i + array_size >= 0){
        return data[array_size + i];
    }
    if (i >= 0 && i < array_size){
        return data[i];
    }
    if((i < 0 && i + array_size < 0) || (i >= 0 && i >= array_size)){
        throw std::invalid_argument("Incorrect index");
    }
}

int& DynamicArray::operator[](int i){
    at(i);
}

void DynamicArray::push_back(int value){
    resize(array_size + 1);
    data[array_size-1] = value;
}

void DynamicArray::pop_back(){
    if (array_size == 0){
        throw std::invalid_argument("Array is empty");
    }else{
        --array_size;
    }
}

void DynamicArray::clear(){
    array_size = 0;
}

void DynamicArray::erase(size_t index){
    if (index < 0 || index >= array_size){
        throw std::invalid_argument("Incorrect index");
    }
    if (array_size == 0){
        throw std::invalid_argument("Array is empty");
    }
    for (int i=index; i<array_size; ++i){
        data[i] = data[i+1];
    }
    --array_size;
}

void DynamicArray::insert(size_t index, int value){
    resize(array_size + 1);
    for (int i=array_size-1; i>index; --i){
        data[i] = data[i-1];
    }
    data[index] = value;
}

void DynamicArray::swap(DynamicArray& other){
    if (other.array_size >= array_size){
        size_t save_size = array_size;
        resize(other.array_size);
        int second_value;
        for (int i=0; i<other.array_size; ++i){
            second_value = other.data[i];
            other.data[i] = data[i];
            data[i] = second_value;
        }
        other.resize(save_size);
    }else{
        size_t save_size = other.array_size;
        other.resize(array_size);
        int second_value;
        for (int i=0; i<array_size; ++i){
            second_value = other.data[i];
            other.data[i] = data[i];
            data[i] = second_value;
        }
        resize(save_size);
    }
}

void DynamicArray::assign(size_t new_size, int value){
    resize(new_size);
    array_size = new_size;
    std::fill(data, data+array_size, value);
}

int* DynamicArray::end(){
    return data+array_size-1;
}

int* DynamicArray::begin(){
    return data;
}









