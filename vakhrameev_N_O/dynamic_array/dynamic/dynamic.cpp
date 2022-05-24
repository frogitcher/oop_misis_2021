#include "class_dynamic_array.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
Dynamic_array::Dynamic_array(size_t n, int value)
{
    size = n;
    capacity = n * 2;
    data = new int[capacity];
    std::fill(data, data + size, value);
}

Dynamic_array::Dynamic_array(const Dynamic_array& other)
{
    size = other.size;
    capacity = other.size;
    int* new_data=new int[capacity];
    std::copy(other.data, other.data+size, new_data);
    data=new_data;
}

Dynamic_array::~Dynamic_array() {
    delete[] data;
}
Dynamic_array::Dynamic_array(const std::initializer_list<int>& other)
{
    size = other.size();
    capacity = other.size() * 2;
    data = new int[other.size() * 2];
    std::copy(other.begin(), other.end(), data);
}

int& Dynamic_array:: operator[](size_t i)
{
    return *(data + i);
}

size_t Dynamic_array::Capacity() const
{
    return capacity;
}

size_t Dynamic_array::Size() const
{
    return size;
}

bool Dynamic_array::Empty() const
{
    if (size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Dynamic_array::push_back(int value)
{
    resize(++size);
    data[size - 1] = value;
}

void Dynamic_array::resize(size_t new_size)
{
    if (new_size == 0)
    {
        size = new_size;
        return;
    }
    reallocate(new_size);
    if (size < new_size)
    {
        for (int i = size;i < new_size;i++)
        {
            data[i] = 0;
        }
    }
    size = new_size;

}
void Dynamic_array::reallocate(size_t new_capacity)
{
    if (new_capacity > capacity)
    {
        capacity = new_capacity;
        int* new_data = new int[new_capacity];
        std::copy(data, data + capacity, new_data);
        delete[] data;
        data = new_data;
    }
}
void Dynamic_array::pop_back()
{
    if (size != 0)
    {
        data[--size] = 0;
    }
    else
    {
        throw std::range_error("Dynamic array has no elements!");
    }
}

void Dynamic_array::assign(size_t n, int value)
{
    size = n;
    capacity = n * 2;
    data = new int[n * 2];
    std::fill(data, data + n, value);
}
void Dynamic_array::clear()
{
    delete[] data;
    size = 0;
}

void Dynamic_array::erase(size_t i)
{
    if (i < size)
    {
        for (int j = i;j < size - 1;j++)
        {
            data[j] = data[j + 1];
        }
        size--;
    }
    else
    {
        throw std::logic_error("impossible to erase element that is out of array range");
    }
}

int* Dynamic_array::begin() const
{
    return data;
}

int* Dynamic_array::end() const
{
    return data + size;
}

void Dynamic_array::swap(Dynamic_array& other)
{
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

bool Dynamic_array::operator==(const Dynamic_array& other) const
{
    if (size != other.size)
    {
        return false;
    }
    for (int i = 0;i < size;i++)
    {
        if (data[i] != other.data[i])
        {
            return false;
        }
    }
    return true;
}

Dynamic_array& Dynamic_array::operator=(const Dynamic_array& other)
{
    resize(other.size);
    std::copy(other.data, other.data + other.capacity, data);
    return *this;
}

bool Dynamic_array::operator!=(const Dynamic_array& other) const
{
    return !(Dynamic_array(*this)==other);
}

bool Dynamic_array::operator>=(const Dynamic_array& other) const
{
    for (int i = 0;i < std::min(other.size, size);i++)
    {
        if (data[i] == other.data[i])
        {
            continue;
        }
        if (data[i] >= other.data[i])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return size >= other.size;
}

bool Dynamic_array::operator<=(const Dynamic_array& other) const
{
    for (int i = 0;i < std::min(other.size, size);i++)
    {
        if (data[i] == other.data[i])
        {
            continue;
        }
        if (data[i] <= other.data[i])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return size <= other.size;
}

bool Dynamic_array::operator>(const Dynamic_array& other) const
{
    return !(Dynamic_array(*this) <= other);
}

bool Dynamic_array::operator<(const Dynamic_array& other) const
{
    return !(Dynamic_array(*this) >= other);
}
std::ostream& operator<<(std::ostream &os,Dynamic_array &other)
{
    for (int i=0;i<other.Size();i++)
    {
        os<<other[i]<<" ";
    }
    return os;
}
