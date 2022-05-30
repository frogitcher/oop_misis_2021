#include "dynamic.h"
#include <stdexcept>
#include <algorithm>

void DynamicArray::realloc(size_t new_capacity) {
	int* new_data = new int[new_capacity];
	std::copy(data, data + size, new_data);
	delete[] data;
	data = new_data;
	capacity = new_capacity;
}

int* DynamicArray::begin() const {
	return data;
}

int* DynamicArray::end() const {
	return data + size;
}

DynamicArray::DynamicArray()
	: size(0)
	, capacity(1)
	, data(nullptr) {
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
	std::copy(other.data, other.data + other.size, data);
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

int& DynamicArray::operator[](size_t i) const{
		return data[i];
}

int& DynamicArray::at(size_t i) const {
	if (i >= size) {
		throw std::invalid_argument("Index is out of range");
	}
	else {
		return *(data + i);
	}
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {

	size = other.size;
	if (other.size > capacity) {
		realloc(other.capacity);
	}
	std::copy(other.data, other.data + other.size, data);
	return *this;

}

bool DynamicArray::operator==(const DynamicArray& other) const {
	if (size == other.size) {
		return std::equal(data, data + size, other.data);
	}
	return false;
}
bool DynamicArray::operator!=(const DynamicArray& other) const {
	return !(*this == other);
}

void DynamicArray::resize(int new_size, int value) {
	size_t old_size = size;
	if (new_size < 0) {
		throw std::invalid_argument("Array size must be positive");
	}
	if (new_size > capacity) {
		int _capacity = 1;
		while (_capacity < new_size) {
			_capacity *= 2;
		}
		realloc(_capacity);
	}
	for (int i = old_size; i < new_size; ++i) data[i] = value;
	size = new_size;
}

void DynamicArray::push_back(int value) {
	if (capacity == 0) {
		capacity = 1;
	}
	realloc(capacity + 1);
	data[size++] = value;
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
	--size;
}

void DynamicArray::insert(size_t idx, int value) {
	resize(size + 1, 0);
	if (idx > size) {
		throw std::range_error("Index is out of range");
	}
	if (idx == size) {
		push_back(value);
	}
	else {
		std::copy_backward(data + idx, data + size + 1, data + size);
	}
	data[idx] = value;
}

void DynamicArray::swap(DynamicArray& other) {
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}