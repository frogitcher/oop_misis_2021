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
	data = new int[other.size];
	std::copy(other.data, other.data + other.capacity, data);
}


DynamicArray::DynamicArray(const std::initializer_list<int>& list)

	: size(list.size())
	, capacity(list.size()) {
	data = new int[list.size()];
	int i = 0;
	for (int value : list) {
		data[i++] = value;
	}
}

DynamicArray::~DynamicArray() {
	delete[] data;
}

void DynamicArray::Push_back(int value) { 

	if (capacity == 0) {  //если PB в пустой массив
		int* new_data = new int[++capacity];
		data = new_data;
	}

	if (size == capacity) {
		int* new_data = new int[capacity * 2];
		std::copy(data, data + capacity, new_data);
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

	int* new_data = new int[--size];
	
	for (int i = 0; i < size; i++) {
		new_data[i] = data[i];
	}

	delete[] data;
	data = new_data;
}

void DynamicArray::Clear() {
	if (size > 0) {
		size = 0;
		delete[] data;
		data = new int[size];
	}
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

int* DynamicArray::GetData() {
	return data;
}

void DynamicArray::Resize(int64_t new_size) {

	if (new_size < 0) {
		throw std::length_error("Resize Error");
	}

	int* new_data = new int[new_size];
	if (new_size > size) {

		capacity = new_size * 2;

		for (int i = 0; i < size; i++) {
			new_data[i] = data[i];
		}
		
		for (int i = size; i < new_size; i++) {
			new_data[i] = 0;
		}
		size = new_size;
	}

	if (new_size < size) {

		size = new_size;

		for (int i = 0; i < size; i++) {
			new_data[i] = data[i];
		}
	}
	delete[] data;
	data = new_data;
}

bool DynamicArray::operator==(const DynamicArray& other){ 

	if (size != other.size) {
		return false;
	}

	for (int i = 0; i < size; i++) {
		if (data[i] != other.data[i]) {
			return false;
		}
	}
	
	return true;
}

bool DynamicArray::operator!=(const DynamicArray& other){ 
	return (!(*this == other));
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) { 
	size = other.size;
	capacity = other.capacity;
	int* new_data = new int[other.size];
	for (int i = 0; i < other.size; i++) {
		new_data[i] = other.data[i];
	}
	delete[] data;
	data = new_data;
	return *this;
}

void DynamicArray::Erase(int64_t index) {

	if (index < 0 || index >= size) {
		throw std::out_of_range("Erase Error");
	}
	
	int* new_data = new int[size - 1];

	for (int i = 0; i < index; i++) {
		new_data[i] = data[i];
	}
	for (int i = index + 1; i < size; i++) {
		new_data[i - 1] = data[i];
	}
	delete[] data;
	data = new_data;
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

	if (new_size > size) {
		capacity = new_size * 2;
	}

	int* new_data = new int[new_size];
	size = new_size;

	for (int i = 0; i < size; i++) {
		new_data[i] = value;
	}
	delete[] data;
	data = new_data;
}

void DynamicArray::Insert(int64_t index, int value) {

	if (index < 0 || index > size) {
		throw std::out_of_range("Insert Error");
	}

	int* new_data = new int[++size];

	for (int i = 0; i < index; i++) {
		new_data[i] = data[i];
	}

	new_data[index] = value;

	for (int i = index + 1; i < size; i++) {
		new_data[i] = data[i - 1];
	}

	capacity++;
	delete[] data;
	data = new_data;
}

int* DynamicArray::begin() {
	return data;
}

int* DynamicArray::end() {
	if (size > 0) {
		return data + size - 1;
	}
	else {
		return data;
	}
}

void DynamicArray::Realocate(int64_t new_size) {

	if (new_size < 0) {
		throw std::length_error("Realocate Error");
	}

	int64_t new_capacity = capacity;
	if (new_size > capacity) {
		new_capacity *= 2;
	}

	int* new_data = new int[new_capacity];
	std::copy(data, data + capacity, new_data);
	delete[] data;
	data = new_data;
}



