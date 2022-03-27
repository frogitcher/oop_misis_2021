#include "dynamic.h"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <stddef.h>
Dynamic_Array::Dynamic_Array(size_t _size, int value) {
	size = _size;
	capacity = _size;
	data = new int[capacity];
	if (size != 0) {
		std::fill(data, data + size, value);
	}
}
Dynamic_Array::Dynamic_Array(const Dynamic_Array& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new int[capacity];
	std::copy(other.data, other.data + other.size, data);
}
Dynamic_Array::~Dynamic_Array() {
	delete[]data;
}
const size_t Dynamic_Array::Size() const
{
	return this->size;
}
const size_t Dynamic_Array::Capacity() const
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
		std::copy(data, (data+size), new_data);
		delete[] data;
		data = new_data;
		capacity *= 2; 
	}
	else {
		size = 0;
		capacity = 1;
	}
	size+=1;
	data[size-1] = _value;
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
	//delete[] data;

	size = 0;
}
void Dynamic_Array::erase(size_t index)
{
	int* new_data = new int[capacity];
	std::copy(data, data + size, new_data);
	delete[] data;
	data = new_data;
	for (size_t i = index; i < this->Size()-1; i++) {
		data[i] = data[i + 1];
	}
	this->size--;
}
void Dynamic_Array::insert(size_t index, int num)
{
	this->size++;
	if (size == capacity) {
		capacity *= 2;
	}
	for (size_t i = this->Size() - 1; i > index; i--) {
		this[i] = this[i - 1];
	}
	this[index] = num;
}
void Dynamic_Array::assign(size_t new_size, int value)
{
	//delete[] data;
	size = new_size;
	capacity = new_size;
	data = new int[capacity];
	if (size != 0) {
		std::fill(data, data + size, value);
	}
}
Dynamic_Array& Dynamic_Array::operator=(const Dynamic_Array other)
{
	delete[] data;
	size = other.size;
	capacity = other.capacity;
	data = new int[capacity];
	for (int i = 0; i < size; i++)
		data[i] = other.data[i];
	return *this;

}
int& Dynamic_Array::operator[](size_t i) const {
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

int* Dynamic_Array::begin()
{
	return data;
}	
int* Dynamic_Array::end()
{
	return data + this->Size();
}
bool Dynamic_Array::operator==(const Dynamic_Array& other) const
{
	if (this->Size() == other.Size()) {
		if (this->Size() == 0)
			return true;
		//Dynamic_Array a(*this);
		for (int i = 0; i < std::min(this->Size(), other.Size())-1; i++) {
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
	if (this->Size() == other.Size()) {
		if (this->Size() == 0)
			return false;
		for (int i = 0; i < std::min(this->Size(), other.Size()); i++) {
			if (data[i] != other.data[i]) {
				return true;
			}
		}
		return false;
	}
	else {
		return true;
	}
}
bool Dynamic_Array::operator>=(const Dynamic_Array& other) const {
	if (*this == other) {
		return true;
	}
	else {

		for (int i = 0; i < std::min(this->Size(), other.Size()); i++) {
			if (data[i] < other.data[i]) {
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
		if (*this != other && *this > other) {
			return false;
		}
		else {
			return true;
		}
		
}
bool Dynamic_Array::operator<(const Dynamic_Array& other) const
{
	if (*this==other && *this > other) {
		return false;
	}
	else {
		return true;
	}
}
int* Dynamic_Array::Data() const
{
	return data;
}
