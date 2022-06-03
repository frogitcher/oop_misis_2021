#include <stdexcept>
#include <algorithm>
#include "kr.h"

Set::Set(const size_t size, int value) : size(size)
{
	data = new int[size];
	std::fill(data, data + size, value);
}

int64_t Set::Size() const
{
	return size;
}

void Set::Insert(int value)
{
	if (Find(value) != -1) {
		return;
	}
	else {

	}
}

int Set::Find(int value)
{
	for (int i = 0; i < size; i++) {
		if (data[i] == value) {
			return i;
		}
	}
	return -1;
}

void Set::Erase(int64_t index)
{
	if (size == 0) {
		throw std::length_error("The array is empty!");
	}
	if (index < 0 || index >= size) {
		throw std::out_of_range("Out of range!");
	}
	for (int64_t i = index; i < size - 1; i++) {
		data[i] = data[i + 1];
	}
	size--;
}

Set& Set::operator=(const Set& rhs)
{
    size = rhs.size;
    std::copy(rhs.data, rhs.data + size, data);
    return *this;
}

int& Set::operator[](int index)
{
	return data[index];
}



Set::~Set()
{
	delete[] data;
}