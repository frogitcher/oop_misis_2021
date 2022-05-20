#include <stdexcept>
#include "dynamic.h"

Dynamic::Dynamic(size_t _size, int value) :size(_size),capacity(_size) {
	data = new int[size];
	std::fill(data, data + size, value);
}
Dynamic::Dynamic(const Dynamic& other) :size(other.size), capacity(other.capacity) {
	int* data = new int[other.size];
	std::copy(other.data, other.data + other.capacity, data);
}
Dynamic::Dynamic(const std::initializer_list <int>& list) : size(list.size()), capacity(list.size()) {
	int* data = new int[list.size()];
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
	return *(data + i);
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

int main() {
	Dynamic a(5, 14);
	a.clear();
	std::cout << a[1];
}





