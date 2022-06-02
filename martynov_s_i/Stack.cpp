#include <iostream>
#include "Stack.h"

Stack::Stack(size_t _size, int value) {
	int* new_data = new int[_size];
	std::fill(new_data, new_data + _size, value);
	data = new_data;
	size = _size;
	capacity = _size;
}

Stack::Stack(const std::initializer_list<int>& list) {
	int* new_data = new int[list.size()];
	std::copy(list.begin(), list.begin() + list.size(), new_data);
	data = new_data;
	size = list.size();
	capacity = list.size();
}

Stack::~Stack() {
	delete[] data;
}

void Stack::Push(const int value) {
	if (capacity > size) {
		data[size] = value;
		++size;
	}
	else {
		int* new_data = new int[capacity * 2];
		std::copy(data, data + size, new_data);
		new_data[size] = value;
		delete[] data;
		data = new_data;
		++size;
		capacity *= 2;
	}
}

void Stack::Pop() {
	if (size == 0) {
		throw "size = 0";
	}
	--size;
}

size_t Stack::Size() const {
	return size;
}

bool Stack::Empty() const {
	return size == 0;
}

int Stack::Get() const {
	if (size == 0) {
		throw "size = 0";
	}
	return data[size - 1];
}

bool Stack::operator==(const Stack& st) const {
	if (size == st.size && std::equal(data, data + size, st.data)) {
		return true;
	}
	return false;
}

bool Stack::operator!=(const Stack& st) const {
	return !(*this == st);
}

Stack& Stack::operator=(const Stack& st) {
	if (capacity >= st.capacity) {
		std::copy(st.data, st.data + st.size, data);
	}
	else {
		int* new_data = new int[std::max(capacity * 2, st.capacity)];
		std::copy(st.data, st.data + st.size, new_data);
		delete[] data;
		data = new_data;
		capacity = std::max(capacity * 2, st.capacity);
	}
	size = st.size;
	return *this;
}