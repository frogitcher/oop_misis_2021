#pragma once
#include <stdexcept>
#include "matrix.h"

template <typename T>
class Table :public Base<T> {
public:
	Table(size_t r, size_t c, T value = (T));
	T* operator[](size_t i) const override;
	Table(const Table<T>& other);
	Table(std::initializer_list<std::initializer_list<T>> list);
	Table() = default;
	~Table();

	void Del() override;
	void Resize(size_t n_r, size_t n_c, T value = (T)0) override;
	T& Get(size_t n_r, size_t n_c) const override;

	bool operator==(const Table < T>& other) const;
	bool operator!=(const Table < T>& other) const;

	Table<T> operator +(const Table<T>& other) const;
	Table<T> operator -(const Table<T>& other) const;
	Table<T> operator *(const Table<T>& other) const;
	Table<T>& operator =(const Table<T>& other);

	Table<T>& operator +=(const Table<T>& other);
	Table<T>& operator -=(const Table<T>& other);
	Table<T>& operator *=(const Table<T>& other);
private:
	T** data = nullptr;
};

template <typename T>
Table<T>::Table(size_t r, size_t c, T value):Base<T>(r,c){
	data = new T * [r];
	for (int i = 0;i < this->n_r;i++) {
		data[i] = new T[c];
		std::fill(data[i], data[i]+c, value);
	}
}

template <typename T>
T* Table<T>::operator[](size_t i) const {
	return data[i];
}

template <typename T>
Table<T>::Table(std::initializer_list<std::initializer_list<T>> list):Base<T>(list.size(),list.begin()->size()){
	T** new_data = new T * [this->n_r];
	for (int i = 0;i < this->n_r;i++) {
		new_data[i] = new T[this->n_c];
	}
	int c = 0, f = 0;
	for (const auto& i : list) {
		for (const auto& b : i) {
			new_data[c][f] = b;
			f++;
		}
		c++;
		f = 0;
	}
	delete[] data;
	data = new_data;

}

template <typename T>
Table<T>::Table(const Table<T>& other):	Base<T>(other.n_r,other.n_c) {
	*this = other;
}

template <typename T>
Table<T>::~Table() {
	Del();
}

template <typename T>
void Table<T>::Del() {
	delete[] data;
	this->n_r = 0;
	this->n_c = 0;
}

template <typename T>
void Table<T>::Resize(size_t n_r, size_t n_c, T value) {
	*this = Table<T>(n_r, n_c, value);
}

template <typename T>
T& Table<T>::Get(size_t r, size_t c) const {
	if (r < this->n_r && c < this->n_c) {
		return data[r][c];
	}
	throw std::out_of_range("chel ti v mute");
}

template <typename T>
bool Table<T>::operator==(const Table <T>& other) const {
	if (this->n_r == other.n_r && this->n_c == other.n_c) {
		for (int i = 0;i < this->n_r;i++) {
			if (!std::equal(data[i], data[i]+ this->n_c, other.data[i])) {
				return false;
			}
		}
		return true;
	}
	return false;
}

template <typename T>
bool Table<T>::operator!=(const Table <T>& other) const {
	return !(*this == other);
}

template <typename T>
Table<T>& Table<T>::operator +=(const Table<T>& other) {
	if (this->n_r == other.n_r && this->n_c == other.n_c) {
		for (int i = 0;i < this->n_r;i++) {
			for (int b = 0;b < this->n_c;b++) {
				data[i][b] += other.data[i][b];
			}
		}
		return *this;
	}
	throw std::invalid_argument("chel ti v mute");
}

template <typename T>
Table<T>& Table<T>::operator -=(const Table<T>& other) {
	if (this->n_r == other.n_r && this->n_c == other.n_c) {
		for (int i = 0;i < this->n_r;i++) {
			for (int b = 0;i < this->n_c;i++) {
				data[i][b] -= other.data[i][b];
			}
		}
		return *this;
	}
	throw std::invalid_argument("chel ti v mute");
}

template <typename T>
Table<T>& Table<T>::operator *=(const Table<T>& other) {
	if (this->n_ñ == other.n_r) {
		T** new_data = new T[this->n_r][other.n_c];
		for (int i = 0; i < this->n_r; i++) {
			for (int j = 0; j < other.n_c; j++) {
				for (int k = 0; k < other.n_r; k++) {
					new_data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}
		delete[] data;
		data = new_data;
	}else {
		throw std::invalid_argument("impossible");
	}
	this->n_c = other.n_c;
}

template <typename T>
Table<T> Table<T>::operator +(const Table<T>& other) const {
	return *this += other;
}

template <typename T>
Table<T> Table<T>::operator -(const Table<T>& other) const {
	return *this -= other;
}

template <typename T>
Table<T> Table<T>::operator *(const Table<T>& other) const {
	return *this *= other;
}

template <typename T>
Table<T>& Table<T>::operator =(const Table<T>& other) {
	T** new_data = new T*[other.n_r];
	delete[] data;
	for (int i = 0;i < other.n_r;i++) {
		new_data[i] = new T [other.n_c];
		for (int b = 0;b < other.n_c;b++) {
			new_data[i][b] = other.data[i][b];
		}
	}
	data = new_data;
	this->n_r = other.n_r;
	this->n_c = other.n_c;
	return *this;
}








