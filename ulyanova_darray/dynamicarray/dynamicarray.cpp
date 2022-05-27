#include "dynamicarray.h"
#include <algorithm>
#include <stdexcept>

DynamicArray::DynamicArray(int64_t _size, int value) 

	: size(_size)
	, capacity(_size) {
		if (size < 0) {
			throw std::invalid_argument("Size Error");
	}
	data = new int[size];
	std::fill(data, data + size, value);
}

DynamicArray::DynamicArray() {
	size = 0;
	capacity = 0;
	data = new int[size];
}

DynamicArray::DynamicArray(const DynamicArray& other)
	: size(other.size)
	, capacity(other.capacity) {
	data = new int[other.capacity];
	std::copy(other.data, other.data + other.size, data);
}


DynamicArray::DynamicArray(const std::initializer_list<int>& list)

	: size(list.size())
	, capacity(list.size()) {
	data = new int[list.size()];
	std::copy(list.begin(), list.end(), data);
}

DynamicArray::~DynamicArray() {
	delete[] data;
}

void DynamicArray::Push_back(int value) { 

	if (capacity == 0) {  //åñëè PB â ïóñòîé ìàññèâ
		int* new_data = new int[++capacity];
		data = new_data;
	}

	if (size == capacity) {
		int* new_data = new int[capacity * 2];
		std::copy(data, data + size, new_data);
		delete[] data;
		data = new_data;
		capacity *= 2;
	}

	data[size] = value;
	size++;
}

bool DynamicArray::Empty() const {
	return (size == 0);
}

void DynamicArray::Pop_back() {

	if (size == 0) {
		throw std::length_error("Pop_back Error");
	}

	size--;
}

void DynamicArray::Clear() {
	size = 0;
}

int& DynamicArray::operator[](int64_t i) const {
	return *(data + i);
}

int& DynamicArray::At(int64_t i) const {

	if (i < 0 || i >= size) { 
		throw std::out_of_range("At Error");
	}
	return *(data + i);
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

void DynamicArray::Resize(int64_t new_size) {

	if (new_size < 0) {
		throw std::length_error("Resize Error");
	}

	if (new_size > size && new_size <= capacity) {
		std::fill(data + size, data + new_size, 0);
	}

	if (new_size > capacity) {
		capacity = new_size;
		int* new_data = new int[capacity];
		std::copy(data, data + size, new_data);
		std::fill(new_data + size, new_data + new_size, 0);
		delete[] data;
		data = new_data;
	}
	size = new_size;
}

bool DynamicArray::operator==(const DynamicArray& other) const{ 

	/*if (size != other.size) {
		return false;
	}

	for (int i = 0; i < size; i++) {
		if (data[i] != other.data[i]) {
			return false;
		}
	}
	
	return true;*/

	return (size == other.size && std::equal(data, data + size, other.data, other.data + size));
}

bool DynamicArray::operator!=(const DynamicArray& other) const{ 
	return (!(*this == other));
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) { 
	if (other.size > capacity) {
		capacity = other.capacity;
		int* new_data = new int[capacity];
		std::copy(other.data, other.data + other.size, new_data);
		delete[] data;
		data = new_data;
	}
	else {
		std::copy(other.data, other.data + other.size, data);
	}
	size = other.size;
	return *this;
}

void DynamicArray::Erase(int64_t index) {

	if (index < 0 || index >= size) {
		throw std::out_of_range("Erase Error");
	}
	
	for (int64_t i = index; i < size - 1; i++) {
		data[i] = data[i + 1];
	}
	size--;
}

void DynamicArray::Swap(DynamicArray& other) { 
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}

void DynamicArray::Assign(int64_t new_size, int value) {

	if (new_size < 0) {
		throw std::length_error("Assign Error");
	}

	if (new_size > size && new_size <= capacity) {
		std::fill(data, data + new_size, value);
	}

	if (new_size > capacity) {
		capacity = new_size;
		int* new_data = new int[capacity];
		std::fill(new_data, new_data + new_size, value);
		delete[] data;
		data = new_data;
	}
	if (new_size <= size) {
		std::fill(data, data + new_size, value);
	}
	size = new_size;
}

void DynamicArray::Insert(int64_t index, int value) {

	if (index < 0 || index > size) {
		throw std::out_of_range("Insert Error");
	}

	if (size + 1 > capacity) {
		capacity++;
		int* new_data = new int[capacity];
		std::copy(data, data + index, new_data);
		for (int64_t i = size; i > index; i--) {
			new_data[i] = data[i - 1];
		}
		new_data[index] = value;
		delete[] data;
		data = new_data;
	}
	else {
		for (int64_t i = size; i > index; i--) {
			data[i] = data[i - 1];
		}
		data[index] = value;
	}
	size++;
}

int* DynamicArray::begin() const{
	return data;
}

int* DynamicArray::end() const {
	if (size > 0) {
		return data + size;
	}
	else {
		return data;
	}
}
