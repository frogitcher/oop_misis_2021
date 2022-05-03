#include "dynamic.h"
#include <stdexcept>

int& DynamicArray::operator[](size_t i) const {
    return *(data+i);
}

int& DynamicArray::at(size_t i) const {
    if (i >= size){
        throw "Index out of range";
    }
    else{
        return *(data+i);
    }
}

DynamicArray::DynamicArray(size_t length, int value)
    : size(length)
    , capacity(length) {
    if (length < 0){
        throw std::invalid_argument("Size should be more or equal than 0!");
    }
    data = new int[size];
    std::fill(data, data + length, value);
}

DynamicArray::DynamicArray(const DynamicArray& other)
    :size(other.size)
    ,capacity(other.capacity) {
    data = new int[size];
    for (int i = 0; i < size; i++){
        data[i]=other.data[i];
    }
}

DynamicArray::DynamicArray(const std::initializer_list<int>& lists)
    :size(lists.size())
    ,capacity(lists.size()) {
    data = new int[size];
    std::copy(lists.begin(), lists.end(), data);
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
	return size == 0;
}

int* DynamicArray::GetData() const {
    return data;
}

void DynamicArray::push_back(int value) {
    if (size == capacity){
        if (capacity == 0){
            capacity++;
        }
        int* new_data = new int[capacity*2];
        std::copy(data, data + capacity, new_data);
        delete[] data;
        data = new_data;
        capacity *= 2;

    data[size] = value;
    size++;
    }
}

void DynamicArray::pop_back() {
    if (size <= 0){
        throw "Array have no elements!";
    }
    size--;
}

void DynamicArray::clear() {
    size = 0;
}

void DynamicArray::erase(size_t index) {
    if (index >= size || index < 0){
        throw "The index is not match for an array!";
    }

    for (int i = index; i < size-1; i++) {
        data[i] = data[i+1];
    }
    size--;
}

void DynamicArray::Reallocate(size_t new_capacity) {
    int* new_data = new int[new_capacity];
    if (new_capacity > size){
		std::copy(data, data + size, new_data);
	}
	else{
		std::copy(data, data + new_capacity, new_data);
	}
    delete[] data;
    capacity = new_capacity;
    data = new_data;
}

void DynamicArray::resize (size_t new_size) {
    Reallocate(new_size);
    size = new_size;
}

void DynamicArray::insert(size_t index, int value) {
    if (index < 0 || index > size) {
         throw "The index is not match for an array!";
    }
    resize(size + 1);
    for(int i = size - 1; i > index; i--) {
        data[i] = data[i-1];
    }
    data[index] = value;
}

void DynamicArray::assign(size_t new_size, int value)
{
    resize(new_size);
    for (int i = 0; i < new_size; i++){
        data[i] = value;
    }
}


void DynamicArray::swap(DynamicArray& other) {
    int* data_copy = data;
    data_copy = other.data;
    other.data = data;
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

int* DynamicArray::begin() const {
    return data;
}

int* DynamicArray::end() const {
    return data+size-1;
}


