#include "dynamic_array.h"
#include <stdexcept>
#include <algorithm>

void DynamicArray::change_capacity(size_t new_capacity) {
	if (size > new_capacity) throw std::out_of_range("Capacity must be more than size.");
	int* new_data = new int[new_capacity];
	std::copy(data, data + size, new_data);
	delete[]data;
	data = new_data;
	capacity = new_capacity;
}


DynamicArray::DynamicArray(size_t _size, int value) : size(_size), capacity(_size) {
		data = new int[size];
		std::fill(data, data + size, value);
}
DynamicArray::DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity) {
		data = new int[capacity];
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
	size = 0;
}
void DynamicArray::erase(size_t i) {
	if (i >= size) throw std::out_of_range("Index out of range");

	std::copy(data+i+1, data + size, data+i);
	size--;
}
void DynamicArray::resize(size_t new_size) {
	if (new_size > capacity) change_capacity(new_size*2);
	else if (new_size > size) std::fill(data + size, data + new_size, 0);
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
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}


bool DynamicArray::operator==(const DynamicArray& other) const {
	return (size == other.size) && std::equal(data, data+size, other.data); 
}
bool DynamicArray::operator!=(const DynamicArray& other) const {
	return !(*this == other);
}
DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	resize(other.size);
	std::copy(other.data, other.data +  other.Size(), data);
	return *this;
}