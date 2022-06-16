#include "dynamic_array.h"
#include <algorithm>
#include <stdexcept>

DynamicArray::DynamicArray(int64_t _size, int value)
    : size(_size)
    , capacity(_size) {
    data = new int[size];
    std::fill(data, data + size, value);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list) 
    : size(list.size())
    , capacity(list.size()) {
    data = new int[list.size()];
    std::copy(list.begin(), list.end(), data);
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : size(other.size)
    , capacity(other.capacity) {
    data = new int[other.size];
    std::copy(other.data, other.data + other.capacity, data);
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

int& DynamicArray::operator[](int64_t i) const {
    return *(data + i);
}

int& DynamicArray::at(int64_t i) const {
    if (i >= Size()) {
        throw std::out_of_range("Index is out of range");
    }
    return *(data + i);
}

int64_t DynamicArray::Size() const {
    return size;
}

int64_t DynamicArray::Capacity() const {
    return capacity;
}

bool DynamicArray::empty() const {
    return size == 0;
}

void DynamicArray::push_back(int value) {
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        }
        int* new_data = new int[capacity*2];
        std::copy(data, data + capacity, new_data);
        delete[] data;
        data = new_data;
        capacity *= 2;
    }
    data[size++] = value;
}

void DynamicArray::pop_back() {
    if (size == 0) {
        throw std::out_of_range("The size is equal to zero");
    }
    else {
        --size;
    }
}

void DynamicArray::clear() {
    size = 0;
}

void DynamicArray::erase(int64_t index) {
    std::copy(data + index + 1, data + size, data + index);
    size--;
}

void DynamicArray::resize(int64_t new_size) {
    if (new_size <= 0) {
        throw std::invalid_argument("The size must be a positive number");
    }
    else if (new_size > capacity) {
        int* new_data = new int[new_size];
        std::copy(data, data + capacity, new_data);
        delete[] data;
        data = new_data;
        std::fill(data + capacity, data + new_size, 0);
        capacity = new_size;
        size = new_size;
    }
    else if (new_size > size) {
        std::fill(data + size, data + new_size, 0);
        size = new_size;
    }
    else {
        size = new_size;
    }
}

void DynamicArray::assign(int64_t new_size, int value) {
    if (new_size <= 0) {
        throw std::invalid_argument("The size must be a positive number");
    }
    else if (new_size > capacity) {
        capacity = new_size;
        int* new_data = new int[capacity];
        delete[] data;
        data = new_data;
        std::fill(data, data + new_size, value);
        size = new_size;
    }
    else {
        size = new_size;
        std::fill(data, data + size, value);
    }
}

void DynamicArray::insert(int64_t index, const int value) {
    if (size + 1 > capacity) {
        if (capacity == 0) {
            capacity = 1;
        }
        int* new_data = new int[capacity * 2];
        std::copy(data, data + index, new_data);
        new_data[index] = value;
        std::copy(data + index, data + capacity, new_data + index + 1);
        delete[] data;
        data = new_data;
        capacity *= 2;
        size++;
    }
    else {
        std::copy(data + index - 1, data + size, data + index);
        data[index] = value;
        size++;
    }
}

void DynamicArray::swap(DynamicArray& other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

int* DynamicArray::begin() {
    return data;
}

int* DynamicArray::end() {
    return data + size;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& rhs) {
    if (rhs.size > capacity) {
        int* new_data = new int[rhs.size];
        std::copy(rhs.data, rhs.data + rhs.size, new_data);
        delete[] data;
        data = new_data;
        capacity = rhs.size;
        size = rhs.size;
    }
    else{
        std::copy(rhs.data, rhs.data + rhs.size, data);
        size = rhs.size;
    }
    return *this;
}

bool DynamicArray::operator==(const DynamicArray& rhs) const {
    return std::equal(rhs.data, rhs.data + rhs.size, data, data + size);
}

bool DynamicArray::operator!=(const DynamicArray& rhs) const {
    return !operator==(rhs);
}