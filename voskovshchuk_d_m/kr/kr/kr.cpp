#include <iostream>
#include "kr.h"

vec::vec(unsigned _int64 size) {
	vec::size = size;
	vec::data = std::vector <double> (size);
}

vec::vec(unsigned _int64 size, std::vector<double>& data) {
	vec::size = size;
	vec::data = data;
}

vec::~vec() {
}

double& vec::operator[](const unsigned _int64 rhs) {
	return vec::data[rhs];
}

vec vec::operator+(const vec& rhs) const {
	vec tmp(vec::size);
	for (unsigned _int64 i = 0; i < vec::size; i++)
		tmp.data[i] = vec::data[i] + rhs.data[i];
	return tmp;
}

vec vec::operator-(const vec& rhs) const {
	vec tmp(vec::size);
	for (unsigned _int64 i = 0; i < vec::size; i++)
		tmp.data[i] = vec::data[i] - rhs.data[i];
	return tmp;
}

vec vec::operator*(const _int64& rhs) const  {
	vec tmp(vec::size);
	for (unsigned _int64 i = 0; i < vec::size; i++)
		tmp.data[i] = vec::data[i] * rhs;
	return tmp;
}

vec vec::operator*(const vec& rhs) const {
	vec tmp(vec::size);
	for (unsigned _int64 i = 0; i < vec::size; i++)
		tmp.data[i] = vec::data[i] * rhs.data[i];
	return tmp;
}

void vec::operator=(const vec& other) {
	vec::size = other.size;
	vec::data = other.data;
}

bool vec::operator==(const vec& other) const {
	if (vec::size == other.size && vec::data == other.data)
		return 1;
	else
		return 0;
}

vec vec::normal() {
	double length = 0;
	vec tmp(vec::size);
	for (unsigned _int64 i = 0; i < vec::size; i++)
		length += vec::data[i] * vec::data[i];
	length = sqrt(length);
	for (unsigned _int64 i = 0; i < vec::size; i++)
		tmp.data[i] = vec::data[i] / length;
	return tmp;
}
