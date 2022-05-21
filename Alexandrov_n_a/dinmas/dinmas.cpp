#include "dinmas.h"
dinmas::dinmas() {
	data = NULL;
	size = 0;
}
dinmas::dinmas(size_t size, int value) {
	data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = value;
	}
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
	if (new_size <= capacity) {
		return;
	}
	capacity = new_size * 2 + 1;
	int* newArr = new int[capacity];
	for (int i = 0; i < size; i++) {
		newArr[i] = data[i];
	}
	delete[] data;
	data = newArr;
}
void dinmas::push_back(int value) {
	Resize(size + 1);
	(*this)[size] = value;
	size++;
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
	int* newArr = new int[size - 1];
	int flag = 0;
	for (int i = 0; i < size - 1; i++) {
		if (i == index) {
			flag = 1;
			newArr[i] = data[i + 1];
		}
		else {
			if (flag == 0) {
				newArr[i] = data[i];
			}
			else {
				newArr[i] = data[i + 1];
			}
		}
	}
	size--;
	delete[] data;
	data = newArr;
}
void dinmas::assign(size_t new_size, int value) {
	Resize(new_size);
	for (int i = 0; i < new_size; i++) {
		(*this)[i] = value;
	}
	size = new_size;
}
int* dinmas::begin() {
	return data;
}
int* dinmas::end() {
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
	int* newArr = new int[size - 1];
	int flag = 0;
	for (int i = 0; i < size - 1; i++) {
		newArr[i] = data[i];
	}
	size--;
	delete[] data;
	data = newArr;
}
void dinmas::insert(const int index, const int value) {
	if (size < 0) {
		throw "index must not be less than 0";
	}
	if (index > size) {
		throw "Out of range";
	}
	Resize(size + 1);
	for (int i = size; i > index; i--) {
		(*this)[i] = (*this)[i - 1];
	}
	(*this)[index] = value;
	size++;
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
	capacity = other.capacity;
	data = new int[other.capacity];
	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[i];
	}
}