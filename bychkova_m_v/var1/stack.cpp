#include "stack.h"
#include <algorithm>

Stack::Stack(std::initializer_list<int> list){
	size = list.size();
	data = new int[size];
	capacity = list.size();
	std::copy(list.begin(), list.end(), data);
}

int* Stack::begin() const{
	return data;
}

int* Stack::end() const{
	return data+size;
}

Stack::Stack(Stack& other){
	size = other.Size();
	capacity = size;
	data = new int[capacity];
	std::copy(other.begin(), other.end(), data);
}

Stack::~Stack(){
	delete[]data;
}

void Stack::reallocate(int64_t new_size){
	capacity = new_size;
	int* new_data = new int[capacity];
	std::copy(data, data+size, new_data);
	delete[]data;
	data = new_data;
}

void Stack::Push(int value){
	reallocate(size+1);
	size = size+1;
	data[size-1]= value;
}

void Stack::Pop(){
	size = size-1;
}

int64_t Stack::Size() const {
	return size;
}

bool Stack::Empty() const {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

int Stack::Get() const {
	return *data;
}

bool Stack::operator==(Stack& other const) const {
	return std::equal(data, data+size, other.begin(), other.end());
}

bool Stack::operator!=(Stack& other const) const {
	return !(*this == other);
}

Stack& Stack::operator=(Stack& other const) {
	data[]delete;
	size = other.Size();
	capacity = size;
	data = new int[capacity];
	std::fill(other.begin(), other.end(), data);
	return *this;
}

