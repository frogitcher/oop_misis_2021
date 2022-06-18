#include <stdexcept>
#include <initializer_list>
#include <cstddef>
#include "dynamic_array.h"

using namespace std;

DynamicArray::DynamicArray() {
    capacity = 1;
    size = 0;
    data = new int[capacity];
}


DynamicArray::DynamicArray(const size_t size, const int value) {
    this->size = size;
    this->capacity = size;
    data = new int[size];
    fill(data, data + size, value);
}

DynamicArray::DynamicArray(const DynamicArray &copy) {
    size = copy.size;
    capacity = copy.capacity;
    data = new int[size];
    std::copy(copy.data, copy.data + size, data);
}

DynamicArray::DynamicArray(const std::initializer_list<int> &list) {
    size = list.size();
    capacity = list.size();
    data = new int[capacity];
    copy(list.begin(), list.end(), data);
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

//operators

int &DynamicArray::operator[](const size_t index) const {
    if (index >= size) throw out_of_range("Index out of range.");
    return data[index];
}


DynamicArray &DynamicArray::operator=(const DynamicArray &rhs) {
    this->resize(rhs.size);
    copy(rhs.data, rhs.data + rhs.size, data);

    return *this;
}

bool DynamicArray::operator==(const DynamicArray &rhs) const {
    if (size != rhs.size) return false;
    for (size_t i = 0; i < size; i++) {
        if ((*this)[i] != rhs[i]) {
            return false;
        }
    }

    return true;
}

bool DynamicArray::operator!=(const DynamicArray &rhs) const {
    return !(*this == rhs);
}


void DynamicArray::resize(const size_t newSize) {
    if (newSize < 0) throw invalid_argument("Size can't be less than zero.");
    if (newSize <= capacity) {
        size = newSize;
    } else {
        reallocate(newSize);
    }
}

void DynamicArray::resize(const std::size_t newSize, const int &value) {
    if (newSize < 0) throw invalid_argument("Size can't be less than zero.");
    if (newSize > capacity) {
        size_t prevSize = size;
        reallocate(newSize);
        fill(data + prevSize, data + size, value);
    } else {
        if (newSize > size)
            fill(data + size, data + newSize, value);
        size = newSize;
    }
}


void DynamicArray::reallocate(const std::size_t newSize) {
    while (capacity < newSize) capacity *= 2;
    int *newData = new int[capacity];
    copy(data, data + size, newData);

    // clear old memory
    delete[] data;
    size = newSize;
    data = newData;
}

void DynamicArray::insert(const size_t index, const int &value) {
    if (index > size) throw out_of_range("Index out of range.");

    resize(size + 1);
    for (size_t i = size - 1; i > index; --i) {
        (*this)[i] = (*this)[i - 1];
    }

    (*this)[index] = value;
}

void DynamicArray::erase(const size_t index) {
    if (index > size) throw out_of_range("Index out of range.");
    for (size_t i = index; i < size - 1; ++i) {
        (*this)[i] = (*this)[i + 1];
    }

    this->resize(size - 1);
}

void DynamicArray::push_back(const int &value) {
    resize(size + 1, value);
}

void DynamicArray::pop_back() {
    if (Empty()) throw invalid_argument("Array is empty.");
    resize(size - 1);
}

void DynamicArray::swap(DynamicArray &copy) {
    std::swap(data, copy.data);
    std::swap(size, copy.size);
    std::swap(capacity, copy.capacity);
}

void DynamicArray::assign(const size_t newSize, const int &value) {
    resize(newSize);
    fill(data, data + size, value);
}

void DynamicArray::assign(const initializer_list<int> &list) {
    resize(list.size());
    copy(list.begin(), list.end(), data);
}

int *DynamicArray::begin() const {
    return data;
}

int *DynamicArray::end() const {
    return data + size;
}

void DynamicArray::clear() {
    size = 0;
}

size_t DynamicArray::Size() const {
    return size;
}

size_t DynamicArray::Capacity() const {
    return capacity;
}


int& DynamicArray::at(const size_t index) const {
    if (index >= size) throw out_of_range("Index out of range.");
    return (*this)[index];
}

bool DynamicArray::Empty() const {
    return size == 0;
}