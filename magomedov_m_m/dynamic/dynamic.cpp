#include <stdexcept>
#include "dynamic.h"


Dynamic::Dynamic(size_t _size, int value) :size(_size),capacity(_size), data(new int[_size]) {
	std::fill(data, data + size, value);
}
Dynamic::Dynamic(const Dynamic& other) :size(other.size), capacity(other.capacity), data(new int[other.size]) {
	std::copy(other.data, other.data + other.size, data);
}
Dynamic::Dynamic(const std::initializer_list <int>& list) : size(list.size()), capacity(list.size()), data(new int[list.size()]){
	std::copy(list.begin(), list.end(), data);
}
Dynamic::~Dynamic() {
	delete[] data;
}
size_t Dynamic::Size() const {
	return size;
}
size_t Dynamic::Capacity() const {
	return capacity;
}
bool Dynamic::Empty() const {
	return(size == 0);
}

int& Dynamic::operator[](size_t i)const
{
	if (i > size) {
		throw std::out_of_range("You Fуck");
	}
	else {
		return *(data + i);
	}
}
int& Dynamic::at(size_t i) const{
	if (i > size) {
		throw std::out_of_range("You went out of the array");
	}
	else {
		return *(data + i);
	}
}
void Dynamic::push_back(int value) {
	if (size == capacity) {
		int* new_data = new int[capacity * 2 +1];
		std::copy(data, data + capacity, new_data);
		delete[] data;
		data = new_data;
		capacity *= 2;
	}
	data[size++] = value;
}
void Dynamic::pop_back() {
	if (size == 0) {
		throw std::out_of_range("You went out of the array");
	} else{

		size -- ;
	}
}
void Dynamic::clear() {
	size = 0;
	int* new_data = new int[0];
	delete[] data;
	data = new_data;
	capacity = 0;
}
void Dynamic::erase(size_t index) {
	std::copy(data + index+1, data+size, data+index);//сдвиг влево от индекса
	--size;
}
void Dynamic::insert(size_t index, int value){
	if (size == capacity) {
		int* new_data = new int[capacity * 2 + 1];
		std::copy(data, data + capacity, new_data);
		delete[] data;
		data = new_data;
		capacity *= 2;
	}
	std::copy(data + index, data + size, data + index + 1);
	++size;
	data[index] = value;
}
void Dynamic::assign(size_t new_size, int value) {
	if (size < new_size) {
		data = new int[new_size];
		std::fill(data, data + new_size, value);
		size = new_size;
	}
	else {
		std::fill(data, data + new_size, value);
	}
}
void Dynamic::resize(size_t new_size) {
	if (new_size > size) {
		capacity += new_size;
		int* new_data = new int[new_size];
		std::copy(data, data + size, new_data);
		delete[] data;
		data = new_data;
		std::fill(data + size, data + new_size, 0);
		size = new_size;
	}
	else {
		std::fill(data + new_size, data + size, 0);
		size = new_size;
	}
}
void Dynamic::swap(Dynamic& other) {
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}
int* Dynamic::begin() {
	return data;
}
int* Dynamic::end() {
	return (data+size);
}
bool Dynamic::operator==(const Dynamic& other) const{
	bool b = false;
	if (size == other.size) {
		b = true;
		for (int i = 0;i < size;i++) {
			if (data[i] != other.data[i]) {
				b = false;
				break;
			}
		}
	}
	return b;
}
bool Dynamic::operator !=(const Dynamic& other) const {
	return !(*this == other);
}
Dynamic& Dynamic::operator=(const Dynamic& other) {
	
	(*this).resize(other.Size());
	std::copy(other.data, other.data + other.size, data);
	return (*this);
}

/*
int main() {
	Dynamic a({ 1,2,3,4 });
	Dynamic b({ 1,2,3,4 });
	std::cout << a.Size()<<" "<<(a==b);
	return 0;
}*/
