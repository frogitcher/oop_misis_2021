#include "dynamic.h"
#include <stdexcept>
#include <initializer_list>

DynamicArray::DynamicArray(int64_t length, int value)
    : size(length)
    , capacity(length)
    {
        data = new int[length];
        std::fill(data,data + size,value);
    }
DynamicArray::DynamicArray (const DynamicArray& other)
    : size(other.size)
    , capacity (other.capacity)
     {
            int *_data=new int[capacity];
            std::copy(other.data,other.data+size,_data);
     }
DynamicArray::DynamicArray(const std::initializer_list <int> list)
    : size(list.size())
    , capacity(list.size())
    {
        data=new int[size];
        std::copy(list.begin(),list.end(),data);
    }
DynamicArray::~DynamicArray()
{
    delete[] data;
}
int64_t DynamicArray::Size()
{
    return size;
}
int64_t DynamicArray::Capacity()
{
    return capacity;
}
bool DynamicArray::Empty() const
{
    return (size==0);
}
int& DynamicArray::operator[](int64_t i) const
{
    return *(data+i);
}
bool DynamicArray::operator==(const DynamicArray& other) const
{
    if (size!=other.size)
    {
        return 0;
    }
    for (int i=0;i<size;i++)
    {
        if (data[i]!= other[i])
        {
            return 0;
        }
    }
    return 1;
}
bool DynamicArray::operator!=(const DynamicArray& other) const
{
    return !(*this==other);
}
DynamicArray& DynamicArray::operator=(const DynamicArray& other)
 {
     resize(other.size);
     std::copy(other.data, other.data + other.capacity, data);
     return *this;
 }
int& DynamicArray::at(int64_t i) const
{
    if(i>=size)
    {
        throw std::length_error("index out of range");
    }
    return *(data+i);
}
void DynamicArray::push_back(int value)
{
    resize(++size);
    data[size-1]=value;
}
void DynamicArray::pop_back()
{
    if (size==0)
    {
        throw std::length_error("Array is empty");
    }
    --size;
}
void DynamicArray::clear()
{
    size = 0;
}
void DynamicArray::erase(int64_t i)
{
    if (i>size)
    {
        throw std::length_error("Index is out of range");
    }
    std::copy(data + i + 1, data + size, data + i);
    --size;
}
void DynamicArray::resize(int64_t _size)
{
    if (_size<0)
    {
        throw std::length_error("size must be > 0");
    }
    if (_size ==0)
    {
        size=_size;
        return;
    }
    reallocate(_size);
    if (size < _size){
            for (int i = size; i < _size; i++){
            data[i] = 0;
            }
    }
    size = _size;
}
void DynamicArray::reallocate(int64_t _capacity)
{
    {
         if (_capacity>capacity)
         {
            capacity = _capacity;
            int* _data = new int[_capacity];
            std::copy(data, data+capacity, _data);
            delete[] data;
            data = _data;
         }
    }
}
void DynamicArray::insert(int64_t i,int value)
{
    if (i > size || i < 0)
    {
        throw std::length_error("index doesn't match the array's size");
    }
    ++size;
    for (int j = size - 1; j > i; j--)
    {
        data[j]=data[j-1];
    }
    data[i]=value;
}
void DynamicArray::swap(DynamicArray& other)
{
    std::swap(data,other.data);
    std::swap(capacity,other.capacity);
    std::swap(size,other.size);
}
void DynamicArray::assign(int64_t _size, int value)
{
    if (_size<0)
    {
        throw std::length_error("size must be > 0");
    }
    if (_size==0)
    {
        size = 0;
        return;
    }
    std::fill(begin(),begin()+_size, value);
    size=_size;
}
int* DynamicArray::begin()
{
    return data;
}
int* DynamicArray::end()
{
    return data+size;
}
