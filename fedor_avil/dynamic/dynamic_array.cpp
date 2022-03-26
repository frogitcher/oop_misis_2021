#include "dynamic.h"
#include <stdexcept>
#include <algorithm>
#include <string>
Dynamic_Array::Dynamic_Array(size_t _size, int value) {
	size = _size;
	capacity = _size;
	data = new int[_size];
	std::fill(data, data + size, value);
}
Dynamic_Array::Dynamic_Array(const Dynamic_Array& other)
{
	size = other.Size();
	capacity = other.Capacity();
	data = other.Data();
}
Dynamic_Array::~Dynamic_Array() {
	delete[]data;
}
size_t Dynamic_Array::Size() const
{
	return this->size;
}
size_t Dynamic_Array::Capacity() const
{
	return this->capacity;
}
bool Dynamic_Array::Empty() const {
	if (size == 0) return true;
	else return false;
}
void Dynamic_Array::push_back(int _value) {
	if (size == capacity && capacity!=0) {
		int* new_data = new int[capacity * 2];
		std::copy(this->begin(), this->end(), new_data);
		delete[] data;
		data = new_data;
		capacity *= 2; 
	}
	data[size++] = _value;
}
void Dynamic_Array::pop_back()
{
	if (size == 0) {
		throw std::underflow_error("Array Size <0");
	}
	else {
		this->size--;

	}
}
void Dynamic_Array::clear()
{
	delete[] data;
	size = 0;
}
void Dynamic_Array::erase(size_t index)
{
	for (size_t i = index; i < this->Size()-1; i++) {
		this[i] = this[i + 1];
	}
	this->size--;
}
void Dynamic_Array::insert(size_t index, int num)
{
	this->size++;

	for (size_t i = this->Size() - 1; i > index; i--) {
		this[i] = this[i-1];
	}
	this[index] = num;
}
void Dynamic_Array::assign(size_t new_size, int value)
{
	*this = Dynamic_Array(new_size, value);
}
Dynamic_Array& Dynamic_Array::operator=(Dynamic_Array other)
{
	this->swap(other);
	return *this;
}
int& Dynamic_Array::operator[](size_t i) const {
	if (i >= this->Size()) {
		throw std::out_of_range("Index Out Of Range");
	}
	return *(data + i);
}
void Dynamic_Array::swap(Dynamic_Array& other) {
	std::swap(this->data, other.data);
	std::swap(this->size, other.size);
	std::swap(this->capacity, other.capacity);
}

int* Dynamic_Array::begin()
{
	return data;
}	
int* Dynamic_Array::end()
{
	return data+this->Size();
}
bool Dynamic_Array::operator==(Dynamic_Array& other) const
{
	if (this->Size() == other.Size()) {
		Dynamic_Array a = *this;
		for (int i = 0; i < std::min(this->Size(), other.Size()); i++) {
			if (a[i] != other[i]) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}
bool Dynamic_Array::operator!=(Dynamic_Array& other) const
{
	if (this->Size() == other.Size()) {
		Dynamic_Array a = *this;
		for (int i = 0; i < std::min(this->Size(), other.Size()); i++) {
			if (a[i] != other[i]) {
				return true;
			}
		}
		return false;
	}
	else {
		return true;
	}
}
bool Dynamic_Array::operator>=(Dynamic_Array& other) const {
	if (*this == other) {
		return true;
	}
	else {
		Dynamic_Array a = *this;
		for (int i = 0; i < std::min(this->Size(), other.Size()); i++) {
			if (a[i] < other[i]) {
				return false;
			}
		}
		if (this->Size() < other.Size() && a[this->Size() - 1] == other[this->Size() - 1]) {
			return false;
		}
		else {
			return true;
		}
	}
}
bool Dynamic_Array::operator>(Dynamic_Array& other) const
{
	if (*this == other) {
		return false;
	}
	else {
		Dynamic_Array a = *this;
		for (int i = 0; i < std::min(this->Size(), other.Size()); i++) {
			if (a[i] < other[i]) {
				return false;
			}
		}
		if (this->Size() < other.Size() && a[this->Size() - 1] == other[this->Size() - 1]) {
			return false;
		}
		else {
			return true;
		}
	}
}
bool Dynamic_Array::operator<=(Dynamic_Array& other) const {
{
	if (*this == other) {
		return true;
	}
	else {
		Dynamic_Array a = *this;
		for (int i = 0; i < std::min(this->Size(), other.Size()); i++) {
			if (a[i] > other[i]) {
				return false;
			}
		}
		if (this->Size() < other.Size() && a[this->Size() - 1] == other[this->Size() - 1]) {
			return true;
		}
		else {
			return false;
		}
	}
}
}
bool Dynamic_Array::operator<(Dynamic_Array& other) const
{
	if (*this==other) {
		return false;
	}
	else {
		Dynamic_Array a = *this;
		for (int i = 0; i < std::min(this->Size(), other.Size()); i++) {
			if (a[i] > other[i]) {
				return false;
			}
		}
		if (this->Size() < other.Size() && a[this->Size() - 1] == other[this->Size() - 1]) {
			return true;
		}
		else {
			return false;
		}
	}
}
int* Dynamic_Array::Data() const
{
	return data;
}

