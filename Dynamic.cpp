#include "Dynamic.h"
#include <stdexcept>
#include <algorithm>

DynamicArray::DynamicArray() {
	size = 0;
	capacity = 0;
	data = nullptr;
}
DynamicArray::DynamicArray(size_t _size, int value) {
	size = _size;
	capacity = _size;
	delete[] data;
	data = new int[size];
	std::fill(data, data + _size, value);
};
DynamicArray::DynamicArray(const DynamicArray& other) {
	size = other.size;
	capacity = size;
	delete[] data;
	data = new int[size];
	std::copy(other.data, other.data + other.size, this->begin());
}
DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
	size = list.size();
	capacity = size;
	delete[] data;
	data = new int[size];
	std::copy(list.begin(), list.end(), this->begin());
}
DynamicArray::~DynamicArray() {
	delete[] data;
}

size_t DynamicArray::getSize() const {
	return size;
}
size_t DynamicArray::getCapacity() const {
	return capacity;
}
bool DynamicArray::empty() const {
	if (size == 0) {
		return true;
	}
	return false;
}

int& DynamicArray::operator[](size_t i) const {
	return *(data + i);
}
bool DynamicArray::operator==(const DynamicArray& other) const {
	if (size == other.size) {
		return std::equal(data, data + size, other.data);
	}
	return false;
}
int& DynamicArray::at(size_t i) const {
	if (i >= size) {
		throw std::invalid_argument("Array out of bounds");
	}
	else {
		return *(data + i);
	}
}

void DynamicArray::push_back(int value) {
	if (size == capacity) {
		if (capacity == 0) {
			capacity = 1;
		}
		else {
			capacity *= 2;
		}
		int* new_data = new int[capacity];
		std::copy(data, data + size, new_data);
		delete[] data;
		data = new_data;
	}
	data[size++] = value;
}
void DynamicArray::pop_back() {
	if (size == 0) {
		throw std::invalid_argument("Array is empty");
	}
	else {
		size--;
	}
}
void DynamicArray::clear() {
	size = 0;
}
void DynamicArray::erase(size_t index) {
	if (index >= size) {
		throw std::invalid_argument("Array out of bounds");
	}
	else {
		std::copy(data + index + 1, data + size, data + index);
		size--;
	}
}
void DynamicArray::insert(size_t index, int value) {
	this->push_back(value);
	std::copy_backward(data + index, data + size, data + size + 1);
	data[index] = value;
}

void DynamicArray::resize(size_t new_size) {
	if (new_size != size) {
		int* new_data = new int[new_size];
		if (new_size > capacity) {
			std::copy(data, data + size, new_data);
			delete[] data;
			data = new_data;
		}
		else {
			if (new_size > size) {
				for (int i = size; i < new_size; i++) {
					data[i] = 0;
				}
			}
		}
		size = new_size;
	}
}
void DynamicArray::assign(size_t new_size, int value) {
	this->resize(new_size);
	std::fill(data, data + size, value);
}

int* DynamicArray::begin() const{
	return data;
}
int* DynamicArray::end() const{
	return data + size;
}

void DynamicArray::swap(DynamicArray& other) {
	std::swap(data, other.data);
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
}

void DynamicArray::operator=(const DynamicArray& other) {
	if (other.size > capacity) {
		int* new_data = new int[other.size];
		delete[] data;
		data = new_data;
		capacity = other.size;
	}
	size = other.size;
	std::copy(data, data + size, other.data);
}