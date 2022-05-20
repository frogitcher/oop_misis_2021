#include "dynamic_array.h"
#include <algorithm>
#include <stdexcept>

void DynamicArray::reallocate(int64_t new_capacity) {
	int* new_data = new int[new_capacity];
		std::copy(data, data+size, new_data);
		delete[]data;

		capacity = new_capacity;
		data = new_data;
}

DynamicArray::DynamicArray(int64_t _size) {
	if (_size < 0) {
		throw std::invalid_argument("Size must not be negative!");
	}

	size = _size;
	capacity = _size;
	data = new int[_size];

	std::fill(data, data+_size, 0);

}

DynamicArray::DynamicArray(int64_t _size, int value) {
	if (_size < 0) {
		throw std::invalid_argument("Size must not be negative!");
	}

	size = _size;
	capacity = _size;
	data = new int[_size];

	std::fill(data, data+_size, value);

}

int64_t DynamicArray::Size() const{
	return size;
}

int64_t DynamicArray::Capacity() const{
	return capacity;
}

int* DynamicArray::begin() const{
	return data;
}

int* DynamicArray::end() const{
	return data+size;
}

DynamicArray::DynamicArray(const DynamicArray& other) {
	size = other.Size();
	capacity = other.Capacity();
	data = new int[capacity];

	std::copy(other.begin(), other.end(), data);
}

DynamicArray::DynamicArray(const std::initializer_list<int>& list) {
	size = list.size();
	capacity = list.size();
	data = new int[capacity];

	std::copy(list.begin(), list.end(), data);
}

DynamicArray::~DynamicArray() {
	delete[]data;
}

int& DynamicArray::operator[](int64_t i) const{
	return *(data+i);
}

int& DynamicArray::at(int64_t i) const {
	if (i>= size || i<0) {
		throw std::out_of_range("Index is out of range!");
	}
	else {
		return *(data+i);
	}
}


bool DynamicArray::empty() const{
	return size==0;
}

void DynamicArray::erase(int64_t i){
	if (i>=size || i<0) {
		throw std::out_of_range("You're trying to access an element which is out of range!");
	}
	std::copy(data+i+1, data+size, data+i);
	size--;
}

void DynamicArray::pop_back() {
	this->erase(size-1);
}

void DynamicArray::insert(int64_t i, int value) {
	if (i<0 || i>size) {
		throw std::out_of_range("Index is out of range!");
	}
	if (size == capacity) {
		reallocate(2*capacity);
	}
	std::copy_backward(data+i, data+size, data+size+1);
	data[i] = value;
	size++;
}

void DynamicArray::push_back(int value) {
	this->insert(size, value);
}

void DynamicArray::resize(int64_t new_size) {
	if (new_size<0) {
		throw std::invalid_argument("Size must not be negative!");
	}
	if (new_size>capacity) {
		reallocate(new_size);
	}
	if (size<new_size) {
		std::fill(data+size, data+new_size, 0);
	}
	size = new_size;
}

void DynamicArray::clear() {
	size = 0;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	if (other.Size() > capacity) {
		reallocate(other.Size());
	}

	std::copy(other.begin(), other.end(), data);
	size = other.Size();

	return *this;
}

void DynamicArray::assign(int64_t new_size, int value) {
	if (new_size<0) {
		throw std::invalid_argument("Size must not be negative!");
	}
	if (new_size > capacity) {
		reallocate(new_size);
	}
	size = new_size;

	std::fill(data, data+new_size, value);
}

void DynamicArray::swap(DynamicArray& other) {
	std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
}

bool DynamicArray::operator==(const DynamicArray& other) const {
	return std::equal(data, data+size, other.begin(), other.end());
}

bool DynamicArray::operator!=(const DynamicArray& other) const {
	return !(*this == other);
}
