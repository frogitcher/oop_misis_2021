#include "dynamic.h"
#include <iostream>
#include <stdexcept>


DynamicArray::DynamicArray(int64_t _size, int value)
	:size(_size)
	,capacity(_size){
		data = new int[size];
		std::fill(data, data + size, value);
}
DynamicArray::DynamicArray(const DynamicArray& other)
	:size(other.size)
	, capacity(other.size) {
	data = new int[capacity];
	std::copy(other.data, other.data + other.size, data);
}
DynamicArray::DynamicArray(const std::initializer_list<int>& list)
	: size(list.size())
	, capacity(list.size()) {
		data = new int[capacity];
		std::copy(list.begin(), list.end(), data);
}
DynamicArray::~DynamicArray() {
	delete[] data;
}
int64_t DynamicArray::Size() const {
	return size;
}
int64_t DynamicArray::Capacity() const {
	return capacity;
}
int* DynamicArray::GetData() const {
	return data;
}
bool DynamicArray::Empty() const { 
	return size == 0;
}
int& DynamicArray::operator[] (int64_t i) const {
	return *(data + i);
}
int& DynamicArray::at(int64_t i) const {
	if (i >= Size()) {
		throw std::out_of_range("Index is Out of range");
	}
	return *(data + i);
}
void DynamicArray::reallocate(int64_t new_capacity) {
	int* new_data = new int[new_capacity];
	std::copy(data, data + size, new_data);
	delete[] data;
	capacity = new_capacity;
	data = new_data;
}

void DynamicArray::push_back(int value) {
	if (size == capacity) {
		if (capacity == 0) capacity++;
		reallocate(capacity);
	}
	data[size++] = value;
}

void DynamicArray::pop_back() {
	if (size == 0) {
		throw std::out_of_range("Out of range");
	}
	size--;
}

void DynamicArray::clear() {
	size = 0;
}

void DynamicArray::erase(int64_t index) {
	if (index >= size || index < 0) {
		throw std::out_of_range("Out of range");
	}
	for (int64_t i = index; i < size - 1; ++i) {
		data[i] = data[i + 1];
	}
	size--;
}

void DynamicArray::resize(int64_t new_size) {
	if (new_size < 0) {
		throw std::invalid_argument("The size is negative");
	}
	if (new_size == 0) {
		size = 0; return;
	}
	reallocate(new_size);
	std::fill(begin() + ((size <= new_size) ? size : 0),begin() + new_size, 0);
	size = new_size;
}

void DynamicArray::assign(int64_t new_size, int value) {
	if (new_size < 0) {
		throw std::invalid_argument("The size can't be below 0");
	}
	*this = DynamicArray(new_size, value);
}

int* DynamicArray::end() {
	return data + size - 1;
}

int* DynamicArray::begin() {
	return data;
}

void DynamicArray::swap(DynamicArray& other) {
	for (int i = 0; i < size; i++) {
		int t = data[i];
		data[i] = other.data[i];
		other.data[i] = t;
	}
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);


}

void DynamicArray::insert(int64_t index, int value) {
	if (index < 0 || index >= size) {
		throw std::out_of_range("Out of range");
	}
	resize(size + 1);
	for (int i = size - 1; i > index; --i) {
		data[i] = data[i - 1];
	}
	data[index] = value;
}


bool DynamicArray:: operator == (const DynamicArray& rhs) const {
	if (size != rhs.size) return false;
	for (int64_t i= 0; i < size; i++) {
		if (data[i] != rhs.data[i]) return false;
	}
	return true;
}
bool DynamicArray::operator!=(const DynamicArray& rhs) const {
	return!(*this == rhs);
}
DynamicArray& DynamicArray:: operator = (const DynamicArray& other){
	size = other.size;
	capacity = other.capacity;
	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[i];
	}
	return *this;

}





