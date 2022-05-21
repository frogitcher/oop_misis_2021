#include "DynamicArray.h"
#include <stdexcept>

DynamicArray::DynamicArray() : size(0), capacity(8)
{
    data = new int[8]{};
};

DynamicArray::DynamicArray(std::size_t length, int value = 0) : size(length), capacity(length) {
    if (length < 0)
        throw std::invalid_argument("size must not be negative");
    data = new int[length];
    std::fill(data, data + length, value);
};

DynamicArray::DynamicArray(const DynamicArray& other) {
    *this = other;
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
    int l = list.size();
    data = new int[l];
    size = l;
    capacity = l;
    int i = 0;
    std::copy(list.begin(), list.end(), data);
}

DynamicArray::~DynamicArray() {
    delete[]data;
}

std::size_t DynamicArray::Size() const {
    return size;
}
std::size_t DynamicArray::Capacity() const {
    return capacity;
}

bool DynamicArray::Empty() const {
    return (size == 0);
}

int& DynamicArray::operator[](int i) const {
    return *(data + i);
}

int& DynamicArray::At(int i) const {
    if (i >= size || i < 0)
        throw std::out_of_range("index out of range");
    else
        return *(data + i);
}

void DynamicArray::Push_back(int value) {
    if (size == capacity) {
        int* new_data = new int[2*capacity + 1];
        std::copy(data, data + capacity, new_data);
        delete[]data;
        data = new_data;
        capacity*= 2;
        capacity++;
    }
    data[size++] = value;
}


void DynamicArray::Clear() {
    size = 0;
}

void DynamicArray::Erase(std::size_t index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("index out of range");
    }
    else {
        for (int i = index; i < size-1; ++i) {
            data[i] = data[i+1];
        }
        --size;
    }
}

void DynamicArray::Pop_back()
{
    if (size != 0)
    {
        size--;
    }
    else
    {
        throw std::length_error("trying pop_back from empty vector");
    }
}

void DynamicArray::Insert(std::size_t index, int val) {
    if (index < 0 || index > size) {
        throw std::out_of_range("index out of range");
    }
    Push_back(0);
    for (int p = size-1; p > index; p--) {
        data[p] = data[p - 1];
    }
    data[index] = val;
}

void DynamicArray::Assign(std::size_t new_size, int val) {
    if (new_size < 0) {
        throw std::length_error("array size must not be negative");
    }
    if (new_size > capacity)
    {
        delete[] data;
        data = new int[new_size];
        std::fill(data, data + new_size, val);
        size = new_size;
        capacity = new_size;
    }
    else
    {
        std::fill(data, data + new_size, val);
        size = new_size;
    }
}

void DynamicArray::Resize(std::size_t new_size, int val) {
    if (new_size < 0) {
        throw std::length_error("array size must not be negative");
    }
    for (int i = size; i < new_size; i++) {
        Push_back(val);
    }
    size = new_size;
}

int* DynamicArray::Begin() const{
    return data;
}

int* DynamicArray::End() const{
    return data + size;
}

void DynamicArray::Swap(DynamicArray& other) {
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}

bool DynamicArray::operator ==(const DynamicArray& other) const {
    if (size != other.size) {
        return false;
    }
    return std::equal(data, data + size, other.data);
    return true;
}

bool DynamicArray::operator !=(const DynamicArray& other) const {
    return !(*this == other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (capacity < other.size)
    {
        delete[] data;
        data = new int[other.capacity]{};
    }
    std::copy(other.data, other.data + other.size, data);
    size = other.Size();
    capacity = other.Capacity();
    return *this;
}

int* DynamicArray::Get_data() const {
    return data;
}

