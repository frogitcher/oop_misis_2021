#include<iostream>
#include "DynamicArray.h"
#include <stdexcept>
#include <vector>

DynamicArray::DynamicArray() {
	data = nullptr;
}

DynamicArray::~DynamicArray() {
	delete[] data;
}

DynamicArray::DynamicArray(size_t length, int value) {
	size = length;
	capacity = size * 2;
	data = new int[capacity];
	for (int i = 0; i < size; i++)
		data[i] = value;
}

DynamicArray::DynamicArray(const DynamicArray& other) {
	size = other.size;
	capacity = other.capacity;
	data = new int[capacity];
	for (int i = 0; i < other.Size(); i++)
		data[i] = other[i];
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
	size = list.size();
	capacity = size * 2;
	data = new int[capacity];
	std::copy(list.begin(), list.end(), data);
}

size_t DynamicArray::Size() const {
	return size_t(size);
}

size_t DynamicArray::Capacity() const {
	return size_t(capacity);
}

bool DynamicArray::Empty() const {
	if (size == 0) return true;
	else
		return false;
}

void DynamicArray::push_back(int value) {
	if (size == capacity) {
		int new_size = size + 1;
		int new_capacity = new_size * 2;
		int* new_data = new int[new_capacity];
		for (int i = 0; i < size; i++)
			new_data[i] = data[i];
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}
	data[size++] = value;
}

int& DynamicArray::at(size_t i)const {
	if (i >= Size()){
		throw std::invalid_argument("exception - Index more then size of array");
	}
	else if (i < 0) {
		throw std::invalid_argument("exception - Index must be more then zero");
	}
	else
		return *(data + i);
}

int& DynamicArray::operator[](size_t i) const {
	if (i >= Size()) {
		throw std::out_of_range("exception - Index more then size of array");
	}
	else if (i < 0) {
		throw std::invalid_argument("exeption - Index must be more then zero");
	}
	return *(data + i);
}

void DynamicArray::pop_back() {
	if (size == 0)
		throw std::logic_error("Size equal zero");
	else {
		data[size--] = 0;
	}
}

int* DynamicArray::begin() {
	return data;
}

int* DynamicArray::end() {
	if (size == 0) return data;
	return data + (size - 1);
}

void DynamicArray::clear() {
	delete[] data;
	size = 0;
	capacity = 0;
	data = nullptr;
}

void DynamicArray::erase(size_t index) {
	if (index > size) {
		throw std::invalid_argument("exception - index more then size");
	}
	else {
		for (int i = index; i < (size - 1); i++)
			data[i] = data[i + 1];

		data[size - 1] = 0;
		size--;
	}
}

void DynamicArray::resize(size_t new_size) {
	if (new_size < size) {
		int new_capacity = new_size * 2;
		int* new_data = new int[new_capacity];
		for (int i = 0; i < new_size; i++)
			new_data[i] = data[i];
		delete[] data;
		data = new_data;
		size = new_size;
		capacity = new_capacity;
	}
	else if (new_size > size) {
		int new_capacity = new_size * 2;
		int* new_data = new int[new_capacity];
		for (int i = 0; i < new_size; i++) {
			if (i < size) new_data[i] = data[i];
			else new_data[i] = 0;
		}
		delete[] data;
		data = new_data;
		size = new_size;
		capacity = new_capacity;
	}
}

bool DynamicArray::operator==(const DynamicArray& other) const {
	if (size != other.size) return false;
	else {
		for (int i = 0; i < size; i++) {
			if (data[i] != other[i]) return false;
		}
		return true;
	}
}

bool DynamicArray::operator!=(const DynamicArray& other) const {
	return !(*this == other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	delete[] data;
	data = new int[other.capacity];
	size = other.size;
	capacity = other.capacity;
	for (int i = 0; i < other.size; i++)
		data[i] = other[i];
	return *this;
}

void DynamicArray::assign(size_t new_size, int value) {
	delete[] data;
	size = new_size;
	capacity = 2 * size;
	data = new int[capacity];
	for (int i = 0; i < size; i++)
		data[i] = value;
}

void DynamicArray::swap(DynamicArray& other) {
	int* temp = data;
	int size_tmp = size;
	int capacity_tmp = capacity;
	data = other.data;
	size = other.size;
	capacity = other.capacity;
	other.data = temp;
	other.capacity = capacity_tmp;
	other.size = size_tmp;
}