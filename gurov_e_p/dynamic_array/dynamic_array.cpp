#include "dynamic_array.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

DynamicArray::DynamicArray(int64_t _size, int value)
    : size(_size)
    , capacity(_size) {
        data = new int[size];
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
    , capacity(list.size()) {
        data = new int[capacity];
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

bool DynamicArray::Empty() const {
    return size == 0;
}

int* DynamicArray::GetData() const {
    return data;
}

void DynamicArray::push_back(int value) {
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        }
        reallocate(capacity * 2);
    }
    data[size++] = value;
}

void DynamicArray::pop_back() {
    if (size == 0) {
        throw std::length_error("Array is empty!");
    }
    --size;
}

void DynamicArray::clear() {
    size = 0;
}

void DynamicArray::erase(int64_t index) {
    if (size == 0) {
        throw std::length_error("Array is empty!");
    }
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index is out of range!");
    }
    int* new_data = new int[capacity];
    std::copy(begin(), begin() + index, new_data);
    std::copy(begin() + index + 1, end(), new_data + index);
    delete[] data;
    data = new_data;
    --size;
}

void DynamicArray::resize(int64_t new_size, int value) {
    if (new_size < 0) {
        throw std::length_error("Length can't be negative!");
    }
    if (new_size == 0) {
        size = 0;
        return;
    }
    int64_t new_capacity = new_size * 2;
    reallocate(new_capacity);
    std::fill(begin() + ((size <= new_size) ? size : 0), begin() + new_size, value);
    size = new_size;
}

void DynamicArray::assign(int64_t new_size, int value) {
    if (new_size < 0) {
        throw std::length_error("Length can't be negative!");
    }
    *this = DynamicArray(new_size, value);
}

void DynamicArray::insert(int64_t index, int value) {
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        }
        reallocate(capacity * 2);
    }
    ++size;
    for (int64_t i = 0; i < size; ++i) {
        if (i > index) {
            data[i] = data[i - 1];
        }
    }
    data[index] = value;
}

void DynamicArray::swap(DynamicArray& other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

void DynamicArray::reallocate(int64_t new_capacity) {
    capacity = new_capacity;
    int* new_data = new int[new_capacity];
    std::copy(begin(), end(), new_data);
    delete[] data;
    data = new_data;
}

int* DynamicArray::begin() {
    return data;
}

int* DynamicArray::end() {
    return data + size;
}

int& DynamicArray::operator[](int64_t i) const {
    return *(data + i);
}

int& DynamicArray::at(int64_t i) const {
    if (i >= size) {
        throw std::out_of_range("Index is out of range!");
    }
    return *(data + i);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& rhs) {
    size = rhs.size;
    capacity = rhs.capacity;
    std::copy(rhs.data, rhs.data + rhs.size, data);
    return *this;
}

bool DynamicArray::operator==(const DynamicArray& rhs) const{
    if (size != rhs.size) {
        return false;
    }
    for (int64_t i = 0; i < size; ++i) {
        if (data[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

bool DynamicArray::operator!=(const DynamicArray& rhs) const{
    return !(*this == rhs);
}
