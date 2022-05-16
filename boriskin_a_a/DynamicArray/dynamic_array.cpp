#include "dynamic_array.h"
#include <stdexcept>

DynamicArray::DynamicArray()
  : _size(0)
  , _capacity(0)
  , _data(nullptr) 
{
}

DynamicArray::DynamicArray(size_t size, int value)
  : _size(size) 
  , _capacity(size)
  , _data(nullptr) 
{
  _data = new int [_capacity];
  for (int i=0; i<size; ++i)
  {
    _data[i] = value;
  }
}

DynamicArray::DynamicArray(const DynamicArray& other)
  : _size (other._size)
  , _capacity (other._capacity)
{
  _data = new int[_size];
  std::copy(other._data, other._data+other._size, _data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list)
  : _size(list.size())
  , _capacity(list.size())
{
  _data = new int[_size];
  std::copy(list.begin(), list.end(), _data);
}

DynamicArray::~DynamicArray()
{
  delete[] _data;
}
  

size_t DynamicArray::Size() const
{
  return _size;
}

size_t DynamicArray::Capacity() const
{
  return _capacity;
}

bool DynamicArray::Empty() const
{
  return _size == 0;
}

void DynamicArray::push_back(int value)
{
  if(_size == _capacity)
    remapmemory(_size*2);
  _data[_size++] = value;
}

void DynamicArray::pop_back()
{
  if (_size<1)
  {
    throw std::invalid_argument("you can not delete element because size is too small");
  }
  _size--;

}
void DynamicArray::clear()
{
  _size = 0;
}

void DynamicArray::erase(size_t index)
{
  for (int k=index; k<_size-1; ++k)
  {
    _data[k] = _data[k+1];
  }
  _size--;
}

void DynamicArray::remapmemory(size_t new_size)
{
  _capacity = new_size;
  int* new_data = new int[_capacity];
  std::copy(_data, _data + _size, new_data);
  delete[] _data;
  _data = new_data;
}

void DynamicArray::resize(size_t new_size, int value )
{
  if (_size >= new_size)
  {
    _size = new_size;
  }
  else
  {
    if(new_size > _capacity)
    {
      remapmemory(new_size);
    }
    for(int i = _size; i < new_size; ++i)
    {
      _data[i] = value;
    }
    _size = new_size;
  }
}


void DynamicArray::insert(size_t index, int value)
{
  if (_size == _capacity)
  {
    remapmemory(_size*2);
  }

  for (int k=_size-1; k>=index; --k)
  {
    _data[k+1] = _data[k];
  }
  _data[index] = value;
  _size++;
}

void DynamicArray::swap(DynamicArray& other)
{
  std::swap(_data, other._data);
  std::swap(_size, other._size);
  std::swap(_capacity, other._capacity);
}


int* DynamicArray::begin() 
{
  return _data;
}

int* DynamicArray::end()
{
  return _data+_size;
}

int& DynamicArray::At(size_t i) const
{
  if (i >= _size) 
  {
      throw std::invalid_argument("your size is bigger than size of array");
  }
  return _data[i];
}


int& DynamicArray::operator[](size_t i) const
{
    return _data[i];
}

DynamicArray& DynamicArray::operator=(const DynamicArray& rhs)
{
  resize(rhs._size);
  std::copy(rhs._data, rhs._data + rhs._size, _data);
  return *this;
}


bool DynamicArray::operator==(const DynamicArray& rhs) const
{
  if (_size != rhs.Size())
  {
    return false;
  }
  for (int i=0; i<=_size; ++i)
  {
    if (_data[i] != rhs._data[i])
    {
      return false;
    }
  }
  return true;
}

bool DynamicArray::operator!=(const DynamicArray& rhs) const
{
  return !(*this == rhs);
}