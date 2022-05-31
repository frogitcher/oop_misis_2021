#pragma once

#include "DinamicArray.h"
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

DynamicArray::DynamicArray(int64_t _size, int _value) : size(_size), capacity(_size)
{
    data = new int[size];
    std::fill(data, data + size, _value);
}

DynamicArray::DynamicArray(const DynamicArray &rhs) : size(rhs.size), capacity(rhs.capacity)
{
    data = new int[capacity];
    std::copy(rhs.data, rhs.data + size, data);
}

DynamicArray::DynamicArray(const std::initializer_list<int> &list) : size(list.size()), capacity(list.size())
{
    data = new int[size];
    std::copy(list.begin(), list.end(), data);
}

DynamicArray::~DynamicArray()
{
    delete[] data;
}

int *DynamicArray::begin() const
{
    return data;
}

int *DynamicArray::end() const
{
    return data + size;
}

DynamicArray &DynamicArray::operator=(const DynamicArray &rhs)
{
    if (rhs.size > capacity)
    {
        int *new_data = new int[rhs.size];
        std::copy(rhs.data, rhs.data + rhs.size, new_data);
        delete[] data;

        data = new_data;
        capacity = rhs.size;
        size = rhs.size;
    }
    else
    {
        std::copy(rhs.data, rhs.data + rhs.size, data);
        size = rhs.size;
    }

    return *this;
}

int64_t DynamicArray::Size() const
{
    return size;
}

int64_t DynamicArray::Capacity() const
{
    return capacity;
}

bool DynamicArray::Empty() const
{
    return size == 0;
}

int &DynamicArray::operator[](const int64_t index)
{
    return *(data + index);
}

void DynamicArray::push_back(int push_value)
{
    if (size == capacity)
    {
        if (capacity == 0)
            capacity++;
        reallocate(size + 1);
    }
    data[size++] = push_value;
}

void DynamicArray::reallocate(int64_t new_size)
{
    int64_t new_capacity = capacity;
    if (new_size > capacity)
    {
        new_capacity = std::max(new_capacity * 2, new_size);
    }

    int *new_data = new int[new_capacity];
    std::copy(begin(), end(), new_data);
    delete[] data;
    data = new_data;

    capacity = new_capacity;
}

void DynamicArray::pop_back()
{
    if (size == 0)
    {
        throw std::length_error("Array is empty");
    }
    --size;
}

void DynamicArray::clear()
{
    size = 0;
}

void DynamicArray::erase(int64_t index)
{
    if (size == 0)
    {
        throw std::length_error("Array is empty");
    }
    if (index < 0 || index >= size)
    {
        throw std::length_error("Index is out of range");
    }

    std::copy(data + index + 1, data + size, data + index);
    --size;
}

void DynamicArray::insert(int64_t index, int insert_value)
{
    if (index < 0 || index > size)
    {
        throw std::length_error("Index is out of range");
    }
    if (size == capacity)
    {
        if (capacity == 0)
            capacity++;
        reallocate(size + 1);
    }

    if (index == size)
    {
        push_back(insert_value);
        return;
    }

    std::copy_backward(data + index, data + size, data + size + 1);
    data[index] = insert_value;
    size++;
}

void DynamicArray::resize(int64_t new_size, int value)
{
    if (new_size < 0)
    {
        throw std::length_error("Size must not be negative");
    }
    if (new_size == 0)
    {
        size = 0;
        return;
    }
    reallocate(new_size);
    if (new_size > size)
    {
        std::fill(begin() + size, begin() + new_size, value);
    }
    size = new_size;
}

void DynamicArray::assign(int64_t new_size, int value)
{
    if (new_size < 0)
    {
        throw std::length_error("Size must not be negative");
    }
    if (new_size == 0)
    {
        size = 0;
        return;
    }
    reallocate(new_size);
    std::fill(begin(), begin() + new_size, value);
    size = new_size;
}

void DynamicArray::swap(DynamicArray &other)
{
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

int &DynamicArray::at(int64_t index) const
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index is out of range");
    }
    return *(data + index);
}

bool DynamicArray::operator==(const DynamicArray &other) const
{
    return std::equal<int *, int *>(data, data + size, other.data);
}

bool DynamicArray::operator!=(const DynamicArray &other) const
{
    return !(*this == other);
}
