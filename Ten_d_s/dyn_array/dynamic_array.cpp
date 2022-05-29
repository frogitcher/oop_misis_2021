#include "dynamic_array.h"
#include <stdexcept>

void DynamicArray::push_back(int value) {
	if (size == capacity) {
		if (capacity == 0) {
			int* nw_data = new int[1];
			delete[]data;
			data = nw_data;
			capacity = 1;
		}
		else {
			std::copy(data, data + size, nw_data);
			delete[]data;
			data = nw_data;
			capacity *= 2;
		}
	}
	data[size++] = value;
}

DynamicArray::DynamicArray(int _size, int value)
	: size(_size)
	, capacity(_size) {
	if (_size < 0) {
		throw std::invalid_argument("Size should be more or equal 1");
	}
	data = new int[size];
	std::fill(data, data + _size, value);
}

DynamicArray::DynamicArray(const DynamicArray& other)
	: size(other.size)
	, capacity(other.capacity) {
	data = new int[capacity];
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}


DynamicArray::DynamicArray(const std::initializer_list<int>& list)
	: size(list.size())
	, capacity(list.size()) {
	data = new int[size];
	std::copy(list.begin(), list.end(), data);
}

DynamicArray::~DynamicArray() {
	delete[]data;
}

int DynamicArray::Size() const {
	return size;
}

int DynamicArray::Capacity() const {
	return capacity;
}
bool DynamicArray::Empty() const {
	return size == 0;
}

bool DynamicArray::operator==(const DynamicArray& other) const {
	if (size == other.size) {
		for (int i = 0; i < size; i++) {
			if (other.data[i] != data[i]) {
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool DynamicArray::operator!=(const DynamicArray& other) const {
	return !(*this == other);
}

void DynamicArray::ResizeArray(int nwcapacity) {
	int* new_data = new int[nwcapacity];
	std::copy(data, data + size, new_data);
	delete[]data;
	data = new_data;
	capacity = nwcapacity;
}

int& DynamicArray::operator[](int i) const {
	return *(data + i);
}


int& DynamicArray::at(int i) const{
	if ((i >= size) && (i < 0)) {
		throw std::out_of_range("Index out of range");
	}
	else
	{
		return *(data + i);
	}
}

void DynamicArray::pop_back() {
	if (size == 0) {
		throw std::underflow_error("Array is empty");
	}
	else
	{
		size-=1;
	}
}

void DynamicArray::clear() {
	size = 0;
}

void DynamicArray::erase(int i) {
	if ((i >= size) && (i<0) ){
		throw std::out_of_range("Index out of range");
	}
	else
	{
		for (; i < size - 1; i++) {
			*(data + i) = *(data + i + 1);
		}
		size--;
	}
}

void DynamicArray::resize(int nwsize) {
	if (nwsize > capacity) {
		int nwcapacity = nwsize * 2;
		int* nwdata = new int[nwcapacity];
		for (int i = 0; i < size; ++i) {
			nwdata[i] = data[i];
		}
		capacity = nwcapacity;
		delete[]data;
		data = nwdata;
	}
	if (nwsize > size) {
		std::fill(data + size, data + nwsize, 0);
	}
	size = nwsize;
}

void DynamicArray::assign(int nwsize, int value) {
	resize(nwsize);
	std::fill(data, data + size, value);
}

void DynamicArray::insert(int i, int value) {
	if ((i >= size) && (i<0)) {
		throw std::out_of_range("Index out of range");
	}
	if (i == size) {
		push_back(value);
	}
	else {
		this->resize(size + 1);
		for (int k = size - 1; k > i; k++) {
			*(data + k) = *(data + k - 1);
		}
		data[i] = value;
	}
}

int* DynamicArray::begin() const {
	return data;
}

int* DynamicArray::end() const {
	return data + size;
}

void DynamicArray::swap(DynamicArray& other) {
	int* a = data;
	data = other.data;
	other.data = a;
	int b = size;
	size = other.size;
	other.size = b;
	b = capacity;
	capacity = other.capacity;
	other.capacity = b;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	resize(other.size);
	std::copy(other.data, other.data + other.Size(), data);
	return *this;
}
