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
	data = new _int64[Size];
	for (int i = 0; i < Size; i++)
		data[i] = other.data[i];
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
	return (Size == 0 ? 1 : 0);
}

void dynamic::push_back(_int64 value) {
	if (Capacity == Size)
		this->resize(Capacity * 2 + 1);
	data[Size++] = value;
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
	Size--;
	for (int i = pos; i < Size; i++)
		data[i] = data[i + 1];
}

void dynamic::erase(_int64* pos) {
	_int64 tmp = pos - this->begin();
	this->erase(tmp);
}

void dynamic::resize(unsigned _int64 size) {
	if(size < 0)
		throw std::invalid_argument("Wrong sign of new size");
	_int64* tmp = new _int64[size];
	for (int i = 0; i < Size; i++)
		tmp[i] = data[i];
	delete[] data;
	data = tmp;
	Capacity = size;
}

void dynamic::assign(unsigned _int64 size, _int64 value) {
	if (size < 0)
		throw std::invalid_argument("Wrong sign of new size");
	this->resize(size);
	Size = size;
	std::fill(data, data + Size, value);
}

void dynamic::insert(unsigned _int64 pos, _int64 value) {
	if (0 > pos || pos > Size)
		throw std::invalid_argument("Position outside of array");
	if (Capacity == Size)
		this->resize(Capacity * 2 + 1);
	for (int i = Size; i != pos; i--)
		data[i] = data[i - 1];
	Size++;
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

_int64* dynamic::begin() {
	return data;
}

_int64* dynamic::end() {
	return data + Size;
}

_int64& dynamic::at(unsigned _int64 pos) const {
	if (0 > pos || pos >= Size)
		throw std::invalid_argument("Position outside of array");
	return *(data + pos);
}

_int64& dynamic::operator[](unsigned _int64 pos) const {
	if (0 > pos || pos >= Size)
		throw std::invalid_argument("Position outside of array");
	return *(data + pos);
}

dynamic& dynamic::operator=(const dynamic& rhs) {
	Size = rhs.Size;
	if (Size > Capacity) {
		Capacity = Size;
		delete[] data;
		_int64* tmp = new _int64[Size];
		data = tmp;
		delete[] tmp;
	}
	for (int i = 0; i < Size; i++)
		data[i] = rhs.data[i];
	return *this;
}

bool dynamic::operator==(const dynamic& rhs) const {
	if (Size == rhs.Size) {
		for (int i = 0; i < Size; i++)
			if (data[i] != rhs.data[i])
				return 0;
			return 1;
	}
	else
		return 0;
}

bool dynamic::operator!=(const dynamic& rhs) const {
	if (Size == rhs.Size) {
		for (int i = 0; i < Size; i++)
			if (data[i] != rhs.data[i])
				return 1;
		return 0;
	}
	else
		return 1;
}