#include "din.h"
#include <stdexcept>
#include <algorithm>

DinamicArray::DinamicArray() {
	size = 0;
	capacity = 0;
	data = new int[size];
}

DinamicArray::DinamicArray(size_t n, int val = 0):size(n), capacity(n){
        if (size < 0) {
			throw std::invalid_argument("Error. Size < 0");
	}
    data = new int[n];
    fill(data, data + n, val);
}

DinamicArray::DinamicArray(const DinamicArray& a)
	: size(a.size)
	, capacity(a.capacity) {
	data = new int[other.size];
	std::copy(a.data, a.data + a.capacity, data);
}

DinamicArray::DinamicArray(const std::initializer_list<int>& list): size(list.size()), capacity(list.size()) {
	data = new int[list.size()];
	int i = 0;
	for (int a : list) {
		data[i] = a;
		i++;
	}
}

size_t DinamicArray::Size() const{
    return size;
}

bool DinamicArray::Empty()const{
    return(size == 0);
}

DinamicArray::~DinamicArray() {
    if(data != NULL)
	delete[] data;
}

int& DinamicArray::operator[](size_t i) const {
    if (i < 0 || i >= size) {
		throw std::out_of_range("index out of range");
	}
	return *(data + i);
}

int& DinamicArray::At(size_t i)const{
    if (i < 0 || i >= size) {
		throw std::out_of_range("index out of range");
	}
	return *(data + i);
}

void DinamicArray::Push_back(int value) {
        if (size == capacity) {
            if (capacity != 0) {
                int* new_data = new int[capacity * 2];
                copy(data, data + capacity * 2, new_data);
                delete[] data;
                data = new_data;
            }
            capacity *= 2;
            capacity++;
        }
        data[size] = value;
        size++;
}

void DinamicArray::Pop_back(){
    if (size > 0) {
        int* new_data = new int[size-1];
        copy(data, data + size-1, new_data);
        delete[] data;
        data = new_data;
        size -= 1;
        capacity = size;
    }
}

void DinamicArray::Clear(){
    delete[] data;
    data = NULL;
    size = 0;
    capacity = 0;
}

void DinamicArray::Erase(size_t i){
    for (int k = i + 1; k < size; k++) {
        data[k - 1] = data[k];
    }
    int* new_data = new int[size - 1];
    copy(data, data + size - 1, new_data);
    delete[] data;
    data = new_data;
    size -= 1;
    capacity = size;
}

void DinamicArray::Resize(size_t new_size){
    if (new_size < 0) {
		throw std::length_error("Resize Error");
	}
    if (new_size < size) {
            int* new_data = new int[new_size];
            copy(data, data + new_size, new_data);
            delete[] data;
            data = new_data;
            size = new_size;
            capacity = size;
        }
        else {
            int* new_data = new int[new_size];
            copy(data, data + new_size, new_data);
            delete[] data;
            data = new_data;
            for (int i = size; i < new_size; i++)
                data[i] = 0;
            size = new_size;
            capacity = size;
        }
}

void DinamicArray::Insert(size_t i, int value) {
        if (size == capacity) {
            if (capacity != 0) {
                int* new_data = new int[capacity * 2];
                copy(data, data + capacity * 2, new_data);
                delete[] data;
                data = new_data;
            }
            capacity *= 2;
            capacity++;
        }
        size++;
        capacity = size;
        for (int k = i + 1; k < size; k++)
            data[k] = data[k - 1];
        data[i] = value;
}

void DinamicArray::Assign(size_t new_size, int value) {
        data = new int[new_size];
        fill(data, data + new_size, value);
        size = new_size;
        capacity = size;
        for (int i = 0; i < new_size; i++)data[i] = value;
}

void DynamicArray::Swap(DynamicArray& a) {
	std::swap(size, a.size);
	std::swap(capacity, a.capacity);
	std::swap(data, a.data);
}

int* DynamicArray::begin() {
	return data;
}

int* DynamicArray::end() {
    return data + size;
}

bool DinamicArray::operator==(const DinamicArray& a){

	if (size != a.size) {
		return false;
	}

	for (int i = 0; i < size; i++) {
		if (data[i] != a.data[i]) {
			return false;
		}
	}

	return true;
}

bool DinamicArray::operator!=(const DinamicArray& a){
	return (!(*this == a));
}

DinamicArray& DinamicArray::operator=(const DinamicArray& a) {
	size = a.size;
	capacity = a.capacity;
	int* new_data = new int[a.size];
	for (int i = 0; i < a.size; i++) {
		new_data[i] = a.data[i];
	}
	delete[] data;
	data = new_data;
	return *this;
}
