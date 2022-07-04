#include "arrayd.h"
#include <stdexcept>
#include <algorithm>

int64_t get_cap(int64_t size) {
	int cap = 1;
	while (size > cap) {
		cap *= 2;
	}
	return cap;
}

void arrayd::realloc(int64_t new_cap) {
	int* new_data = new int[new_cap];
	std::copy(data, data + size, new_data);
	delete[] data;
	data = new_data;
	cap = new_cap;
}

arrayd::arrayd(int64_t _size, int val) : size(_size) {
	if (_size < 0) throw std::length_error("kooky array size: < 0");
	cap = get_cap(_size);
	data = new int[cap];
	std::fill(data, data + _size, val);
}

arrayd::arrayd(const arrayd& other) : cap(other.cap), size(other.size) {
	data = new int[cap];
	std::copy(other.data, other.data + size, data);
}

arrayd::arrayd(const std::initializer_list<int>& list) : size(list.size()) {
	cap = get_cap(list.size());
	data = new int[cap];
	std::copy(list.begin(), list.end(), data);
}

arrayd& arrayd::operator=(const arrayd& rhs) {
	resize(rhs.size);
	std::copy(rhs.data, rhs.data + size, data);
	return *this;
}

void arrayd::resize(int64_t new_size) {
	if (new_size < 0) throw std::length_error("negative array size");
	if (new_size > cap) realloc(get_cap(new_size));
	size = new_size;
}

void arrayd::push_back(int val) {
	if (size == cap) realloc(cap * 2);
	data[size++] = val;
}

void arrayd::pop_back() {
	if (size == 0) throw std::length_error("kovo ti popaesh?)");
	size--;
}

int& arrayd::operator[](int64_t i) const {
	if (i < 0 || i >= size) throw std::out_of_range("ny kuda???");
	return *(data + i);
}

void arrayd::assign(int64_t new_size, int val) {
	resize(new_size);
	std::fill(data, data + size, val);
}

void arrayd::swap(arrayd& other) {
	std::swap(size, other.size);
	std::swap(cap, other.cap);
	std::swap(data, other.data);
}

void arrayd::insert(int64_t i, int val) {
	if (i < 0 || i >= size) throw std::out_of_range("invalid insertion index");
	resize(size + 1);
	for (int j = size; j > i; j--) {
		data[j] = data[j - 1];
	}
	data[i] = val;
}

void arrayd::erase(int64_t i) {
	if (i < 0 || i >= size) throw std::out_of_range("invalid erasion index");
	for (int j = i; j < size - 1; j++) {
		data[j] = data[j + 1];
	}
	size--;
}

bool arrayd::operator==(const arrayd& rhs) const {
	return size == rhs.size && std::equal(begin(), end(), rhs.begin());
}
