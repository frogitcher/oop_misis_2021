#include "stack.h"
#include <stdexcept>

void stack::Realloc(int new_size)
{
    int new_capacity = capacity;
    if (new_size > size)
    {
        new_capacity *= 2;
    }
    int* new_data = new int[new_capacity];
    std::copy(data[0], data[size-1], new_data);
    delete[] data;
    data = new_data;
}

stack::stack()
    :size(0)
    , capacity(0)
    , data(nullptr)
    {
    }

stack::~stack()
{
    delete[]data;
}

int stack::Size() const
{
    return size;
}

bool stack::Empty() const
{
    return(size == 0);
}

int stack::Get() const
{
    return data[size-1];
}

int& stack::operator[](int value) const
{
    if (value == size-1)
    {
        return data[value];
    }
}

void stack::Push(int value)
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

void stack::Pop()
{
    if(size == 0)
    {
        throw std::invalid_argument("Size is emoty");
    }
    size--;
}

stack& stack::operator=(const stack& other)
{
    size = other.Size();
    std::copy(other.data, other.data + other.size, data);
    return *this;
}

bool stack::operator==(const stack& other) const
{
    if (other.Size() != size)
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

bool stack::operator!=(const stack& other) const
{
    return !(*this == other);
}