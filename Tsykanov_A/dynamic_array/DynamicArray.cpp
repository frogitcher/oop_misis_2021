#include "DynamicArray.h"
#include <algorithm>
#include <stdexcept>

// Конструкторы
DynamicArray::DynamicArray(int64_t lenght, int value = 0) 
    : size(lenght)
    , capacity(lenght) {
    data = new int[lenght];
    std::fill(begin(), end(), value);
}
DynamicArray::DynamicArray(const DynamicArray& other)
    : size(other.size)
    , capacity(other.capacity) {
    data = new int[capacity];
    std::copy(other.data, other.data + other.size, data);
}
DynamicArray::DynamicArray(const std::initializer_list<int>& list)
    : size(list.size())
    , capacity(list.size()){
    data = new int[capacity];
    std::copy(list.begin(), list.end(), data);
}
DynamicArray::~DynamicArray()
{
    delete[] data;
}
//Методы
void DynamicArray::resize(int64_t new_size, int value = 0){
    if (new_size < 0) {
        throw std::length_error("Length can't be negative!");
    }
    if (new_size >= capacity){
        reallocate(new_size);
    } 
    std::fill(begin() + ((size <= new_size) ? size : 0), begin() + new_size, value);
    size = new_size;
};
void DynamicArray::push_back(int value){
    if (size == capacity){
        if (capacity == 0){
            capacity = 1;
        }
        reallocate(capacity);
    }
    data[size++] = value;
};
void DynamicArray::pop_back(){
    if (size == 0) {
        throw std::length_error("Array is empty!");
    }
    --size;  
};
void DynamicArray::erase(int64_t index){
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index is out of range!");
    }
    if (size == 0) {
        throw std::length_error("Array is empty!");
    }
    std::copy(begin() + index + 1, end(),begin() + index) ;
    size--;
};
void DynamicArray::assign(int64_t new_size, int value){
    if (new_size < 0) {
        throw std::length_error("Length can't be negative!");
    }
    if (new_size == 0) {
        size = 0;
        return;
    }
    reallocate(new_size);
    for(int64_t i = 0; i < new_size; i++){
        data[i] = value;
    }
    size = new_size;
};
void DynamicArray::swap(DynamicArray& other){
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
};
void DynamicArray::insert(int64_t index, int value){
    if (size == 0) {
        throw std::length_error("Array is empty!");
    }
    if (size == capacity){
        if (capacity == 0){
            capacity = 1;
        }
        reallocate(capacity);
    }
    ++size;
    std::copy_backward(begin() + index, end() , end() + 1);
    data[index] = value;
};
//операторы
int& DynamicArray::operator[](int64_t i) const{
    return *(data + i);
};
int& DynamicArray::at(int64_t i) const{
    if (i < 0 || i >= size) {
        throw std::out_of_range("Index is out of range!");
    }
    return *(data + i);    
}; 
bool DynamicArray::operator==(const DynamicArray& other) const{
    return (size == other.size && std::equal<int*, int*>(data, data + size, other.data));
};
bool DynamicArray::operator!=(const DynamicArray& other) const{
    return !(*this == other);
};
DynamicArray& DynamicArray::operator=(const DynamicArray& rhs){
    size = rhs.size;
    capacity = rhs.capacity;
    std::copy(rhs.data, rhs.data + rhs.size, data);
    return *this;
};
void DynamicArray::reallocate(int64_t new_capacity) {
    int _new_capacity = std::max(new_capacity, size * 2);
        int *new_data = new int[_new_capacity];
        std::copy(begin(), end(), new_data);
        delete[] data;
        data = new_data;
        capacity = _new_capacity;
};

