#include "dynamic.h"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <stddef.h>
#include <initializer_list>


DynamicArray::DynamicArray(size_t _size, int value)
{
	size = _size;
	capacity = _size;
	data = new int[_size];
	std::fill(begin(), end(), value);
}

DynamicArray::DynamicArray(const DynamicArray& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new int[other.capacity];
	std::copy(other.data, other.data + other.size, data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list)
{
	size = list.size();
	capacity = list.size();
	data = new int[list.size()];
	std::copy(list.begin(), list.end(), data);
}

DynamicArray::~DynamicArray()
{
	delete[] data;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
	delete[] data;
	size = other.size;
	capacity = other.capacity;
	data = new int[other.capacity];
	std::copy(other.data, other.data + other.size, data);
	return *this;
}

size_t DynamicArray::Size() const
{
	return size;
}

size_t DynamicArray::Capacity() const
{
	return capacity;
}

bool DynamicArray::Empty() const
{
	if (size == 0)
		return true;
	return false;
}

int& DynamicArray::operator[](size_t i) const
{
	return *(data + i);
}

int& DynamicArray::at(size_t i) const
{
	if (i >= size || i < 0)
		throw std::out_of_range("Index out of range");

	return *(data + i);
}

void DynamicArray::push_back(int value)
{
	if (size == capacity) {
		reallocate(capacity * 2 + 1);
	}
	data[size++] = value;
}

void DynamicArray::pop_back()
{
	if (size == 0)
		throw std::out_of_range("There is nothing to delete");
	size--;
}

void DynamicArray::erase(size_t i)
{
	for (int j = i; j < size - 1; ++j)
	{
		data[j] = data[j + 1];
	}
	size--;
}

void DynamicArray::insert(size_t i, int value)
{
	if (size == capacity)
		reallocate(capacity * 2 + 1);
	int cache = data[i];
	for (int j = i + 1; j < size + 1; ++j)
	{
		data[j] = cache;
		cache = data[j];
	}
	data[i] = value;
	size++;
}

void DynamicArray::clear()
{
	size = 0;
}

void DynamicArray::assign(int lenght, int value)
{
	DynamicArray c(lenght, value);
	*this = c;
}

void DynamicArray::resize(size_t new_size)
{
	if (new_size > capacity)
		reallocate(new_size * 2 + 1);
	size = new_size;
}

void DynamicArray::swap(DynamicArray& other)
{
	std::swap(capacity, other.capacity);
	std::swap(size, other.size);
	std::swap(data, other.data);
}

int* DynamicArray::begin() const
{
	return data;
}

int* DynamicArray::end() const
{
	return data + size;
}

bool DynamicArray::operator==(const DynamicArray& other) const
{
	if (size != other.size)
		return false;
	if (size == 0)
		return true;
	if (std::equal(begin(), end(), other.begin()))
		return true;
	return false;
}

bool DynamicArray::operator!=(const DynamicArray& other) const
{
	if (*this == other)
		return false;
	return true;
}

void DynamicArray::reallocate(size_t new_capacity)
{
	int* new_data = new int[new_capacity];
	std::copy(data, data + size, new_data);
	delete[]data;
	data = new_data;
	capacity = new_capacity;
}
