#include "Dynamic.h"
#include <stdexcept>
#include <algorithm>
#include <string>

//Array Creation
Dynamic_Array::Dynamic_Array()
	: size(0)
	, capacity(1) {
}
Dynamic_Array::~Dynamic_Array() {
	delete[]data;
}
Dynamic_Array::Dynamic_Array(size_t _size, int value) :
	size(_size),
	capacity(_size) {
		data = new int[size];
		std::fill(data, data + size, value);
}
Dynamic_Array::Dynamic_Array(const Dynamic_Array& other) :
	size(other.size),
	capacity(other.capacity) {
		data = new int[capacity];
		std::copy(other.data, other.data + other.size, data);
}
Dynamic_Array::Dynamic_Array(const std::initializer_list<int>& list): 
	size(list.size()), 
	capacity(list.size()) 
{
		data = new int[capacity];
		if (size != 0) {
			std::copy(list.begin(), list.end(), data);
		}
	}

//Actions with arrays
void Dynamic_Array::push_back(int value) {
	resize(size + 1);
	data[size - 1] = value;
}
void Dynamic_Array::pop_back()
{
	if (size == 0) {
		throw std::underflow_error("Array is empty (there is nothing to delete)!");
	}
	else {
		--size;
	}
}
void Dynamic_Array::clear()
{
	size = 0;
	capacity = 0;
}
void Dynamic_Array::erase(size_t index)
{
	if (index < 0 || index >= size) {
		throw std::out_of_range("Index is out of the range!");
	}
	for (size_t i = index; i < size - 1; ++i) {
		data[i] = data[i + 1];
	}
	--size;
}
void Dynamic_Array::insert(size_t index, int value)
{
	if (index >= size) {
		throw std::out_of_range("Index is out of the range!");
	}
	else {
		resize(size + 1);
		for (int i = size - 1; i > index; --i) {
			data[i] = data[i - 1];
		}
		data[index] = value;
	}
}
void Dynamic_Array::resize(size_t new_size)
{
	if (new_size > capacity) {
		create_data(new_size);
	}
	if (new_size > size) {
		std::fill(data + size, data + new_size, 0);
	}
	size = new_size;
}
void Dynamic_Array::assign(size_t new_size, int value)
{
		resize(new_size);
		size = new_size;
		std::fill(data, data + size, value);
}
void Dynamic_Array::swap(Dynamic_Array& other) {

	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}


//Logical functions
bool Dynamic_Array::operator==(const Dynamic_Array& other) const
{
	if (size == other.size) {
		for (int i = 0; i < size; ++i) {
			if (other.data[i] != data[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}
bool Dynamic_Array::operator!=(const Dynamic_Array& other) const
{
	return !(*this == other);
}

//Assignment
Dynamic_Array& Dynamic_Array::operator=(const Dynamic_Array other)
{
	resize(other.size);
	size = other.size;
	capacity = other.capacity;
	std::copy(other.data, other.data +other.size, data);
	return *this;
}

//Referencing
int& Dynamic_Array::at(size_t i) const {
	if (i >= size) {
		throw std::out_of_range("Index is out of the range!");
	}
	return *(data + i);
}

//private
void Dynamic_Array::reallocate(size_t new_capacity) {
	capacity = new_capacity;
	int* new_data = new int[new_capacity];
	std::copy(begin(), end(), new_data);
	delete[] data;
	data = new_data;
}
void Dynamic_Array::create_data(size_t new_size) {
	int new_capacity = new_size * 2;
	int* new_data = new int[new_capacity];
	for (int i = 0; i < size; ++i) {
		new_data[i] = data[i];
	}
	capacity = new_capacity;
	delete[]data;
	data = new_data;
}