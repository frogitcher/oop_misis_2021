#pragma once
#include "matrix.h"
#include <initializer_list>
#include <stdexcept>

template <typename T>
class TableMatrix : public BaseMatrix<T> {
public:
	TableMatrix(int64_t row = 0, int64_t col = 0, T filler = T(0));
	TableMatrix(int64_t row, T value);
	TableMatrix(const TableMatrix<T>& other);
	TableMatrix(std::initializer_list<std::initializer_list<T>> list);
	~TableMatrix();

	void resize(int64_t r, int64_t c, const T filler = T(0)) override;
	T* operator[](int64_t r);
	T& get(int64_t r, int64_t c) const override;
	TableMatrix<T>& operator=(const TableMatrix<T>& rhs);
	TableMatrix<T>& operator+=(const TableMatrix<T>& rhs);
	TableMatrix<T>& operator-=(const TableMatrix<T>& rhs);
	TableMatrix<T>& operator*=(const TableMatrix<T>& rhs);

	bool operator==(const TableMatrix<T>& rhs) const;	
	bool operator !=(const TableMatrix<T>& rhs) const;

	void diag(int64_t r, const T filler) override;
private:
	T** data = nullptr;
};

template <typename T>
TableMatrix<T> operator+(const TableMatrix<T>& lhs, const TableMatrix<T>& rhs) {
	TableMatrix<T> res(rhs);
	res += lhs;
	return res;
}

template <typename T>
TableMatrix<T> operator-(const TableMatrix<T>& lhs, const TableMatrix<T>& rhs) {
	TableMatrix<T> res(lhs);
	res -= rhs;
	return res;
}

template <typename T>
TableMatrix<T> operator*(const TableMatrix<T>& lhs, const TableMatrix<T>& rhs) {
	TableMatrix<T> res(lhs);
	res *= rhs;
	return res;
}

template <typename T>
TableMatrix<T> operator+(const TableMatrix<T>& lhs, const T& rhs) {
	TableMatrix<T> res(lhs);
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
TableMatrix<T> operator-(const TableMatrix<T>& lhs, const T& rhs) {
	TableMatrix<T> res(lhs);
	if (res.IsSquare()) {
		TableMatrix<T> sing(lhs);
		sing.diag(res.rows(), rhs);
		res -= sing;
	}
	else {
	throw std::logic_error("you can substruct value only from square matrix");
	}
	return res;
}

template <typename T>
TableMatrix<T> operator*(const TableMatrix<T>& lhs, const T& rhs) {
	TableMatrix<T> res(lhs);
	for (int i = 0; i < res.rows(); i++) {
		for (int j = 0; j < res.colums(); j++) {
			res[i][j] *= rhs;
		}
	}
	return res;
}

template <typename T>
TableMatrix<T>::TableMatrix(int64_t row = 0, int64_t col = 0, T filler = T(0))
	: BaseMatrix<T>(row, col) {
	if (row < 0 || col < 0) {
		throw std::invalid_argument("the number of rows and colums must be positive");
	}
	data = new T * [row_];
	for (int64_t i = 0; i < row_; i++) {
		data[i] = new T[col_];
		std::fill(data[i], data[i] + col_, filler);
	}
}

template <typename T>
TableMatrix<T>::TableMatrix(int64_t row, T value)
	: BaseMatrix<T>(row, row) {
	data = new T * [row_];
	for (int64_t = 0; i < row_; i++) {
		std::fill(data[i], data[i] + col_, T(0));
		data[i][i] = value;
	}
}

template <typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& other)
	: BaseMatrix<T>(other.row_, other.col_) {
	data = new T * [row_];
	for (int64_t i = 0; i < row_; i++) {
		data[i] = new T[col_];
		std::copy(other.data[i], other.data[i] + col_, data[i]);
	}
}

template <typename T>
TableMatrix<T>::TableMatrix(std::initializer_list<std::initializer_list<T>> list)
	: BaseMatrix<T>(list.size(), list.begin()->size()) {
	data = new T * [row_];
	for (int64_t i = 0; i < row_; i++) {
		if ((list.begin() + i)->size() != col_) {
			throw std::invalid_argument("the number of elements in each row must be same");
		}
		data[i] = new T[col_];
		std::copy((list.begin() + i)->begin(), (list.begin() + i)->begin() + col_, data[i]);
	}
}

template <typename T>
TableMatrix<T>::~TableMatrix() {
	for (int64_t i = 0; i < row_; i++) {
		delete[] data[i];
	}
	delete[] data;
}

template <typename T>
void TableMatrix<T>::resize(int64_t r, int64_t c, const T filler = T(0)){
	if (r < 0 || c < 0) {
		throw std::invalid_argument("index must be positive number");
	}
	for (int64_t i = 0; i < row_; i++) {
		delete[] data[i];
	}
	delete[] data;
	row_ = r;
	col_ = c;
	data = new T * [row_];
	for (int64_t i = 0; i < row_; i++) {
		data[i] = new T[col_];
		std::fill(data[i], data[i] + col_, filler);
	}

}

template <typename T>
T* TableMatrix<T>::operator[](int64_t r) {
	return data[r];
}

template <typename T>
T& TableMatrix<T>::get(int64_t r, int64_t c) const {
	if (r > row_ || r < 0 || c > col_ || c < 0) {
		throw std::out_of_range("index out of range");
	}
	return data[r][c];
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator=(const TableMatrix<T>& rhs) {
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < col_; j++) {
			data[i][j] = rhs.data[i][j];
		}
	}
	return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator+=(const TableMatrix<T>& rhs) {
	if (row_ == rhs.row_ && col_ == rhs.col_) {
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				data[i][j] += rhs.data[i][j];
			}
		}
	}
	else {
		throw std::logic_error("you can not add up matrix of different size");
	}
	return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator-=(const TableMatrix<T>& rhs) {
	if (row_ == rhs.row_ && col_ == rhs.col_) {
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				data[i][j] -= rhs.data[i][j];
			}
		}
	}
	else {
		throw std::logic_error("you can not substruct matrix of different size");
	}
	return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator*=(const TableMatrix<T>& rhs) {
	if (col_ == rhs.row_) {
		TableMatrix temp(*this);
		resize(row_, rhs.col_);
		int r = 0;
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				for (int k = 0; k < rhs.row_; k++) {
					data[i][j] += temp.data[i][k] * rhs.data[k][j];
				}
			}
		}
	}
	else {
		throw std::logic_error("you can only multiply matrix sizes {m*n} and {n*k}");
	}
	return *this;
}

template <typename T>
bool TableMatrix<T>::operator==(const TableMatrix<T>& rhs) const {
	bool res = false;
	if (row_ == rhs.row_ && col_ == rhs.col_) {
		for (int i = 0; i < row_; i++) {
			res = std::equal(data[i], data[i] + col_, rhs.data[i], rhs.data[i] + col_);
		}
	}
	return res;
}

template <typename T>
bool TableMatrix<T>::operator !=(const TableMatrix<T>& rhs) const {
	return !(this == rhs);
}

template <typename T>
void TableMatrix<T>::diag(int64_t r, const T filler) {
	resize(r, r);
	for (int64_t i = 0; i < row_; i++) {
		data[i][i] = filler;
	}
}


