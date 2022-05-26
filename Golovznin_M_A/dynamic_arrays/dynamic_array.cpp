#include "dynamic_array.h"
#include <stdexcept>

// конструкторы

DynamicArray::DynamicArray(int64_t _size, int value = 0)
        : size(_size) {
    data = new int[size];
    std::fill(data, data + size, value);
    capacity = _size;
}

DynamicArray::DynamicArray(const DynamicArray &other) {
    change_array(other.data, other.size);
}

DynamicArray::DynamicArray(const std::initializer_list<int> &list) {
    data = new int[list.size()];
    std::copy(list.begin(), list.end(), data);
    size = list.size();
    capacity = size * 2;
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

// геттеры

int64_t DynamicArray::getSize() const {
    return size;
}

int64_t DynamicArray::getCapacity() const {
    return capacity;
}

int *DynamicArray::getData() const {
    return data;
}

bool DynamicArray::empty() const {
    return size == 0;
}

// методы

void DynamicArray::push_back(int value) {
    int *new_data = new int[size + 1];
    std::copy(data, data + size, new_data);
    new_data[size] = value;

    change_array(new_data, size + 1);
}

void DynamicArray::pop_back() {
    if (empty()) {
        throw std::length_error("Array is empty");
    }

    change_array(data, size - 1);
}

void DynamicArray::clear() {
    change_array(data, 0);
}

void DynamicArray::erase(int64_t index) {
    if (size == 0) {
        throw std::length_error("Array is empty");
    }
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index was outside of bounds of an array");
    }
    int *new_data = new int[size - 1];
    int x = 0;
    for (int i = 0; i < getSize(); ++i) {
        if (i != index) {
            new_data[x++] = getData()[i];
        }
    }
    change_array(new_data, size - 1);
}


void DynamicArray::resize(int64_t new_size) {
    if (new_size < size) {
        change_array(data, new_size);
    } else {
        int *new_data = new int[new_size];
        std::fill(new_data + size, new_data + new_size, 0);

        change_array(new_data, new_size);
    }
}

void DynamicArray::assign(int64_t new_size, int value) {
    if (new_size < 0) {
        throw std::length_error("Array length can't be negative");
    }

    int *new_data = new int[new_size];

    for (int i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }

    std::fill(new_data + size, new_data + new_size, value);

    change_array(new_data, new_size);
}

void DynamicArray::insert(int64_t index, int value) {
    if (index > size || index < 0) {
        throw std::out_of_range("Index was outside of bounds of an array");
    } else if (index == size) {
        push_back(value);
    } else {
        int *new_data = new int[size + 1];
        int x = 0;
        for (int i = 0; i <= getSize(); ++i) {
            if (i == index) {
                new_data[x++] = value;
            }
            new_data[x++] = getData()[i];
        }
        change_array(new_data, size + 1);
    }

}

void DynamicArray::swap(DynamicArray &other) {
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

int &DynamicArray::at(int64_t i) const {
    if (i >= getSize() || i < 0) {
        throw std::out_of_range("Index was outside of bounds of an array");
    }
    return *(data + i);
}

// указатели

int *DynamicArray::begin() const {
    return data;
}

int *DynamicArray::end() const {
    return data + size;
}

// операторы

int &DynamicArray::operator[](int64_t i) const {
    return *(data + i);
}

DynamicArray &DynamicArray::operator=(const DynamicArray &rhs) {
    if (this == &rhs) {
        return *this;
    }

    int* newData = new int[rhs.size];
    std::copy(rhs.data, rhs.data + rhs.size, newData);
    delete data;
    data = newData;

    if(rhs.size > capacity) {
        capacity = rhs.size * 2;
    }

    size = rhs.size;

    return *this;
}

bool DynamicArray::operator==(const DynamicArray &rhs) const {
    if (size != rhs.getSize()) { return false; }

    std::equal(data, data + size, rhs.data);

    return true;
}

bool DynamicArray::operator!=(const DynamicArray &rhs) const {
    return !(*this == rhs);
}

// внутренние методы

void DynamicArray::change_array(int *new_data, int64_t new_size) {
    if (capacity == 0) {
        capacity = 1;
    }

    capacity = new_size * 2;

    int *tmp_data = new int[capacity];
    std::copy(new_data, new_data + new_size, tmp_data);

    delete[] data;
    data = tmp_data;
    size = new_size;
}


