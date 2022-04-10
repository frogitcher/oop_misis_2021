#include "dynamic.h"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <stddef.h>
void Dynamic_Array::reallocate(size_t new_capacity) {
	int* new_data = new int[new_capacity];
	std::copy(data, data + size, new_data);
	delete[]data;
	data = new_data;
	capacity = new_capacity;
}
Dynamic_Array::Dynamic_Array(size_t _size, int value) {
	size = _size;
	capacity = _size;
	data = new int[capacity];
	std::fill(data, data + size, value);
}
Dynamic_Array::Dynamic_Array(const std::initializer_list<int>& list) {
	size = list.size();
	capacity = list.size();
	data = new int[capacity];
	std::copy(list.begin(), list.end(), data);
}
Dynamic_Array::Dynamic_Array(const Dynamic_Array& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new int[capacity];
	std::copy(other.data, other.data + other.size, data);
}

/*Dynamic_Array::~Dynamic_Array() {
	delete[] data;
}*/

const size_t Dynamic_Array::Size() const
{
	return this->size;
}
const size_t Dynamic_Array::Capacity() const
{
	return this->capacity;
}
bool Dynamic_Array::Empty() const {
	return size == 0;
}
void Dynamic_Array::push_back(int _value) {
	if (size == capacity) {
		size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
		int* new_data = new int[new_capacity];
		std::copy(data, (data + size), new_data);
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}
	
	size += 1;
	data[size - 1] = _value;
}
void Dynamic_Array::resize(size_t new_size) {
	if (new_size < 0) {
		throw std::out_of_range("Size can't be negative");
	}
	if (new_size >= capacity) {
		int new_capacity = 1;
		while (new_capacity < new_size) {
			new_capacity *= 2;
		}
		reallocate(new_capacity);
	}
	size = new_size;
}
void Dynamic_Array::pop_back()
{
	if (size == 0) {
		throw std::out_of_range("Array Size <0");
	}
	else {
		this->size--;
	}
}
void Dynamic_Array::clear()
{
	delete[]data;
	size = 0;
}
void Dynamic_Array::erase(size_t index)
{
	if (index >= size) {
		throw std::out_of_range("Index Out Of Range");
	}
	for (; index < size - 1; index++) {
		*(data + index) = *(data + index + 1);
	}
	size--;
}
void Dynamic_Array::insert(size_t index, int num)
{
	push_back(0);
	if (index > size - 1) {
		throw std::out_of_range("Index Out Of Range");
	}
	for (size_t i = this->Size() - 1; i > index; i--) {
		data[i] = data[i - 1];
	}
	data[index] = num;
}
void Dynamic_Array::assign(size_t new_size, int value)
{
	resize(new_size);
	std::fill(data, data + size, value);
}
Dynamic_Array& Dynamic_Array::operator=(const Dynamic_Array other)
{
	if (other.Size() > Size()) {
		delete[]data;
		capacity = other.capacity;

	}
	size = other.size;
	data = new int[capacity];
	std::copy(other.data, (other.data + other.size), data);
	return *this;

}
inline int& Dynamic_Array::operator[](size_t i) const {return *(data + i);}
int& Dynamic_Array::at(size_t i) const {
	if (i >= this->Size()) {
		throw std::out_of_range("Index Out Of Range");
	}
	return *(data + i);
}
void Dynamic_Array::swap(Dynamic_Array& other) {

	std::swap(this->size, other.size);
	std::swap(this->capacity, other.capacity);
	std::swap(this->data, other.data);
}

int* Dynamic_Array::begin() const
{
	return data;
}
int* Dynamic_Array::end() const
{
	return data + Size();
}
bool Dynamic_Array::operator==(const Dynamic_Array& other) const
{
	//return (std::equal(this->begin(),this->end(),other.begin(),other.end()));
	if (this->Size() == other.Size()) {
		if (size == 0)
			return true;
		for (int i = 0; i < Size() - 1; i++) {
			if (data[i] != other.data[i]) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}
bool Dynamic_Array::operator!=(const Dynamic_Array& other) const
{
	return !(*this == other);
}
bool Dynamic_Array::operator>=(const Dynamic_Array& other) const {
	return ((*this > other )|| *this == other);

}
bool Dynamic_Array::operator>(const Dynamic_Array& other) const
{
	if (*this == other) {
		return false;
	}
	else {
		for (int i = 0; i < std::min(this->Size(), other.Size()); i++) {
			if (data[i] < other.data[i])
			{
				return false;
			}
		}
		if (this->Size() < other.Size() && this[this->Size() - 1] == other[this->Size() - 1]) {
			return false;
		}
		else {
			return true;
		}
	}
}
bool Dynamic_Array::operator<=(const Dynamic_Array& other) const
{
	return (*this == other || (other > *this));
}
bool Dynamic_Array::operator<(const Dynamic_Array& other) const
{
	return (other>=*this);
}
int* Dynamic_Array::Data() const
{
	return data;
}