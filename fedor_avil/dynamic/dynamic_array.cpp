#include "dynamic.h"
#include <stdexcept>
#include <algorithm>
#include <string>
#include <stddef.h>
void DynamicArray::reallocate(size_t new_capacity) {
	int* new_data = new int[new_capacity];
	std::copy(data, data + size, new_data);
	delete[]data;
	data = new_data;
	capacity = new_capacity;
}
DynamicArray::DynamicArray(size_t _size, int value) {
	size = _size;
	capacity = _size;
	data = new int[capacity];
	std::fill(data, data + size, value);
}
DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
	size = list.size();
	capacity = list.size();
	data = new int[capacity];
	std::copy(list.begin(), list.end(), data);
}
DynamicArray::DynamicArray(const DynamicArray& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new int[capacity];
	std::copy(other.data, other.data + other.size, data);
}

DynamicArray::~DynamicArray() {
	delete[] data;
}

void DynamicArray::push_back(int _value) {
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
void DynamicArray::erase(size_t index)
{
	if (index >= size) {
		throw std::out_of_range("Index Out Of Range");
	}
	for (; index < size - 1; index++) {
		*(data + index) = *(data + index + 1);
	}
	size--;
}
void DynamicArray::insert(size_t index, int num)
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
void DynamicArray::assign(size_t new_size, int value)
{
	if (new_size >= capacity) {
		int new_capacity = 1;
		while (new_capacity < new_size) {
			new_capacity *= 2;
		}
		reallocate(new_capacity);
	}
	size = new_size;
	std::fill(data, data + size, value);
}
DynamicArray& DynamicArray::operator=(const DynamicArray other)
{
	if (other.Size() > Size()) {
		delete[]data;
		capacity = other.capacity;
		data = new int[capacity];
	}
	size = other.size;
	std::copy(other.data, (other.data + other.size), data);
	return *this;

}
int& DynamicArray::at(size_t i) const {
	if (i >= this->Size()) {
		throw std::out_of_range("Index Out Of Range");
	}
	return *(data + i);
}
void DynamicArray::swap(DynamicArray& other) {

	std::swap(this->size, other.size);
	std::swap(this->capacity, other.capacity);
	std::swap(this->data, other.data);
}
bool DynamicArray::operator==(const DynamicArray& other) const
{
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
bool DynamicArray::operator!=(const DynamicArray& other) const
{
	return !(*this == other);
}
bool DynamicArray::operator>=(const DynamicArray& other) const {
	return ((*this > other )|| *this == other);

}
bool DynamicArray::operator>(const DynamicArray& other) const
{
	for (int i = 0; i < std::min(Size(), other.Size()); ++i) {
		if (data[i] != other.data[i]) {
			return data[i] > other.data[i];
		}
	}
	return Size() > other.Size();
}
bool DynamicArray::operator<=(const DynamicArray& other) const
{
	return !(*this > other);
}
bool DynamicArray::operator<(const DynamicArray& other) const
{
	return (other>=*this);
}