#pragma once
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <stddef.h>

template <size_t _size>
class VecDub{
public:
	VecDub(const double init[size]) {
		for (size_t i = 0; i < size; i++) {
			cords[i] = init[i];
		}
	}
	VecDub(const std::initializer_list<int>& list) {
		if (list.size != size) {
			throw std::bad_array_new_length("Init List Size != Vector Size!");
		}
		std::copy(list.begin(), list.end(), cords);
	}
	~VecDub(){
		delete[] cords;
		delete size;
	}
	double operator*(const VecDub& other) const {
		double res = 0;
		for (size_t i = 0; i < size; i++) {
			res += cords[i] * other.cords[i];
		}
		return res;
	}
	inline double operator[] (size_t i) {
		return cords[i];
	}
	double at(size_t i) {
		if (i > size) {
			throw std::out_of_range("Index Out Of Range");
		}
		return cords[i];
	}
	VecDub& operator+=(const VecDub& other) {
		for (size_t i = 0; i < size; i++) {
			cords[i] += other.cords[i];
		}
		return *this;
	}
	VecDub& operator-=(const VecDub& other) {
		for (size_t i = 0; i < size; i++) {
			cords[i] += other.cords[i];
		}
	}
	VecDub operator+(const VecDub& other) const{
		return (*this) += other;
	}
	VecDub operator-(const VecDub& other) const {
		return (*this) -= other;
	}
	VecDub& operator+=(const double other) {
		for (size_t i = 0; i < size; i++) {
			cords[i] += other;
		}
		return *this;
	}
	VecDub& operator-=(const double other) {
		for (size_t i = 0; i < size; i++) {
			cords[i] -= other;
		}
		return *this;
	}
	VecDub& operator*=(const double other) {
		for (size_t i = 0; i < size; i++) {
			cords[i] *= other;
		}
		return *this;
	}
	VecDub& operator/=(const double other) {
		for (size_t i = 0; i < size; i++) {
			cords[i] /= other;
		}
		return *this;
	}
	VecDub operator-(const double other) const {
		return (*this) -= other;
	}
	VecDub operator+(const double other) const {
		return (*this) += other;
	}
	VecDub operator-(const double other) const{
		return (*this) *= other;
	}
	VecDub operator/(const double other) const {
		return (*this) /= other;
	}
	double Length() const{
		double res = 0;
		for (size_t i = 0; i < size; i++) {
			res+=cords[i]*cords[i];
		}
		return sqrt(res);
	}
	inline size_t Size() const {
		return size;
	}
	bool operator==(const VecDub& other) const{
		if (Length() != other.Length()) {
			return false;
		}
		for (size_t i = 0; i < size; i++) {
			if (cords[i] != other.cords[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator!=(const VecDub& other) const {
		return !((*this)== other);
	}
private:
	const size_t size = _size;
	double cords[size];
};