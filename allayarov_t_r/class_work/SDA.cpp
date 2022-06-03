#include "SDA.h"

#include <iostream>

SDA::SDA()
    : capacity_(0),
      size_(0),
      data_(nullptr)
{
}

SDA::SDA(const size_t size, const int &value)
    : capacity_(size),
      size_(size)
{
  data_ = new int[capacity_];
  std::fill(data_, data_ + size_, value);
}

SDA::SDA(const SDA &other)
    : capacity_(other.size_),
      size_(other.size_)
{
  data_ = new int[capacity_];
  std::copy(other.Begin(), other.End(), data_);
}

SDA::~SDA()
{
  delete[] data_;
}

SDA &SDA::operator=(const SDA &rhs)
{
  SDA temp(std::move(rhs));
  Swap(temp);
  return temp;
}

bool SDA::operator==(const SDA &rhs) const
{
  return std::equal(data_, data_ + size_, rhs.data_, rhs.data_ + rhs.size_);
}

bool SDA::operator!=(const SDA &rhs) const
{
  return !(operator==(rhs));
}

size_t SDA::Size() const
{
  return size_;
}

bool SDA::Empty() const
{
  return size_ == 0;
}

int SDA::Get() const
{
  return *(data_ + size_);
}

void SDA::Push(const int &value)
{
  if (size_ == capacity_)
  {
    size_t new_capacity = capacity_ == 0 ? capacity_ + 1 : 2 * capacity_;
    int *new_data = new int[new_capacity];
    std::copy(data_, data_ + size_, new_data);

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }

  *(data_ + size_++) = value;
}

void SDA::Pop()
{
  --size_;
}

void SDA::Swap(SDA &rhs)
{
  std::swap(capacity_, rhs.capacity_);
  std::swap(size_, rhs.size_);
  std::swap(data_, rhs.data_);
}

int *SDA::Begin() const
{
  return data_;
}

int *SDA::End() const
{
  return data_ + size_;
}
