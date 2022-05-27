#include "darrey.h"
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <stddef.h>









darrey::darrey(size_t lenght, int value)
{
	size = lenght;
	capacity = lenght;
	data = new int[lenght];
	std::fill(data, data + lenght, value);
}

darrey::darrey(const darrey& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new int[other.size];
	std::copy(other.data, other.data + other.size, data);
}

darrey::darrey(const std::initializer_list<int>& list)
{
	size = list.size();
	capacity = list.size();
	data = new int[capacity];
	std::copy(list.begin(), list.end(), data);
}

darrey::~darrey()
{
	delete[] data;
}

int& darrey::operator[](const size_t i) const  
{
	return *(data + i);
}

int& darrey::at(const size_t i) const
{
	if (i >= size)
	{
		throw std::invalid_argument("dynamicarray index out of range");
	}
	else
	{
		return *(data + i);
	}
}

int* darrey::begin() const
{
	return data;
}

int* darrey::end() const
{
	return (int*)(data + size);
}

void darrey::push_back(const int value)
{
	if (size == capacity)
	{
		reallocate();
	}
	data[size++] = value;
}

void darrey::pop_back()
{
	if (size == 0) {
		throw std::out_of_range("Array Size <0");
	}
	else {
		size--;
	}
}

void darrey::clear()
{
	size = 0;
}

void darrey::erase(size_t i)
{
	if (i >= size) {
		throw std::out_of_range("Index Out Of Range");
	}
	for (; i < --size; i++) {
		*(data + i) = *(data + i + 1);
	}
	
}

void darrey::resize(const size_t new_size)
{
	if (new_size > capacity)
	{
		reallocate(new_size);
	}
	size = new_size;
}

void darrey::assign(const size_t new_size, const int value)
{
	if (new_size > capacity)
	{
		reallocate(new_size);
	}
	size = new_size;
	std::fill(begin(), end(), value);
}

void darrey::swap(darrey& other)
{
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}

void darrey::insert(const size_t i, const int value)
{
	push_back(0);
	if (i >= size) {
		throw std::out_of_range("Index Out Of Range");
	}
	for (size_t j = size - 1; j > i; --j) {
		data[j] = data[j - 1];
	}
	data[i] = value;
}

darrey& darrey::operator=(const darrey& other) //darrey& 
{
	delete[] data;
	data = new int[other.size];
	size = other.size;
	capacity = size;
	std::copy(other.begin(), other.end(), begin());
	return *this;
}

bool darrey::operator==(const darrey& other) const
{
	if (size == other.size)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (*(data + i) != *(other.data + i))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool darrey::operator!=(const darrey& other) const
{
	return !(*this == other);
}





size_t darrey::getsize() const
{
	return size;
}

size_t darrey::getcapacity() const
{
	return capacity;
}

bool darrey::empty() const
{
	return bool(size);
}

void darrey::reallocate(size_t new_capacity)
{
	if (new_capacity == 0)
	{
		capacity += capacity + 1;
		int* new_data = new int[capacity];
		std::copy(begin(), end(), new_data);
		delete[] data;
		data = new_data;
	}
	else
	{
		capacity = new_capacity;
		int* new_data = new int[capacity];
		std::copy(begin(), end(), new_data);
		delete[] data;
		data = new_data;
	}
}
