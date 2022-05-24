#include "dynamic_array.h"

void dynamic_array::Realloc(size_t new_size)
{
    int new_capacity = capacity;
    while (new_size >= new_capacity)
    {
        new_capacity *= 2;
    }
    int* new_data = new int[new_capacity];
    std::copy(begin(), end(), new_data);
    delete[] data;
    data = new_data;
}

dynamic_array::dynamic_array()
    : size(0)
    , capacity(0)
    , data(nullptr)
    {}

dynamic_array::dynamic_array(int size, int value)
    : size(size)
    , capacity(size * 2)
    , data(nullptr)
    {
        if (size < 0)
        {
            throw std::invalid_argument("size of array can't be < 0!");
        }
        else
        {
            data = new int[size * 2];
            for(int i = 0; i < size; i++)
            {
                data[i] = value;
            }
        }
    }

dynamic_array::dynamic_array(const dynamic_array& other)
    : size(other.size)
    , capacity(other.capacity)
    , data(nullptr)
 {
    data = new int[size];
    for(int i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

dynamic_array::dynamic_array(const std::initializer_list<int>& input_list)
    : size(input_list.size())
    , capacity(input_list.size())
{
    data = new int[size];
    std::copy(input_list.begin(), input_list.end(), data);
}

dynamic_array::~dynamic_array()
{
    delete[] data;
}

size_t dynamic_array::Size() const
{
    return size;
}


size_t dynamic_array::Capacity() const
{
    return capacity;
}

bool dynamic_array::empty() const
{
    return(size == 0);
}

int& dynamic_array::at(int value) const
{
    if (value >= size)
    {
        throw std::out_of_range("Index out of range!");
    }
    return data[value];
}

int& dynamic_array::operator[](size_t value) const
{
    if (value >= size)
    {
        throw std::out_of_range("Index out of range!");
    }
    return data[value];
}

void dynamic_array::Push_back(int value)
{
    if (size == capacity)
    {
        if (capacity == 0)
        {
            capacity = 1;
        }
        Realloc(size);
    }
    data[size++] = value;
}

void dynamic_array::Pop_back()
{
    if(size == 0)
    {
        throw std::invalid_argument("Size is empty!");
    }
    size--;
}

void dynamic_array::Clear()
{
    size = 0;
}

void dynamic_array::Erase(size_t index)
{
    if(size == 0)
    {
        throw std::invalid_argument("Array is empty");
    }
    if(index >= size || index < 0)
    {
        throw std::out_of_range("Index out if range!");
    }
    for(int i = index; i < size-1; i++)
    {
        data[i] = data[i+1];
    }
    size--;
}

void dynamic_array::Resize(size_t new_size, int value)
{
    if (new_size <= size)
    {
        size = new_size;
    }
    else
    {
        if (new_size > size)
        {
            Realloc(new_size);
        }
        for (int i = size; i < new_size; i++)
        {
            data[i] = value;
        }
        size = new_size;
    }
}   

void dynamic_array::insert(size_t index, int value)
{
    if (size == capacity)
    {
        if (capacity == 0)
        {
            capacity = 1;
        }
        Realloc(size);
    }
    size++;
    for(int i = index+1; i < size; i++)
    {
        data[i] = data[i-1];
    }
    data[index] = value;
}

void dynamic_array::swap(dynamic_array& other)
{
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

int* dynamic_array::begin()
{
    return data;
}

int* dynamic_array::end()
{
    return data + size;
}

dynamic_array& dynamic_array::operator=(const dynamic_array& other)
{
    size = other.size;
    capacity = other.capacity;
    std::copy(other.data, other.data + other.size, data);
    return *this;
}

bool dynamic_array::operator==(const dynamic_array& other) const
{
    if (other.size != size)
    {
        return false;
    }
    for(int i = 0; i < size; i++)
    {
        if(data[i] != other[i])
        {
            return false;
        }
    }
    return true;
}

bool dynamic_array::operator!=(const dynamic_array& other) const
{
    return !(*this == other);
}