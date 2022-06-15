#include <algorithm>
#include "dynamic_array.h"


DynamicArray::DynamicArray(int64_t _size, int value)
    : size(_size)
    , capacity(_size) {
        data = new int[size];
        std::fill(data, data + size, value);
}
DynamicArray::DynamicArray(const DynamicArray& other)
    : size(other.size)
    , capacity(other.capacity) {
        data = new int[other.capacity];
        std::copy(other.data, other.data + other.size, data);
}
DynamicArray::DynamicArray(const std::initializer_list<int>& list)
    : size(list.size())
    , capacity(list.size()) {
        data = new int[capacity];
        std::copy(list.begin(), list.end(), data);
}
DynamicArray::~DynamicArray() {
    delete[] data;
}
int64_t DynamicArray::Size() const
{
    return size;
}
int64_t DynamicArray::Capacity() const
{
    return capacity;
}
int* DynamicArray::GetData() const
{
    return data;
}
bool DynamicArray::Empty() const
{
   return size == 0;
}

int& DynamicArray::operator[](int64_t i) const
{
    return *(data + i);
}

 int& DynamicArray::at(int64_t i) const
 {
    if  ( i >= size || i < 0)
  {
      throw "the pointer does not match the size of the array"; 
  }
  return *(data + i);
 }

void DynamicArray::push_back(int value) 
{
    if (size == capacity) {
        reallocate(capacity*2+1);
    }
    
    data[size++] = value;
}
void DynamicArray::pop_back()
{
    if (size == 0) {
        throw "there are no elements in the array";
    }
    --size;
}
void DynamicArray::clear()
{
    size = 0;
}
void DynamicArray::erase(int64_t index)
{
    if (index < 0 || index >= size) {
        throw "the index does not match the size of the array";
    }
    for (int i = index; i < size; i++){
        data[i] = data[i+1];
    }
    size--;
}
 void DynamicArray::resize(int64_t new_size)
 {
    if (new_size < 0) {
        throw "the size of the array must be non-negative";
    }
    reallocate(new_size);
    if (size < new_size){
            for (int i = size; i < new_size; i++){
            data[i] = 0;
            }
    }
    size = new_size;
}


void DynamicArray::reallocate(int64_t new_capacity)
 {
     if (new_capacity>capacity)
     {
    capacity = new_capacity;
    int* new_data = new int[new_capacity];
    std::copy(data, data+capacity, new_data);
    delete[] data;
    data = new_data;
     }
}
void DynamicArray::assign(int64_t new_size, int value)
{
    resize(new_size);
    std:: fill(data, data+size, value);
}
  void DynamicArray::insert(int64_t index, int value)
  {
    if (index < 0  || index > size) {
        throw "the pointer does not match the size of the array"; 
    }
    resize(size + 1);
     for (int i = size-1; i > index; i--){
        data[i] = data[i-1];
    }
    data[index] = value;
  }
  void DynamicArray::swap(DynamicArray& other)
  {
    DynamicArray a(*this);
    *this=other;
    other=a;
  }

 int* DynamicArray::begin()
 {
     return data;
 }
  int* DynamicArray::end()
 {
     if (size == 0){return data;}
     return data + size;
 }
 DynamicArray& DynamicArray::operator=(const DynamicArray& other)
 {
     resize(other.size);
     std::copy(other.data, other.data + other.capacity, data);
     return *this;
 }
 bool DynamicArray::operator==(const DynamicArray& other) const
 {
     return (size == other.size && std:: equal(data, data+size, other.data, other.data + other.size));
 }
  bool DynamicArray::operator!=(const DynamicArray& other) const
 {
     return !(operator==(other));
 }