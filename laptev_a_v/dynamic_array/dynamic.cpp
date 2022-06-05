#include <stdexcept>
#include <initializer_list>
#include <stddef.h>
#include "dynamic.h"

DynamicArray::DynamicArray(size_t _size, int value)
    : size(_size)
    , capacity(_size){
        data = new int[capacity];
        std::fill(data, data + size, value);
}
DynamicArray::DynamicArray(const DynamicArray& other)
    : size(other.size)
    , capacity(other.capacity) {
        data = new int[capacity];
        std::copy(other.data, other.data + other.size, data);
}
DynamicArray::DynamicArray(const std::initializer_list<int>& list)
    : size(list.size())
    , capacity(list.size()) {
        data = new int[capacity];
        std::copy(list.begin(), list.end(), data);
    }
const size_t DynamicArray::Size() const{
    return size;
}
const size_t DynamicArray::Capacity() const{
    return capacity;
}
bool DynamicArray::Empty() const{
    return size == 0;
}
int& DynamicArray::operator[](size_t i){
    return *(data+i);
}
int& DynamicArray::at(size_t i){
    if(i < size){
        return *(data+i);
    }
    else{
        throw std::out_of_range("index out of range");
    }
}
void DynamicArray::push_back(int value){
    if(size == capacity){
        int* new_data = new int[capacity*2];
        std::copy(data, data+capacity, new_data);
        delete[] data;
        data = new_data;
        capacity *= 2;
    }
    size += 1;
    data[size - 1] = value;
}
void DynamicArray::pop_back(){
    if (size == 0) {
		throw std::out_of_range("size can't be < 0");
	}
	else {
		size--;
	}
}
void DynamicArray::clear() {
    delete[] data ;
    size = 0;
}
void DynamicArray::erase(size_t index){
    if (index >= size) {
		throw std::out_of_range("index out of range");
	}
    for(size_t i=index;i < size-1; ++i){
        data[i] = data[i+1];
    }
    size--;
}
void DynamicArray::insert(size_t index, int value){
    push_back(0);
	if (index > size - 1) {
		throw std::out_of_range("index out of range");
	}
	for (size_t i = size - 1; i > index; --i) {
		data[i] = data[i - 1];
	}
	data[index] = value;
}
void DynamicArray::assign(size_t new_size, int value){
    if (new_size < 0) {
		throw std::out_of_range("size can't be < 0");
	}
	if (new_size >= capacity) {
		int new_capacity = 1;
		while (new_size > new_capacity) {
			new_capacity *= 2;
		}
		realloc(new_capacity);
	}
	size = new_size;
	std::fill(data, data + size, value);
}
int* DynamicArray::begin() const{
    return data;
}
int* DynamicArray::end() const{
    return data+size;
}
void DynamicArray::swap(DynamicArray& other){
    std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}
void DynamicArray::realloc(size_t new_capacity) {
	int* new_data = new int[new_capacity];
	std::copy(data, data + size, new_data);
	data = new_data;
	capacity = new_capacity;
}
bool DynamicArray::operator==(const DynamicArray& other) const
{
    if(size == other.Size()){
        return std::equal(begin(),end(),other.begin(), other.end());
    }
    else{
        return false;
    }
}
bool DynamicArray::operator!=(const DynamicArray& other) const{
    return !(*this==other);
}
