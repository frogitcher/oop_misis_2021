#include "dynamicarray.h"
#include <stdexcept>

dynamicarray::dynamicarray(size_t _size, int value)
	: size(_size), capacity(_size) {
	data = new int[capacity];
	std::fill(data, data + size, value);
}

dynamicarray::dynamicarray(const dynamicarray& other)
	: size(other.size), capacity(other.capacity) {
	data = new int[capacity];
	std::copy(other.data, other.data + size, data);
}

dynamicarray::dynamicarray(const std::initializer_list<int>& list)
	: size(list.size()), capacity(list.size()) {
	data = new int[capacity];
	std::copy(list.begin(), list.end(), data);
}

dynamicarray::~dynamicarray() {
	delete[] data;
}

void dynamicarray::reallocate(size_t new_capacity) {
	int* new_data = new int[new_capacity];
	std::copy(data, data + size, new_data);
	delete[] data;
	data = new_data;
	capacity = new_capacity;
}

size_t dynamicarray::Size() const
{
	return size;
}

size_t dynamicarray::Capacity() const
{
	return capacity;
}

bool dynamicarray::empty() const
{
	return size == 0;
}

int& dynamicarray::operator[](size_t index) const
{
	return *(data + index);
}

int& dynamicarray::at(size_t index) const
{
	if (index >= size)
		throw std::invalid_argument("index out of range");
	else
		return data[index];
}

void dynamicarray::push_back(int value) {
	if (size == capacity)
		reallocate(2 * capacity + 1);
	data[size++] = value;
}

void dynamicarray::pop_back()
{
	if (!size)
		throw std::invalid_argument("empty array before pop");
	else
		size--;
}

void dynamicarray::clear()
{
	size = 0;
}

void dynamicarray::erase(size_t index)
{
	if (index < 0 || index >= size)
		throw std::invalid_argument("index out of range");
	else
		std::copy(data + index + 1, data + size, data + index);
	size--;
}

void dynamicarray::assign(size_t _size, int value)
{
	if (_size < 0)
		throw std::invalid_argument("bad array new length");
	if (_size >= capacity)
		reallocate(std::max(_size, 2 * capacity));
	size = _size;
	std::fill(data, data + size, value);
}

void dynamicarray::resize(size_t new_size)
{
	if (new_size < 0)
		throw std::invalid_argument("bad array new length");
	if (new_size >= capacity) {
		reallocate(std::max(new_size, 2 * capacity));
	}
	std::fill(data + size, data + new_size, 0);
	size = new_size;
}

void dynamicarray::swap(dynamicarray& other)
{
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(data, other.data);
}

void dynamicarray::insert(size_t index, int value)
{
	if (index > size || index < 0)
		throw std::invalid_argument("index out of range");
	push_back(0);
	std::copy_backward(data + index, data + size - 1, data + size);
	data[index] = value;
}

int* dynamicarray::begin() const
{
	return data;
}

int* dynamicarray::end() const
{
	return data+size;
}

bool dynamicarray::operator==(const dynamicarray& other) const
{
	return std::equal(data, data + size, other.data, other.data + other.size);
}

bool dynamicarray::operator!=(const dynamicarray& other) const
{
	return !(*this == other);
}

dynamicarray& dynamicarray::operator=(const dynamicarray& other)
{
	resize(other.size);
	std::copy(other.data, other.data + other.size, data);
	return *this;
}
