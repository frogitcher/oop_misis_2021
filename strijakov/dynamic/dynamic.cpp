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
    , capacity(length)
    data = new int[size];
    std::fill(data, data + length, value);
}

DynamicArray::DynamicArray(const DynamicArray& other)
    :size(other.size)
    ,capacity(other.capacity) {
    data = new int[capacity];
    for (int i = 0; i < size; i++){
        std::copy(other.data, other.data + other.size, data);
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
        std::copy(data, data + size, new_data);
        delete[] data;
        data = new_data;
        capacity *= 2;
    }
    data[size] = value;
    size++;
}

void DynamicArray::pop_back() {
    if (size == 0){
        throw "Array have no elements!";
    }
    size--;
}

void DynamicArray::clear() {
    size = 0;
}

void DynamicArray::erase(size_t index) {
    if (index >= size){
        throw "The index is not match for an array!";
    }

    for (int i = index; i < size-1; i++) {
        data[i] = data[i+1];
    }
    size--;
}

void DynamicArray::Reallocate(size_t new_capacity) {
    int* new_data = new int[new_capacity];
    std::copy(data, data + size, new_data);
    delete[] data;
    capacity = new_capacity;
    data = new_data;
}

void DynamicArray::resize (size_t new_size) {
    if (new_size > capacity){
	Reallocate(new_size);
    }
    if (size < new_size || new_size <= capacity) {
    	for(int i = size; i <= new_size; i++) {
        	data[i] = 0;
	}
    }
    size = new_size;
}

void DynamicArray::insert(size_t index, int value) {
    if (index > size) {
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
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
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
	std::copy(data, data + size, new_data);
	return *this;
}

int* DynamicArray::begin() const {
    return data;
}

int* DynamicArray::end() const {
    return data+size;
}


