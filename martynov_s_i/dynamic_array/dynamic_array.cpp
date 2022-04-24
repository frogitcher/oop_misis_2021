#include "dynamic_array.h"
#include <initializer_list>
#include <vector>

DynamicArray::DynamicArray(size_t _size, int value) {
	size = _size;
	capacity = _size;
	data = new int[_size];
	std::fill(data, data + _size, value);
}

DynamicArray::DynamicArray(const DynamicArray& other) {
	int* new_data = new int[other.capacity];
	std::copy(other.data, other.data + other.size, new_data);
	data = new_data;
	size = other.size;
	capacity = other.capacity;
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
	size = list.size();
	capacity = list.size();
	int* new_data = new int[capacity];
	std::copy(list.begin(), list.end(), new_data);
	data = new_data;
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
			for (size_t i = size; i < new_size; ++i) {
				new_data[i] = 0;
			}
		}
		delete[] data;
		data = new_data;
	}
	else {
		if (new_size > size) {
			for (size_t i = size; i < new_size; ++i) {
				data[i] = 0;
			}
		}
	}
	size = new_size;
}

void DynamicArray::assign(size_t new_size, int value) {
	int* new_data = new int[new_size];
	for (size_t i = 0; i < new_size; ++i) {
		new_data[i] = value;
	}
	delete[] data;
	data = new_data;
	size = new_size;
	capacity = new_size;
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


int& DynamicArray::at(size_t index) const {
	return (*this)[index];
}

int& DynamicArray::operator[](size_t index) const {
	if (index >= size) {
		throw "index out";
	}
	return *(data + index);
}


bool DynamicArray::empty() const {
	return size == 0;
}

bool DynamicArray::operator==(const DynamicArray& other) const {
	if (size != other.size) {
		return false;
	}
	return std::equal(data, data + size, other.data);
}

bool DynamicArray::operator!=(const DynamicArray& other) const {
	return !(*this == other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	if (size >= other.size) {
		std::copy(other.data, other.data + other.size, data);
	}
	else {
		int* new_data = new int[other.capacity];
		std::copy(other.data, other.data + other.capacity, new_data);
		delete[] data;
		data = new_data;
		capacity = other.capacity;
	}
	size = other.size;
	return *this;
}