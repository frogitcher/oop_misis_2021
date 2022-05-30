#include "dynamic.h"
#include <stdexcept>
#include <vector>

dynamic::dynamic(size_t size) {
	Size = size;
	Capacity = size;
	data = new _int64[size];
}

dynamic::dynamic(size_t size, _int64 value) {
	Size = size;
	Capacity = size;
	data = new _int64[size];
	std::fill(data, data + size, value);
}

dynamic::dynamic(const std::initializer_list<_int64>& list) {
	Size = list.size();
	Capacity = list.size();
	data = new _int64[list.size()];
	unsigned _int64 i = 0;
	for (auto elem : list)
		data[i++] = elem;
}

dynamic::dynamic(const dynamic& other) {
	Size = other.Size;
	Capacity = other.Capacity;
	data = new _int64[Capacity];
	std::copy(other.begin(), other.end(), this->begin());
}

dynamic::~dynamic() {
	delete[] data;
}

size_t dynamic::size() const {
	return Size;
}

size_t dynamic::capacity() const {
	return Capacity;
}

bool dynamic::empty() const {
	return (Size == 0);
}

void dynamic::push_back(_int64 value) {
	this->resize(Size + 1);
	data[Size - 1] = value;
}

void dynamic::pop_back() {
	Size--;
}

void dynamic::clear() {
	Size = 0;
}

void dynamic::erase(unsigned _int64 pos) {
	if (0 > pos || pos >= Size)
		throw std::invalid_argument("Position outside of array");
	std::copy(this->begin() + pos + 1, this->end(), this->begin() + pos);
	Size--;
}

void dynamic::erase(_int64* pos) {
	_int64 tmp = pos - this->begin();
	this->erase(tmp);
}

void dynamic::resize(unsigned _int64 size) {
	if(size < 0)
		throw std::invalid_argument("Wrong sign of new size");
	while (Capacity < size) {
		_int64* tmp = new _int64[Capacity * 2 + 1];
		std::copy(this->begin(), this->end(), tmp);
		delete[] data;
		data = tmp;
		Capacity = Capacity * 2 + 1;
	}
	std::fill(this->begin() + Size, this->begin() + size, 0);
	Size = size;
}

void dynamic::assign(unsigned _int64 size, _int64 value) {
	if (size < 0)
		throw std::invalid_argument("Wrong sign of new size");
	this->resize(size);
	std::fill(data, data + Size, value);
}

void dynamic::insert(unsigned _int64 pos, _int64 value) {
	if (0 > pos || pos > Size)
		throw std::invalid_argument("Position outside of array");
	this->resize(Size + 1);
	std::copy(this->begin() + pos, this->end() - 1, this->begin() + pos + 1);
	data[pos] = value;
}

void dynamic::insert(_int64* pos, _int64 value) {
	_int64 tmp = pos - this->begin();
	this->insert(tmp, value);
}

void dynamic::swap(dynamic& other) {
	std::swap(Size, other.Size);
	std::swap(Capacity, other.Capacity);
	std::swap(data, other.data);
}

_int64* dynamic::begin() const {
	return data;
}

_int64* dynamic::end() const {
	return data + Size;
}

_int64& dynamic::at(unsigned _int64 pos) const {
	return *(data + pos);
}

_int64& dynamic::operator[](unsigned _int64 pos) const {
	return *(data + pos);
}

dynamic& dynamic::operator=(const dynamic& rhs) {
	Size = rhs.Size;
	if (Size > Capacity) {
		Capacity = Size;
		delete[] data;
		_int64* tmp = new _int64[Size];
		data = tmp;
	}
	std::copy(rhs.begin(), rhs.end(), data);
	return *this;
}

bool dynamic::operator==(const dynamic& rhs) const {
	if (Size == rhs.Size)
		return std::equal(this->begin(), this->end(), rhs.begin(), rhs.end());
	else
		return 0;
}

bool dynamic::operator!=(const dynamic& rhs) const {
	return !(*this == rhs);
}