#include "dynamic_array.h"

DynamicArray::DynamicArray()
    : capacity_(0),
      size_(0),
      data_(nullptr)
{
}

DynamicArray::DynamicArray(const size_t size, const int value = 0)
    : capacity_(size),
      size_(size),
      data_(nullptr)
{
  if (size_ < 0)
    throw std::invalid_argument("Invalid size value");
  else if (size_ > 0)
  {
    data_ = new int[capacity_];
    std::fill(data_, data_ + size_, value);
  }
}

DynamicArray::DynamicArray(const DynamicArray &array)
    : capacity_(array.size_),
      size_(array.size_)
{
  data_ = new int[capacity_];
  std::copy(array.data_, array.data_ + size_, data_);
}

DynamicArray::DynamicArray(const std::initializer_list<int> &init_list)
    : capacity_(init_list.size()),
      size_(init_list.size())
{
  data_ = new int[capacity_];
  std::copy(init_list.begin(), init_list.end(), data_);
}

DynamicArray::~DynamicArray()
{
  delete[] data_;
}

int &DynamicArray::operator[](const size_t idx)
{
  if (idx >= size_)
    throw std::out_of_range("Index out of range");

  return *(data_ + idx);
}

bool DynamicArray::operator==(const DynamicArray &rhs) const
{
  return std::equal(data_, data_ + size_, rhs.data_, rhs.data_ + rhs.size_);
}

bool DynamicArray::operator!=(const DynamicArray &rhs) const
{
  return !operator==(rhs);
}

DynamicArray &DynamicArray::operator=(const DynamicArray &rhs)
{
  DynamicArray tmp(std::move(rhs));
  swap(tmp);
  return *this;
}

size_t DynamicArray::size() const
{
  return size_;
}

size_t DynamicArray::capacity() const
{
  return capacity_;
}

bool DynamicArray::empty() const
{
  return size_ == 0;
}

void DynamicArray::resize(const size_t new_size, const int value = 0)
{
  if (new_size < 0)
    throw std::invalid_argument("Invalid size value");
  else if (new_size > capacity_)
  {
    int *new_data = new int[new_size];
    std::copy(data_, data_ + size_, new_data);
    std::fill(new_data + size_, new_data + new_size, value);

    delete[] data_;
    data_ = new_data;
    capacity_ = new_size;
  }
  else if (new_size > size_)
    std::fill(data_ + size_, data_ + new_size, value);
  else
  {
    int *new_data = new int[new_size];
    std::copy(data_, data_ + new_size, new_data);

    delete[] data_;
    data_ = new_data;
  }

  size_ = new_size;
}

void DynamicArray::reserve(const size_t new_capacity)
{
  if (new_capacity > capacity_)
  {
    int *new_data = new int[new_capacity];
    std::copy(data_, data_ + size_, new_data);

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
}

void DynamicArray::shrink_to_fit()
{
  capacity_ = size_;
  resize(size_);
}

void DynamicArray::push_back(const int value)
{
  if (size_ == capacity_)
    _relocate();

  data_[size_++] = value;
}

void DynamicArray::pop_back()
{
  if (size_ == 0)
    throw std::length_error("Array is empty");

  --size_;
}

void DynamicArray::clear()
{
  size_ = 0;
}

void DynamicArray::swap(DynamicArray &array)
{
  std::swap(data_, array.data_);
  std::swap(size_, array.size_);
  std::swap(capacity_, array.capacity_);
}

void DynamicArray::erase(const size_t idx)
{
  if (idx >= size_)
    throw std::out_of_range("Index out of range");

  for (size_t pos = idx; pos < size_; ++pos)
    *(data_ + pos) = *(data_ + pos + 1);
  --size_;
}

void DynamicArray::insert(const size_t idx, const int value)
{
  if (idx > size_)
    throw std::out_of_range("Index out of range");
  else if (idx == size_)
    push_back(value);
  else
  {
    if (size_ == capacity_)
      _relocate();

    for (size_t pos = size_; pos != idx; --pos)
      *(data_ + pos) = *(data_ + pos - 1);
    *(data_ + idx) = value;
    ++size_;
  }
}

void DynamicArray::assign(const size_t size, const int value)
{
  size_ = size;
  if (capacity_ > 0)
    reserve(size_);
  else
    capacity_ = size_;

  data_ = new int[capacity_];
  std::fill(data_, data_ + size_, value);
}

void DynamicArray::assign(const std::initializer_list<int> &init_list)
{
  size_ = init_list.size();
  if (capacity_ > 0)
    reserve(size_);
  else
    capacity_ = size_;

  data_ = new int[capacity_];
  std::copy(init_list.begin(), init_list.end(), data_);
}

int &DynamicArray::at(const size_t idx)
{
  if (idx >= size_)
    throw std::out_of_range("Index out of range");

  return *(data_ + idx);
}

int *DynamicArray::begin()
{
  return data_;
}

int *DynamicArray::end()
{
  return data_ + size_;
}

void DynamicArray::_relocate()
{
  if (capacity_ == 0)
    ++capacity_;
  else
    capacity_ *= 2;

  int *new_data = new int[capacity_];
  std::copy(data_, data_ + size_, new_data);

  delete[] data_;
  data_ = new_data;
}
