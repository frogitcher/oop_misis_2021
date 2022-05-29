#include "dyn_array.h"
#include <stdexcept>


void DynArray::reallocate(int64_t new_capacity) {
	int* new_data = new int[new_capacity];
	std::copy(data, data + size, new_data);
	delete[]data;
	data = new_data;
	capacity = new_capacity;
}

DynArray::DynArray(int64_t _size, int value) 
	: size(_size)
	, capacity(_size) {
	data = new int[size];
	std::fill(data, data + _size, value);
}

DynArray::DynArray(const DynArray& other)
	: size(other.size)
	, capacity(other.capacity) {
	data = new int[size];
	std::copy(other.begin(), other.end(), begin());
}

DynArray::DynArray(const std::initializer_list<int>& list) 
	: size(list.size())
	, capacity(list.size()) {
	data = new int[size];
	std::copy(list.begin(), list.end(), data);
}

DynArray::~DynArray() {
	delete[]data;
}

int64_t DynArray::Size() const {
	return size;
}

int64_t DynArray::Capacity() const {
	return capacity;
}

bool DynArray::Empty() const {
	return size == 0;
}

int& DynArray::operator[](int64_t i) const {
	return *(data + i);
}

int& DynArray::at(int64_t i) const {
	if (i >= size) {
		throw std::out_of_range("Index out of array's range");
	}
	return *(data + i);
}

void DynArray::push_back(int value) {
	if (size == capacity) {
		reallocate(capacity == 0 ? 1 : capacity * 2);
	}
	data[size++] = value;
}

void DynArray::pop_back() {
	if (size == 0) {
		throw std::underflow_error("Array is already empty");
	}
	size--;
}

void DynArray::clear() {
	size = 0;
}

void DynArray::erase(int64_t i) {
	if (i >= size) {
		throw std::out_of_range("Index out of array's range");
	}
	for (; i < size-1; i++) {
		data[i] = data[i + 1];
	}
	size--;
}

void DynArray::resize(int64_t new_size) {
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

void DynArray::assign(int64_t new_size, int value) {
	resize(new_size);
	std::fill(data, data+size, value);
}

void DynArray::insert(int64_t i, int value) {
	if (i >= size) {
		throw std::out_of_range("Index out of array's range");
	}
	else {
		resize(size + 1);
		for (int k = size - 1; k > i; k++) {
			*(data + k) = *(data + k - 1);
		}
		data[i] = value;
	}
}

int* DynArray::begin() const {
	return data;
}

int* DynArray::end() const {
	return data + size;
}

void DynArray::swap(DynArray& other) {
	std::swap(data, other.data);
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
}

bool DynArray::operator==(const DynArray& rhs) const {
	return (size == rhs.size && std::equal(begin(), end(), rhs.begin());
}

bool DynArray::operator!=(const DynArray& rhs) const {
	return !(*this == rhs);
}

DynArray& DynArray::operator=(const DynArray& rhs) {
	resize(rhs.size);
	for (int i = 0; i < size; i++) {
		data[i] = rhs.data[i];
	}
	return *this;
}