#include "dyn_array.h"
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <stddef.h>

DynamicArray::DynamicArray(size_t _size, int fill_value) {
    size = _size;
    capacity = _size;
    data = new int[_size];
    std::fill(data, data + _size, fill_value);
}

DynamicArray::DynamicArray(const DynamicArray& dyn_array) {
    size = dyn_array.size;
    capacity = dyn_array.capacity;
    data = new int[dyn_array.capacity];
    std::copy(dyn_array.begin(), dyn_array.end(), data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& init_list) {
    size = init_list.size();
    capacity = init_list.size();
    data = new int[size];
    std::copy(init_list.begin(), init_list.end(), data);
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

int& DynamicArray::operator[](size_t index) {
    return *(data + index);
}

int& DynamicArray::at(size_t index) const {
    if (index >= size) {
        throw std::invalid_argument("DynamicArray index out of range");
    }
    else {
        return *(data + index);
    }
}

void DynamicArray::push_back(int push_value) {
    if (capacity == size) {
        size_t new_capacity = capacity * 2 + 1;
        int* new_data = new int[new_capacity];
        std::copy(data, (data + size), new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    data[size++] = push_value;
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
        std::copy(data + index + 1, data + size, data + index);
        size--;
    }
}

void DynamicArray::insert(size_t index, int insert_value) {
    if (index > size) {
        throw std::invalid_argument("DynamicArray index out of range");
    }
    if (capacity == size) {
        size_t new_capacity = capacity * 2 + 1;
        int* new_data = new int[new_capacity];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
    std::copy_backward(data + index, data + size, data + size + 1);
    data[index] = insert_value;
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
    for (int i = size; i < new_size; ++i) {
        data[i] = 0;
    }
    size = new_size;
}

void DynamicArray::assign(size_t new_size, int assign_value) {
    if (new_size > capacity) {
        int* new_data = new int[new_size];
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity = new_size;
    }
    for (int i = 0; i < new_size; ++i) {
        data[i] = assign_value;
    }
    size = new_size;
}

int* DynamicArray::begin() const {
    return data;
}

int* DynamicArray::end() const {
    return data + size;
}

void DynamicArray::swap(DynamicArray& other_value) {
    std::swap(size, other_value.size);
    std::swap(capacity, other_value.capacity);
    std::swap(data, other_value.data);
}

bool DynamicArray::operator==(const DynamicArray& other_dyn_array) const {
    return (size == other_dyn_array.size) && std::equal(data, data + size, other_dyn_array.begin());
}

bool DynamicArray::operator!=(const DynamicArray& other_dyn_array) const {
    return !(*this == other_dyn_array);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other_dyn_array) {
    resize(other_dyn_array.Size());
    std::copy(other_dyn_array.begin(), other_dyn_array.end(), data);
    return *this;
}