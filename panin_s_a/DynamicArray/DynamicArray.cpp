#include "DynamicArray.h"
#include <stdexcept>

DynamicArray::DynamicArray() : size(0), capacity(8)
{
    data = new int[16]{};
};

DynamicArray::DynamicArray(int length, int value = 0) : size(length), capacity(length) {
    if (length < 0)
        throw std::invalid_argument("size must not be negative");
    data = new int[length];
    std::fill(data, data + length, value);
};

DynamicArray::DynamicArray(const DynamicArray& other) {
    data = other.Get_data();
    size = other.Size();
    capacity = other.Capacity();
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
    int l = list.size();
    data = new int[l];
    size = l;
    capacity = l;
    int i = 0;
    for (auto item : list) {
        data[i] = item;
        ++i;
    }
}

DynamicArray::~DynamicArray() {
    delete[]data;
}

int DynamicArray::Size() const {
    return size;
}
int DynamicArray::Capacity() const {
    return capacity;
}

bool DynamicArray::Empty() const {
    return (size == 0);
}

int& DynamicArray::operator[](int i) {
    return *(data + i);
}

int& DynamicArray::At(int i) const {
    if (i >= size)
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
        capacity*= 2+1;
    }
    data[size++] = value;
}


void DynamicArray::Clear() {
    size = 0;
}

void DynamicArray::Erase(int index) {
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
        data[size -1] = 0;
        size--;
    }
}

void DynamicArray::Insert(int index, int val) {
    if (index < 0 || index > size) {
        throw std::out_of_range("index out of range");
    }
    Push_back(0);
    for (int p = size-1; p > index; p--) {
        data[p] = data[p - 1];
    }
    data[index] = val;
}

void DynamicArray::Assign(int new_size, int val) {
    if (new_size < 0) {
        throw std::length_error("array size must not be negative");
    }
    (*this) = DynamicArray(new_size, val);
}

void DynamicArray::Resize(int new_size, int val) {
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
    for (int i = 0; i < std::min(size, other.size); i++) {
        if (data[i] != other.data[i])
            return false;
    }
    return true;
}

bool DynamicArray::operator !=(const DynamicArray& other) const {
    return !(*this == other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    // data = other.Get_data();
    data = new int[other.capacity]{};
    std::copy(other.data, other.data + other.size, data);
    size = other.Size();
    capacity = other.Capacity();
    return *this;
}

int* DynamicArray::Get_data() const {
    return data;
}

