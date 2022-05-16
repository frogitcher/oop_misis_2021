//
// Created by tarasov egor on 4/15/2022.
//

#include <stdexcept>
#include "dynamicarray.h"
#include <iostream>

DynamicArray::DynamicArray(int64_t _size, int _value)
        : size(_size), capacity(_size) {
    data = new int[size];
    for (int64_t i = 0; i < size; i++) { data[i] = _value; }
}

DynamicArray::DynamicArray(const DynamicArray &other)
        :size(other.size), capacity(other.capacity){
    data = new int[other.size];
    std::copy(other.data, other.data + size, data);
}

DynamicArray::DynamicArray(const std::initializer_list<int> &list)
        : size(list.size()), capacity(list.size()) {
    data = new int[size];
    std::copy(list.begin(), list.end(), data);
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

int64_t DynamicArray::Size() const {
    return size;
}

int64_t DynamicArray::Capacity() const {
    return capacity;
}

void DynamicArray::push_back(int value) {
    if (size == capacity) {
        if (capacity == 0) capacity++;
        reallocate(capacity);
    }
    data[size++] = value;
}

void DynamicArray::pop_back() {
    if (size == 0) throw std::length_error("Array is empty");
    --size;
}

void DynamicArray::erase(int64_t index) {
    if (size == 0) throw std::length_error("Array is empty");
    if (index < 0 || index >= size) throw std::length_error("Index is out of range");
    for (uint64_t i = index; i < size; ++i) data[i] = data[i + 1];
    --size;
}

void DynamicArray::resize(int64_t new_size, int value) {
    if (new_size < 0) throw std::length_error("Size must be positive");
    if (new_size == 0) {
        size = 0;
        return;
    }
    reallocate(new_size);
    std::fill(begin() + ((size <= new_size) ? size : 0), begin() + new_size, value);
    size = new_size;
}

void DynamicArray::assign(int64_t new_size, int value) {
    if (new_size < 0) throw std::length_error("Size must be positive");
    size = new_size;
    if (size == 0) return;
    reallocate(size);
    std::fill(begin(), begin() + size, value);
}

void DynamicArray::insert(int64_t index, int value) {
    if (index < 0 || index >= size) throw std::length_error("Index is out of range");
    if (size == capacity) {
        if (capacity == 0) capacity = 1;
        reallocate(size);
    }
    size++;
    for (uint64_t i = size - 1; i > index; i--) data[i] = data[i - 1];
    data[index] = value;
}

void DynamicArray::swap(DynamicArray &other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

void DynamicArray::reallocate(int64_t new_size) {
    uint64_t new_capacity = capacity;
    if (new_size > capacity) new_capacity *= 2;
    int *new_data = new int[new_capacity];
    std::copy(begin(), end(), new_data);
    delete[] data;
    data = new_data;
}

int &DynamicArray::at(int64_t i) const {
    if (i < 0 || i >= size) throw std::length_error("Index is out of range");
    return *(data + i);
}

DynamicArray &DynamicArray::operator=(const DynamicArray &rhs) {
    size = rhs.size;
    capacity = rhs.capacity;
    delete[] data;
    std::copy(rhs.data, rhs.data + rhs.size, data);
    return *this;
}
