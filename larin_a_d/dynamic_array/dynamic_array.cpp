#include "dynamic_array.h"
#include <stdexcept>

DynamicArray::DynamicArray(int64_t _size, int value)
    : size(_size)
    , capacity(_size) {
        data = new int[size];
        std::fill(begin(), end(), value);
}

DynamicArray::DynamicArray(const DynamicArray& another)
    : size(another.size)
    , capacity(another.capacity) {
        data = new int[capacity];
        std::copy(another.data, another.data + another.size, data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list)
    : size(list.size())
    , capacity(list.size()) {
        data = new int[capacity];
        std::copy(list.begin(), list.end(), data);
}

int64_t DynamicArray::Size() const {
    return size;
}

int64_t DynamicArray::Capacity() const {
    return capacity;
}

void DynamicArray::push_back(int value) {
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        }
        reallocate(size);
    }
    data[size++] = value;
}

void DynamicArray::pop_back() {
    if (size == 0) {
        throw std::length_error("The array is empty!");
    }
    size--;
}

void DynamicArray::erase(int64_t index) {
    if (size == 0) {
        throw std::length_error("The array is empty!");
    }
    if (index < 0 || index >= size) {
        throw std::out_of_range("Out of range!");
    }
    for (int64_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

void DynamicArray::resize(int64_t new_size, int value) {
    if (new_size < 0) {
        throw std::length_error("The size of the array cannot be less than zero!");
    }
    if (new_size == 0) {
        size = 0;
        return;
    }
    reallocate(new_size);
    std::fill(begin() + ((size <= new_size) ? size : 0), begin() + new_size, value);
    size = new_size;
}

void DynamicArray::assign(int64_t new_size, int value) {
    if (new_size < 0) {
        throw std::length_error("Size cannot be less than zero!");
    }
    if (new_size == 0) {
        size = 0;
        return;
    }
    reallocate(new_size);
    std::fill(begin(), begin() + new_size, value);
    size = new_size;
}

void DynamicArray::swap(DynamicArray& another) {
    std::swap(size, another.size);
    std::swap(capacity, another.capacity);
    std::swap(data, another.data);
}

void DynamicArray::insert(int64_t index, int value) {
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        }
        reallocate(size);
    }
    ++size;
    for (int64_t i = index + 1; i < size; i++) {
        data[i] = data[i - 1];
    }
    data[index] = value;
}

void DynamicArray::reallocate(int64_t new_size) {
    int64_t new_capacity = capacity;
    if (new_size > capacity) {
        new_capacity *= 2;
    }
    int* new_data = new int[new_capacity];
    std::copy(begin(), end(), new_data);
    delete[] data;
    data = new_data;
}

int& DynamicArray::at(int64_t i) const {
    if (i >= size) {
        throw std::out_of_range("Out of range!");
    }
    return *(data + i);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& rhs) {
    size = rhs.size;
    capacity = rhs.capacity;
    std::copy(rhs.data, rhs.data + rhs.size, data);
    return *this;
}

DynamicArray::~DynamicArray() {
    delete[] data;
}