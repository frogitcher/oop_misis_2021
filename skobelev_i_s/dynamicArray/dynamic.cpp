#include "dynamic.h"
#include <stdexcept>
#include <algorithm>

size_t DynamicArray::Size() const{
    return size;
}
size_t DynamicArray::Capacity() const{
    return capacity;
}
bool DynamicArray::Empty() const{
    return size == 0;
}

DynamicArray::DynamicArray (size_t length, int value) {
    size = length;
    capacity = length;
    data = new int[size];
    std::fill(data, data + size, value);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
    size = list.size();
    capacity = list.size();
    data = new int[list.size()];
    std::copy(list.begin(), list.end(), data);
}

DynamicArray::DynamicArray (DynamicArray& other) {
    size = other.Size();
    capacity = other.Capacity();
    data = new int[other.capacity];
    std::copy(other.data, other.data + other.size, data);
}

DynamicArray::~DynamicArray () {
    delete[] data;
}

int& DynamicArray::operator[](size_t i) const {
    return *(data + i);
}

int& DynamicArray::at(size_t i) const {
    if (i >= Size()) {
        throw std::out_of_range("index out of range");
    } else {
        return *(data + i);
    }
}

void DynamicArray::Push_back(int value) {
    if (size == capacity) {
        int* newData = new int[capacity*2];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        capacity *= 2;
    }
    data[size++] = value;
}

void DynamicArray::Pop_back() {
    if (size == 0) {
        throw std::out_of_range("The array is empty");
    } else {
        size--;
    }
}

void DynamicArray::Clear() {
    size = 0;
}

void DynamicArray::Erase(size_t index) {
    std::copy(data + index + 1, data + size, data + index);
    size--;
}

void DynamicArray::Resize(size_t newSize) {
    if (newSize <= 0) {
        throw std::out_of_range("The new size should be at least 1");
    } else if (newSize > capacity) {
        int* newData = new int[newSize];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        std::fill(data + size, data + newSize, 0);
        size = newSize;
        capacity = newSize;
    } else if (newSize > size) {
        std::fill(data + size, data + newSize, 0);
        size = newSize;
    } else {
        size = newSize;
    }
}

void DynamicArray::Assign(size_t newSize, int value) {
    if (newSize <= 0) {
        throw std::out_of_range("The new size should be at least 1");
    } else if (newSize > capacity) {
        int* newData = new int[newSize];
        delete[] data;
        data = newData;
        std::fill(data, data + newSize, value);
        capacity = newSize;
        size = newSize;
    } else {
        std::fill(data, data + newSize, value);
        size = newSize;
    }
}

void DynamicArray::Insert(size_t index, int value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("index out of range");
    } else if (size == capacity) {
        int* newData = new int[capacity * 2];
        std::copy(data, data + index, newData);
        newData[index] = value;
        std::copy(data + index, data + capacity, newData + index + 1);
        delete[] data;
        data = newData;
        size++;
        capacity *= 2;
    } else {
        std::copy_backward(data + index, data + size, data + index + 1);
        data[index] = value;
        size++;
    }
}

int* DynamicArray::begin() const{
    return data;
}

int* DynamicArray::end() const{
    return data + size;
}

void DynamicArray::Swap(DynamicArray& other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

bool DynamicArray::operator==(const DynamicArray& other) const{
    if (size == other.Size()) {
        return std::equal(other.data, other.data + other.Size(), data, data + size);
    } else {
        return false;
    }
}
bool DynamicArray::operator!=(const DynamicArray& other) const{
    return !(*this == other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (other.Size() > capacity) {
        int* newData = new int[other.Size()];
        std::copy(other.data, other.data + other.Size(), newData);
        delete[] data;
        data = newData;
        size = other.Size();
        capacity = other.Size();
    } else {
        std::copy(other.data, other.data + other.Size(), data);
        size = other.Size();
    }
    return *this;
}