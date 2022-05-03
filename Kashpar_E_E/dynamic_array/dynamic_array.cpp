#include "dynamic_array.h"
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <stddef.h>

DynamicArray::DynamicArray(size_t _size, int value) {
    size = _size;
    capacity = _size;
    data = new int[_size];
    std::fill(data, data + _size, value);
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    capacity = other.capacity;
    data = new int[other.capacity];
    std::copy(other.begin(), other.end(), data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
    size = list.size();
    capacity = list.size();
    data = new int[size];
    std::copy(list.begin(), list.end(), data);
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

size_t DynamicArray::Size() const {
    return size;
}

size_t DynamicArray::Capacity() const {
    return capacity;
}

bool DynamicArray::Empty() const {
    return size == 0;
}

int& DynamicArray::operator[](size_t i) {
    return *(data + i);
}

int& DynamicArray::at(size_t i) const {
    if (i >= size) {
        throw std::invalid_argument("DynamicArray index out of range");
    }
    else {
        return *(data + i);
    }
}

void DynamicArray::push_back(int value) {
    if (capacity == size) {
        size_t new_capacity = capacity * 2 + 1;  // ƒобавл€ем 1, чтобы не добавл€ть проверку capacity != 0
        int* new_data = new int[new_capacity];
        std::copy(data, (data + size), new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    data[size++] = value;
}

void DynamicArray::pop_back() {
    if (size == 0) {
        throw std::invalid_argument("pop_back from empty DynamicArray");
    }
    else {
        size--;
    }
}

void DynamicArray::clear() {
    size = 0;
}

void DynamicArray::erase(size_t index) {
    if (index >= size) {
        throw std::invalid_argument("DynamicArray index out of range");
    }
    else {
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
}

void DynamicArray::insert(size_t index, int value) {
    if (index > size) {
        throw std::invalid_argument("DynamicArray index out of range");
    }
    if (capacity == size) {
        size_t new_capacity = capacity * 2 + 1;  // ƒобавл€ем 1, чтобы не добавл€ть проверку capacity != 0
        int* new_data = new int[new_capacity];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

void DynamicArray::resize(size_t new_size) {
    if (new_size > capacity) {
        int* new_data = new int[new_size];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity = new_size;
    }
    size = new_size;
}

void DynamicArray::assign(size_t new_size, int value) {
    if (new_size > size) {
        int* new_data = new int[new_size];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        size_t _size = size;
        size = new_size;
        capacity = new_size;
        std::fill(data + _size, data + size, value);
    }
    else {
        resize(new_size);
    }
}

int* DynamicArray::begin() const {
    return data;
}

int* DynamicArray::end() const {
    return data + size;
}

void DynamicArray::swap(DynamicArray& other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

bool DynamicArray::operator==(const DynamicArray& other) const {
    if (size != other.size) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool DynamicArray::operator!=(const DynamicArray& other) const {
    return !(*this == other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    resize(other.Size());
    std::copy(other.begin(), other.end(), data);
    return *this;
}
