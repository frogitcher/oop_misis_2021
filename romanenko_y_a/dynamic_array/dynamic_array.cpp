#include "dynamic_array.h"
#include <stdexcept>

void DynamicArray::change_capacity(size_t new_capacity) {
	int* new_data = new int[new_capacity];
	if (new_capacity > size){
		std::copy(data, data + size, new_data);
	}
	else{
		std::copy(data, data + new_capacity, new_data);
	}
	delete[]data;
	data = new_data;
	capacity = new_capacity;
}


DynamicArray::DynamicArray(size_t _size, int value) : size(_size), capacity(_size) {
		if (size < 0) throw std::invalid_argument("Size must be positive");
		data = new int[size];
		std::fill(data, data + size, value);
}
DynamicArray::DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity) {
		data = new int[size];
        std::copy(other.data, other.data + other.size, data);
}
DynamicArray::DynamicArray(const std::initializer_list<int>& list) : size(list.size()), capacity(list.size()) {
	data = new int[size];
	std::copy(list.begin(), list.end(), data);
}
DynamicArray::~DynamicArray() {
	delete[]data;
}


size_t DynamicArray::Size() const {
	return size;
}
size_t DynamicArray::Capacity() const {
	return capacity;
}
bool DynamicArray::Empty() const {
	return size == 0;
}
int& DynamicArray::operator[](size_t i) const {
	return *(data + i);
}
int& DynamicArray::at(size_t i) const {
	if (i >= size) throw std::out_of_range("Index out of range");
	return *(data + i);
}


void DynamicArray::push_back(int value) {
	if (size == capacity) {
		if (capacity != 0) {
			change_capacity(capacity * 2);
		}
		else {
			change_capacity(1);
		}
	}
	data[size++] = value;
}
void DynamicArray::pop_back() {
	if (size == 0) throw std::underflow_error("Array is empty");
	size--;
}
void DynamicArray::clear() {
	delete[]data;
	size = 0;
	capacity = 0;
	data = new int[0];
}
void DynamicArray::erase(size_t i) {
	if (i >= size) throw std::out_of_range("Index out of range");

	for (; i < size-1; i++) {
		*(data + i) = *(data + i + 1);
	}
	size--;
}
void DynamicArray::resize(size_t new_size) {
	change_capacity(new_size);
	size = new_size;
}
void DynamicArray::assign(size_t new_size, int value) {
	resize(new_size);
	std::fill(data, data+size, value);
}
int* DynamicArray::begin() const {
	return data;
}
int* DynamicArray::end() const {
	return data + size;
}
void DynamicArray::swap(DynamicArray& other) {
	int* data_copy = data;
	data = other.data;
	other.data = data_copy;

	size_t size_copy = size;
	size = other.size;
	other.size = size_copy;

	size_t capacity_copy = capacity;
	capacity = other.capacity;
	other.capacity = capacity_copy;
}


bool DynamicArray::operator==(const DynamicArray& other) const {
	if (size != other.size) return false;
	for (int i = 0; i < size; i++) {
		if (data[i] != other.data[i]) return false;
	}
	return true;
}
bool DynamicArray::operator!=(const DynamicArray& other) const {
	return !(*this == other);
}
DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	resize(other.size);
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
	return *this;
}