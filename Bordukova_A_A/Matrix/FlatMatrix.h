#pragma once
#include "BaseMAtrix.h"
#include <ostream>

template <typename T>
class FlatMatrix : public BaseMatrix<T> {
public:

	//Constructors and destructors
	FlatMatrix(const size_t& r = 0, const size_t& c = 0, const T& value = 0);
	FlatMatrix(const std::initializer_list<std::initializer_list<T>>& list);
	FlatMatrix(const FlatMatrix<T>& other);
	~FlatMatrix();
	void Resize(const size_t& r, const size_t& c, const T& value) override;


	//Pointers
	inline T& Get(const size_t& r, const size_t& c) const override {
		return *(data + (this->num_columns * r) + c);
	}
	inline T* operator[](const size_t& r) const override {
		return data + (this->num_columns * r);
	}

	//Assignment
	FlatMatrix<T>& operator=(const FlatMatrix<T>& rhs);

	//Logical operators
	inline bool operator==(const FlatMatrix<T>& rhs) const {
		return (this->num_columns == rhs.num_columns && this->num_rows == rhs.num_rows && std::equal(data, data + (this->num_rows * this->num_columns), rhs.data));
	}
	inline bool operator!=(const FlatMatrix<T>& rhs) const {
		return !(*this == rhs);
	}

	//Arithmetical operators
	FlatMatrix<T> operator+(const FlatMatrix<T>& rhs) const;
	FlatMatrix<T>& operator+=(const FlatMatrix<T>& rhs);
	FlatMatrix<T> operator-(const FlatMatrix<T>& rhs) const;
	FlatMatrix<T>& operator-=(const FlatMatrix<T>& rhs);
	FlatMatrix<T> operator*(const FlatMatrix<T>& rhs) const;
	FlatMatrix<T>& operator*=(const FlatMatrix<T>& rhs);

	/*inline friend T* Get_Data(const FlatMatrix<T>& fm) {
		return fm.data;
	}*/

private:
	T* data = nullptr;

	void Reallocate(const size_t& r, const size_t& c) override;
};


//Constructors and destructors
template<typename T>
FlatMatrix<T>::FlatMatrix(const size_t& r, const size_t& c, const T& value) {
	this->num_rows = r;
	this->num_columns = c;
	data = new T[r * c];
	std::fill(data, data + (r * c), value);
}

template<typename T>
FlatMatrix<T>::FlatMatrix(const std::initializer_list<std::initializer_list<T>>& list) {
	this->num_rows = list.size();
	this->num_columns = list.begin()->size();
	data = new T[this->num_rows * this->num_columns];
	size_t pos = 0;
	for (auto row : list) {
		for (auto element : row) {
			data[pos] = element;
			++pos;
		}
	}
}

template<typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T>& other) {
	*this = other;
}

template<typename T>
FlatMatrix<T>::~FlatMatrix() {
	delete[] data;
}

template<typename T>
void FlatMatrix<T>::Resize(const size_t& r, const size_t& c, const T& value) {
	Reallocate(r, c);
	if (this->num_rows < r) {
		std::fill(data + (this->num_rows * this->num_columns), data + (r * c), value);
	}
	if (this->num_columns < c) {
		for (size_t i = 0; i < this->num_rows * this->num_columns; ++i) {
			std::fill(data + (this->num_columns * i), data + (this->num_columns * i) + c, value);
		}
	}
	this->num_rows = r;
	this->num_columns = c;
}

//Assignment
template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator=(const FlatMatrix<T>& rhs) {
	Reallocate(rhs.num_rows, rhs.num_columns);
	this->num_rows = rhs.num_rows;
	this->num_columns = rhs.num_columns;
	std::copy(rhs.data, rhs.data + (rhs.num_rows * rhs.num_columns), data);
	return *this;
}

//Arithmetical operators
template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T>& rhs) const {
	if (this->num_rows != rhs.num_rows || this->num_columns != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	return FlatMatrix<T>(*this) += rhs;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator+=(const FlatMatrix<T>& rhs) {
	if (this->num_rows != rhs.num_rows || this->num_columns != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	for (size_t i = 0; i < this->num_rows * this->num_columns; ++i) {
		data[i] += rhs.data[i];
	}
	return *this;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T>& rhs) const {
	if (this->num_rows != rhs.num_rows || this->num_columns != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	return FlatMatrix<T>(*this) -= rhs;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator-=(const FlatMatrix<T>& rhs) {
	if (this->num_rows != rhs.num_rows || this->num_columns != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	for (size_t i = 0; i < this->num_rows * this->num_columns; ++i) {
		data[i] -= rhs.data[i];
	}
	return *this;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& rhs) const {
	if (this->num_rows != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	return FlatMatrix<T>(*this) *= rhs;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const FlatMatrix<T>& rhs) {
	if (this->num_columns != rhs.num_rows) {
		throw std::invalid_argument("Number of the rows in the first matrix must be the same as the number of columns in the second one!");
	}
	FlatMatrix<T> res(this->num_rows, rhs.num_columns);
	for (size_t i = 0; i < this->num_rows; ++i) {
		for (size_t j = 0; j < rhs.num_columns; ++j) {
			T sum = 0;
			for (size_t k = 0; k < rhs.num_rows; ++k) {
				sum += data[(i * this->num_columns) + k] * rhs.data[(k * rhs.num_columns) + j];
			}
			res.data[(i * res.num_columns) + j] = sum;
		}
	}
	*this = res;
	return *this;
}


template<typename T>
void FlatMatrix<T>::Reallocate(const size_t& r, const size_t& c) {
	size_t cur_size = this->num_rows * this->num_columns;
	size_t new_size = r * c;
	if (cur_size < new_size) {
		T* new_data = new T[r * c];
		std::copy(data, data + cur_size, new_data);
		delete[] data;
		data = new_data;
	}
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const FlatMatrix<T>& fm) {
	for (size_t i = 0; i < fm.Rows(); ++i) {
		os << "| ";
		for (size_t j = 0; j < fm.Columns(); ++j) {
			os << fm[i][j] << " ";
		}
	}
	os << "|";
	return os;
}