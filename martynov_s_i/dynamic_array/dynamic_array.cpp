#include "dynamic_array.h"
#include <initializer_list>
#include <vector>

void DynamicArray::Create(size_t oth_size, size_t oth_capacity, int* oth_data) {
	int* new_data = new int[oth_capacity];
	std::copy(oth_data, oth_data + oth_size, new_data);
	delete[] data;
	data = new_data;
	size = oth_size;
	capacity = oth_capacity;
}

DynamicArray::DynamicArray(size_t _size, int value) {
	size = _size;
	capacity = _size;
	data = new int[_size];
	std::fill(data, data + _size, value);
}

DynamicArray::DynamicArray(const DynamicArray& other) {
	Create(other.size, other.capacity, other.data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
	int* new_data = new int[list.size()];
	std::copy(list.begin(), list.end(), new_data);
	data = new_data;
	size = list.size();
	capacity = list.size();
}

DynamicArray::~DynamicArray() {
	delete[] data;
}

size_t DynamicArray::Size() const {
	return size;
}

size_t DynamicArray::Capacity() const {
	return capacity;
}

void DynamicArray::push_back(int value) {
	resize(++size);
	data[size - 1] = value;
}

void DynamicArray::pop_back() {
	if (size == 0) {
		throw "size 0";
	}
	resize(--size);
}

void DynamicArray::clear() {
	size = 0;
}

void DynamicArray::erase(size_t index) {
	if (size == 0 || index >= size) {
		throw "size 0 or index out";
	}
	std::copy(data + index + 1, data + size, data + index);
	--size;
}

void DynamicArray::insert(size_t index, int value) {
	if (index > size) {
		throw "index out";
	}
	resize(++size);
	for (size_t i = index; i < size; ++i) {
		std::swap(data[i], value);
	}
}

void DynamicArray::resize(size_t new_size) {
	if (new_size > capacity) {
		capacity = std::max(new_size, size * 2);
		int* new_data = new int[capacity];
		std::copy(data, data + size, new_data);
		if (new_size > size) {
			std::fill(new_data + size, new_data + new_size, 0);
		}
		delete[] data;
		data = new_data;
	}
	else {
		if (new_size > size) {
			std::fill(data + size, data + new_size, 0);
		}
	}
	size = new_size;
}

void DynamicArray::assign(size_t new_size, int value) {
	if (capacity >= new_size) {
		std::fill(data, data + new_size, value);
	}
	else {
		int* new_data = new int[new_size];
		std::fill(new_data, new_data + new_size, value);
		delete[] data;
		data = new_data;
		capacity = new_size;
	}
	size = new_size;
}

void DynamicArray::swap(DynamicArray& other) {
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}

int* DynamicArray::begin() const {
	return data;
}

int* DynamicArray::end() const {
	return data + size;
}

int& DynamicArray::at(size_t index) const {
	if (index >= size) {
		throw "index out";
	}
	return (*this)[index];
}

int& DynamicArray::operator[](size_t index) const {
	return *(data + index);
}

bool DynamicArray::empty() const {
	return size == 0;
}

bool DynamicArray::operator==(const DynamicArray& other) const {
	return ((size == other.size) && (std::equal(data, data + size, other.data)));
}

bool DynamicArray::operator!=(const DynamicArray& other) const {
	return !(*this == other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	if (capacity >= other.size) {
		std::copy(other.data, other.data + other.size, data);
		size = other.size;
	}
	else {
		Create(other.size, other.capacity, other.data);
	}
	return *this;
}