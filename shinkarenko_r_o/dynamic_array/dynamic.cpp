#include "dynamic.h"
#include <stdexcept>

void DynamicArray::realloc(size_t new_size) {
	size_t new_capacity = capacity;
	if (new_size > capacity) {
		new_capacity *= 2;
	}
	int* new_data = new int[new_capacity];
	std::copy(begin(), end(), new_data);
	delete[] data;
	data = new_data;
}

DynamicArray::DynamicArray()
	: size(0)
	, capacity(1)
	, data(nullptr){
	data = new int[1];
}

DynamicArray::DynamicArray(size_t _size, int value)
	: size(_size)
	, capacity(_size)
	, data(nullptr) {
	data = new int[capacity];
	std::fill(data, data + size, value);
}

DynamicArray::DynamicArray(const DynamicArray& other)
	: size(other.size)
	, capacity(other.capacity)
	, data(nullptr) {
	data = new int[capacity];
	std::fill(other.data, other.data + other.capacity, data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list)
	: size(list.size())
	, capacity(list.size())
	, data(nullptr) {
	data = new int[capacity];
	std::copy(list.begin(), list.end(), data);
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

bool DynamicArray::Empty() const {
	return (size == 0);
}

int& DynamicArray::operator[](size_t i) {
	if (i >= size) {
		throw std::invalid_argument("Index is out of range");
	}
	else {
		return data[i];
	}
}

int& DynamicArray::at(size_t i) const {
	if (i >= size) {
		throw std::invalid_argument("Index is out of range");
	}
	else {
		return *(data + i);
	}
}

void DynamicArray::operator=(const DynamicArray& other) {
	size = other.Size();
	capacity = other.Capacity();
	std::copy(other.data, other.data + other.capacity, data);
}

bool DynamicArray::operator==(const DynamicArray& other) const {
	if (size == other.size) {
		for (int i = 0; i < size; ++i) {
			if (data[i] != other.data[i]) return false;
		}
		return true;
	}
	return false;
}
bool DynamicArray::operator!=(const DynamicArray& other) const {
	return !(*this == other);
}

void DynamicArray::resize(size_t new_size, int value) {
	if (new_size < 0) {
		throw std::invalid_argument("Array size must be positive number");
	}
	else if (new_size == 0) {
		size = 0;
	}
	else {
		realloc(new_size);
		std::fill(data + size, data + new_size, value);
	}
}

void DynamicArray::push_back(int value) {
	resize(size + 1, 0);
	data[size - 1] = value;
}

void DynamicArray::pop_back() {
	if (size == 0) {
		throw std::range_error("Empty array");
	}
	--size;
}

void DynamicArray::clear() {
	size = 0;
}

void DynamicArray::erase(size_t idx) {
	if (idx >= size || size == 0) {
		throw std::range_error("Index is out of range");
	}
	for (int i = idx; i < size - 1; ++i) {
		data[i] = data[i + 1];
	}
	size--;
}

void DynamicArray::insert(size_t idx, int value) {
	resize(size + 1, 0);
	if (idx >= size) {
		throw std::range_error("Index is out of range");
	}
	for (int i = idx + 1; i < size; ++i) {
		data[i] = data[i - 1];
	}
	data[idx] = value;
}

void DynamicArray::swap(DynamicArray& other) {
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}

int* DynamicArray::begin() {
	return data;
}

int* DynamicArray::end() {
	return data + size;
}



