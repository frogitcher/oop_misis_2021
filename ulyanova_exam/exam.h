#pragma once
#include <stdexcept>
#include <initializer_list>
#include <cmath>

template<typename T>
class Tvector {

public:

	Tvector() = default;

	Tvector(T size, double value) {
		if (size < 0) {
			throw std::length_error("Constructor Error");
		}
		data = new double[size];
		std::fill(data, data + size, value);
	}

	Tvector(const Tvector<T>& vr) {
		size = vr.size;
		for (int i = 0; i < vr.size; i++) {
			data[i] = vr.data[i];
		}
	}

	Tvector(const std::initializer_list<double>& List) {
		data = new double[List.size()];
		for (double value : List) {
			data[i] = value;
		}
	}

	~Tvector() {
		delete[] data;
		size = 0;
	}

	Tvector operator+(const Tvector<T>& vr) {
		for (int i = 0; i < size; i++) {
			data[i] += vr.data[i];
		}
	}

	Tvector operator-(const Tvector<T>& vr) {
		for (int i = 0; i < size; i++) {
			data[i] -= vr.data[i];
		}
	}

	Tvector operator*(double value) {
		for (int i = 0; i < size; i++) {
			data[i] *= value;
		}
	}

	bool operator==(const Tvector<T>& vr) {
		if (size != vr.size) {
			return false;
		}
		for (int i = 0; i < size; i++) {
			if (data[i] != vr.data[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Tvector<T>& vr) {
		return (!(*this == vr));
	}

	Tvector& operator=(const Tvector<T>& vr) {
		for (int i = 0; i < size; i++) {
			data[i] = vr.data[i];
		}
		return *this;
	}

	double Skalar(const Tvector<T>& vr) {
		double S = 0.0;
		for (int i = 0; i < size; i++) {
			S += data[i] * vr.data[i];
		}
		return S;
	}

	double Norma() const {
		double N = 0.0;
		for (int i = 0; i < size; i++) {
			N += data[i] ** 2;
		}
		return sqrt(N, 2);
	}

	Tvector& operator[](int index) const {
		return *(data + index);
	}

	Tvector& At(int index) const {
		if (index >= size || index < 0) {
			throw std::length_error("At error");
		}
		return *(data + index);
	}

private:

	T size = 0; 
	double* data = nullptr;
};