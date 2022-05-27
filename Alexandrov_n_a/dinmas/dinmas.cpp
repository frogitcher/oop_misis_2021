#include "dinmas.h"
dinmas::dinmas() {
	data = NULL;
	size = 0;
	capacity = 0;
}
dinmas::dinmas(size_t size_, int value) {
	size = size_;
	capacity = size_;
	data = new int[size];
	std::fill(data, data + size, value);
}
dinmas::dinmas(const dinmas& other) {
	size = other.size;
	capacity = other.capacity;
	data = new int[other.capacity];
	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[i];
	}
}
dinmas::dinmas(const std::initializer_list<int>& list) {
	size = list.size();
	capacity = list.size();
	data = new int[list.size()];
	int count = 0;
	for (auto i : list) {
		data[count] = i;
		count += 1;
	}
}
dinmas::~dinmas() {
	delete[] data;
}
int& dinmas::operator[](size_t i) const {
	return *(data + i);
}
int& dinmas::at(size_t i) const {
	if (i >= Size()) {
		throw "Going beyond the borders!";
	}
	return *(data + i);
}
void dinmas::Resize(size_t new_size) {
	if (new_size > size) {
		capacity = new_size * 2 + 1;
		int* newArr = new int[capacity];
		for (int i = 0; i < new_size; i++) {
			if (i < size) {
				newArr[i] = data[i];
			}
			else {
				newArr[i] = 0;
			}		
		}
		delete[] data;
		data = newArr;
		size = new_size;
	}
	size = new_size;
}
void dinmas::push_back(int value) {
	Resize(size + 1);
	(*this)[size - 1] = value;
}
void dinmas::Clear() {
	size = 0;
}
void dinmas::Erase(size_t index) {
	if (size == 0) {
		throw "Array size 0";
	}
	if (index > size) {
		throw "Out of range";
	}
	for (int i = index; i < size; ++i) {
		data[i] = data[i + 1];
	}
	--size;
}
void dinmas::assign(size_t new_size, int value) {
	Resize(new_size);
	for (int i = 0; i < new_size; i++) {
		(*this)[i] = value;
	}
}
int* dinmas::begin() const {
	return data;
}
int* dinmas::end() const {
	return data + size;
}
void dinmas::swap(dinmas& other) {
	std::swap(data, other.data);
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
}
void dinmas::pop_back() {
	if (size == 0) {
		throw "Array size 0";
	}
	--size;
}
void dinmas::insert(const int index, const int value) {
	if (size < 0) {
		throw "index must not be less than 0";
	}
	if (index > size) {
		throw "Out of range";
	}
	Resize(size + 1);
	for (int i = size - 1; i > index; i--) {
		(*this)[i] = (*this)[i - 1];
	}
	(*this)[index] = value;
}
size_t dinmas::Size() const {
	return size;
}
size_t dinmas::Capacity() const {
	return capacity;
}
bool dinmas::Empty() const {
	return (size == 0);
}
bool dinmas::operator==(const dinmas& r) const {
	int flag = 0;
	if (size == r.size) {
		flag = 1;
		for (int i = 0; i < size; i++) {
			if (data[i] != r.data[i]) {
				flag = 2;
			}
		}
	}
	if (flag == 1) {
		return true;
	}
	else {
		return false;
	}
}
bool dinmas::operator!=(const dinmas& r) const {
	return !(*this == r);
}
void dinmas::operator= (const dinmas& other) {
	size = other.size;
	if (other.size > capacity) {
		capacity = other.capacity;
		int* newArr = new int[other.capacity];
		for (int i = 0; i < other.size; i++) {
			newArr[i] = other.data[i];
		}
		delete[] data;
		data = newArr;
	}
	else {
		for (int i = 0; i < other.size; i++) {
			data[i] = other.data[i];
		}
	}
}
