#pragma once
#include "matrix.h"
#include <initializer_list>
#include <stdexcept>

template <typename T>
class FlatMatrix: public BaseMatrix<T> {
public:
	FlatMatrix(int64_t row = 0, int64_t col = 0, T filler = T(0));
	FlatMatrix(const FlatMatrix<T>& other);
	FlatMatrix(std::initializer_list<std::initializer_list<T>> list);
	~FlatMatrix();

	T* operator[](int64_t row);

	void resize(int64_t r, int64_t c, const T filler = T(0)) override;
	T& get(int64_t r, int64_t c) const override;

	FlatMatrix<T>& operator=(const FlatMatrix<T>& rhs);
	FlatMatrix<T>& operator+=(const FlatMatrix<T>& rhs);
	FlatMatrix<T>& operator-=(const FlatMatrix<T>& rhs);
	FlatMatrix<T>& operator*=(const FlatMatrix<T>& rhs);

	bool operator==(const FlatMatrix<T>& rhs) const;
	bool operator !=(const FlatMatrix<T>& rhs) const;
	void diag(int64_t r, const T filler) override;

private:
	T* matrix = nullptr;
};

template <typename T>
FlatMatrix<T> operator+(const FlatMatrix<T>& lhs, const FlatMatrix<T>& rhs) {
	FlatMatrix<T> res(rhs);
	res += lhs;
	return res;
}

template <typename T>
FlatMatrix<T> operator-(const FlatMatrix<T>& lhs, const FlatMatrix<T>& rhs) {
	FlatMatrix<T> res(lhs);
	res -= rhs;
	return res;
}

template <typename T>
FlatMatrix<T> operator*(const FlatMatrix<T>& lhs, const FlatMatrix<T>& rhs) {
	FlatMatrix<T> res(lhs);
	res *= rhs;
	return res;
}

template <typename T>
FlatMatrix<T> operator+(const FlatMatrix<T>& lhs, const T& rhs) {
	FlatMatrix<T> res(lhs);
	if (res.IsSquare()) {
		res.diag(res.rows(), rhs);
		res += lhs;
	}
	else {
		throw std::logic_error("you can add up value only to square matrix");
	}
	return res;
}

template <typename T>
FlatMatrix<T> operator-(const FlatMatrix<T>& lhs, const T& rhs) {
	FlatMatrix<T> res(lhs);
	if (res.IsSquare()) {
		FlatMatrix<T> sing(lhs);
		sing.diag(res.rows(), rhs);
		res -= sing;
	}
	else {
		throw std::logic_error("you can substruct value only from square matrix");
	}
	return res;
}

template <typename T>
FlatMatrix<T> operator*(const FlatMatrix<T>& lhs, const T& rhs) {
	FlatMatrix<T> res(lhs);
	for (int i = 0; i < res.rows(); i++) {
		for (int j = 0; j < res.colums(); j++) {
			res[i][j] *= rhs;
		}
	}
	return res;
}

template <typename T>
FlatMatrix<T>::FlatMatrix(int64_t row = 0, int64_t col = 0, T filler = T(0))
	: BaseMatrix<T>(row, col) {
	if (row < 0 || col < 0) {
		throw std::invalid_argument("the number of rows and colums must be positive");
	}
	matrix = new T[row_ * col_];
	std::fill(matrix, matrix + (row_ * col_), filler);
}

template <typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T>& other)
	: BaseMatrix<T>(other.row_, other.col_) {
	matrix = new T[row_ * col_];
	std::copy(other.matrix, other.matrix + (row_ * col_), matrix);
}

template <typename T>
FlatMatrix<T>::FlatMatrix(std::initializer_list<std::initializer_list<T>> list)
	: BaseMatrix<T>(list.size(), list.begin()->size()) {
	matrix = new T[row_ * col_];
	for (int i = 0; i < row_; i++) {
		if ((list.begin() + i)->size() != col_) {
			throw std::invalid_argument("the number of elements in each row must be same");
		}
		std::copy((list.begin() + i)->begin(), (list.begin() + i)->begin() + col_, matrix + (i * col_));
	}
}

template <typename T>
FlatMatrix<T>::~FlatMatrix() {
	delete[] matrix;
}

template <typename T>
T* FlatMatrix<T>::operator[](int64_t row) {
	return matrix + col_ * row;
}

template <typename T>
void FlatMatrix<T>::resize(int64_t r, int64_t c, const T filler = T(0)) {
	if (r < 0 || c < 0) {
		throw std::invalid_argument("index must be positive number");
	}
	delete[] matrix;
	matrix = new T[r * c];
	std::fill(matrix, matrix + r * c, filler);
	row_ = r;
	col_ = c;
}

template <typename T>
T& FlatMatrix<T>::get(int64_t r, int64_t c) const {
	if (r > row_ || r < 0 || c > col_ || c < 0) {
		throw std::out_of_range("index out of range");
	}
	return *(matrix + r * col_ + c);
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator=(const FlatMatrix<T>& rhs) {
	resize(rhs.row_, rhs.col_);
	std::copy(rhs.matrix, rhs.matrix + (row_ * col_), matrix);
	return *this;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator+=(const FlatMatrix<T>& rhs) {
	if (row_ == rhs.row_ && col_ == rhs.col_) {
		for (int i = 0; i < row_ * col_; i++) {
			matrix[i] = matrix[i] + rhs.matrix[i];
		}
	}
	else {
		throw std::logic_error("you can not add up matrix of different size");
	}
	return *this;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator-=(const FlatMatrix<T>& rhs) {
	if (row_ == rhs.row_ && col_ == rhs.col_) {
		for (int i = 0; i < row_ * col_; i++) {
			matrix[i] = matrix[i] - rhs.matrix[i];
		}
	}
	else {
		throw std::logic_error("you can not substruct matrix of different size");
	}
	return *this;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const FlatMatrix<T>& rhs) {
	if (col_ == rhs.row_) {
		FlatMatrix temp(*this);
		resize(row_, rhs.col_);
		int r = 0;
		for (int i = 0; i < row_ * col_; i++) {
			r = i;
			if (i % rhs.row_ != 0) r = i - (i % rhs.row_);
			if (rhs.row_ == 1) r = i / rhs.col_;
			for (int j = i % rhs.col_; j < rhs.row_ * rhs.col_; j = j + rhs.col_) {
				matrix[i] += temp.matrix[r] * rhs.matrix[j];
				r++;
			}
		}
	}
	else {
		throw std::logic_error("you can only multiply matrix sizes {m*n} and {n*k}");
	}
	return *this;
}

template <typename T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T>& rhs) const {
	return (std::equal(matrix, matrix + row_ * col_, rhs.matrix, rhs.matrix + rhs.row_ * rhs.col_) && (row_ == rhs.row_) && (col_ == rhs.col_));
}

template <typename T>
bool FlatMatrix<T>::operator !=(const FlatMatrix<T>& rhs) const {
	return !(this == rhs);
}

template <typename T>
void FlatMatrix<T>::diag(int64_t r, const T filler) {
	resize(r, r);
	int temp = 0;
	for (int64_t i = 0; i < (row_ * col_); i = i + row_) {
		matrix[i + temp++] = filler;
	}
}

