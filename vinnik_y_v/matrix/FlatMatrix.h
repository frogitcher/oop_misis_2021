#pragma once

#include "Matrix.h"

template<typename T>
FlatMatrix<T>::FlatMatrix(size_t r, size_t c, T value) : BaseMatrix<T>(r, c, value) {
	data = Alloc(r, c, value);
}

template<typename T>
FlatMatrix<T>::~FlatMatrix() {
	DeleteData();
}

template<typename T>
FlatMatrix<T>::FlatMatrix(std::initializer_list<std::initializer_list<T>> list) : BaseMatrix<T>(list) {
	int r = list.size();
	int c = r == 0 ? 0 : list.begin()->size();
	data = Alloc(r, c);
	int i_cnt = 0, j_cnt = 0;
	for (const auto& i : list) {
		for (const auto& j : i) {
			Get(i_cnt, j_cnt) = j;
			++j_cnt;
		}
		++i_cnt;
		j_cnt = 0;
	}
}

template<typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T>& oth) noexcept
{
	BaseMatrix<T>::rows = oth.BaseMatrix<T>::rows;
	BaseMatrix<T>::cols = oth.BaseMatrix<T>::cols;
	data = Alloc(BaseMatrix<T>::rows, BaseMatrix<T>::cols);
	CopyData(oth.data);
}

template<typename T>
void FlatMatrix<T>::Resize(size_t r, size_t c, T value) {
	T* new_data = Alloc(r, c);
	DeleteData();
	data = new_data;
	BaseMatrix<T>::rows = r;
	BaseMatrix<T>::cols = c;
}

template<typename T>
T& FlatMatrix<T>::Get(size_t r, size_t c) const {
	if (r >= BaseMatrix<T>::rows || c >= BaseMatrix<T>::cols) {
		throw std::out_of_range("Matrix index is out of range");
	}
	return data[r * BaseMatrix<T>::rows + c];
}

template<typename T>
T* FlatMatrix<T>::operator[](size_t i) const {
	return (data + i * BaseMatrix<T>::rows);
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator+=(const TableMatrix<T>& oth) {
	if (BaseMatrix<T>::rows != oth.BaseMatrix<T>::rows || BaseMatrix<T>::cols != oth.BaseMatrix<T>::cols) {
		throw std::invalid_argument("Cannot perform += operation with given matrix");
	}
	for (int i = 0; i < (int)BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < (int)BaseMatrix<T>::cols; ++j) {
			Get(i, j) += oth.Get(i, j);
		}
	}
	return *this;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator+=(const FlatMatrix<T>& oth) {
	if (BaseMatrix<T>::rows != oth.BaseMatrix<T>::rows || BaseMatrix<T>::cols != oth.BaseMatrix<T>::cols) {
		throw std::invalid_argument("Cannot perform += operation with given matrix");
	}
	for (int i = 0; i < (int)BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < (int)BaseMatrix<T>::cols; ++j) {
			Get(i, j) += oth.Get(i, j);
		}
	}
	return *this;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const TableMatrix<T>& oth) const {
	if (BaseMatrix<T>::rows != oth.BaseMatrix<T>::rows || BaseMatrix<T>::cols != oth.BaseMatrix<T>::cols) {
		throw std::invalid_argument("Cannot perform + operation with given matrix");
	}
	return FlatMatrix<T>(*this) += oth;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T>& oth) const {
	if (BaseMatrix<T>::rows != oth.BaseMatrix<T>::rows || BaseMatrix<T>::cols != oth.BaseMatrix<T>::cols) {
		throw std::invalid_argument("Cannot perform + operation with given matrix");
	}
	return FlatMatrix<T>(*this) += oth;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator-=(const TableMatrix<T>& oth)
{
	if (BaseMatrix<T>::rows != oth.BaseMatrix<T>::rows || BaseMatrix<T>::cols != oth.BaseMatrix<T>::cols) {
		throw std::invalid_argument("Cannot perform += operation with given matrix");
	}
	for (int i = 0; i < (int)BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < (int)BaseMatrix<T>::cols; ++j) {
			Get(i, j) -= oth.Get(i, j);
		}
	}
	return *this;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator-=(const FlatMatrix<T>& oth)
{
	if (BaseMatrix<T>::rows != oth.BaseMatrix<T>::rows || BaseMatrix<T>::cols != oth.BaseMatrix<T>::cols) {
		throw std::invalid_argument("Cannot perform += operation with given matrix");
	}
	for (int i = 0; i < (int)BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < (int)BaseMatrix<T>::cols; ++j) {
			Get(i, j) -= oth.Get(i, j);
		}
	}
	return *this;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const TableMatrix<T>& oth) const
{
	return FlatMatrix<T>(*this) -= oth;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T>& oth) const
{
	return FlatMatrix<T>(*this) -= oth;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const TableMatrix<T>& oth) const
{
	return FlatMatrix<T>(*this) *= oth;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& oth) const
{
	return FlatMatrix<T>(*this) *= oth;
}

template<typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const double num) const noexcept
{
	return FlatMatrix<T>(*this) *= num;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator/=(const double num)
{
	if (num == 0.f) {
		throw std::exception("Cannot divide matrix by 0");
	}
	for (int i = 0; i < BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < BaseMatrix<T>::cols; ++j) {
			Get(i, j) /= num;
		}
	}
	return *this;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator/(const double num) const
{
	return FlatMatrix<T>(*this) /= num;
}

template<typename T>
bool FlatMatrix<T>::operator==(const TableMatrix<T>& oth) const noexcept
{
	if (BaseMatrix<T>::rows != oth.BaseMatrix<T>::rows || BaseMatrix<T>::cols != oth.BaseMatrix<T>::cols) {
		return false;
	}
	for (int i = 0; i < BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < BaseMatrix<T>::cols; ++j) {
			if (Get(i, j) != oth.Get(i, j)) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T>& oth) const noexcept
{
	if (BaseMatrix<T>::rows != oth.BaseMatrix<T>::rows || BaseMatrix<T>::cols != oth.BaseMatrix<T>::cols) {
		return false;
	}
	for (int i = 0; i < BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < BaseMatrix<T>::cols; ++j) {
			if (Get(i, j) != oth.Get(i, j)) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
void FlatMatrix<T>::Transponse() noexcept
{
	FlatMatrix<T> old_matrix(*this);
	Resize(BaseMatrix<T>::cols, BaseMatrix<T>::rows);
	for (int i = 0; i < (int)BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < (int)BaseMatrix<T>::cols; ++j) {
			Get(j, i) = old_matrix.Get(i, j);
		}
	}
}

template<typename T>
double FlatMatrix<T>::Determinant() const
{
	if (!BaseMatrix<T>::isSquare()) {
		throw std::domain_error("Cannot find determinant for non-square matrix");
	}
	//Using Gauss method
	double tmp = 0.f;
	FlatMatrix<T> target_matrix(*this);
	//Finding target matrix
	for (int k = 0; k < (int)BaseMatrix<T>::rows; ++k) {
		for (int i = k + 1; i < (int)BaseMatrix<T>::rows; ++i) {
			tmp = -(target_matrix[i][k]) / target_matrix[k][k];
			for (int j = 0; j < (int)BaseMatrix<T>::rows; ++j) {
				target_matrix[i][j] += target_matrix[k][j] * tmp;
			}
		}
	}
	//Calculating determinant
	double det = 0.f;
	for (int i = 0; i < (int)BaseMatrix<T>::rows; i++) {
		det *= target_matrix[i][i];
	}
	return det;
}

template<typename T>
void FlatMatrix<T>::Inverse()
{
	if (!BaseMatrix<T>::isSquare()) {
		throw std::domain_error("Cannot inverse non-square matrix");
	}
	FlatMatrix<T> identity_matrix(*this);
	//Find Identity Matrix
	for (int i = 0; i < (int)BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < (int)BaseMatrix<T>::rows; ++j) {
			if (i == j) {
				identity_matrix[i][j + (int)BaseMatrix<T>::rows] = 1;
			}
			else {
				identity_matrix[i][j + (int)BaseMatrix<T>::rows] = 0;
			}
		}
	}
	//Gauss elimination method
	for (int i = 1; i <= (int)BaseMatrix<T>::rows; i++) {
		if (identity_matrix[i][i] == 0.0) {
			throw std::invalid_argument("Failed to inverse given matrix");
		}
		for (int j = 0; j < (int)BaseMatrix<T>::rows; ++j) {
			if (i != j) {
				double ratio = identity_matrix[j][i] / identity_matrix[i][i];
				for (int k = 0; k < 2 * (int)BaseMatrix<T>::rows; ++k) {
					identity_matrix[j][k] = identity_matrix[j][k] - ratio * identity_matrix[i][k];
				}
			}
		}
	}
	//Normalize rows
	for (int i = 0; i <= (int)BaseMatrix<T>::rows; ++i) {
		for (int j = (int)BaseMatrix<T>::rows + 1; j < 2 * (int)BaseMatrix<T>::rows; ++j)
		{
			identity_matrix[i][j] = identity_matrix[i][j] / identity_matrix[i][i];
		}
	}
	CopyData(identity_matrix.data);
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const TableMatrix<T>& oth) {
	if (BaseMatrix<T>::cols != oth.Rows()) {
		throw std::invalid_argument("Cannot perform multiplication with given matrix");
	}

	FlatMatrix<T> result(BaseMatrix<T>::Rows(), oth.Columns(), 0);
	for (int i = 0; i < BaseMatrix<T>::Rows(); ++i) {
		for (int j = 0; j < oth.Columns(); ++j) {
			for (int k = 0; k < oth.Rows(); ++k) {
				result[i][j] += Get(i, k) * oth.Get(k, j);
			}
		}
	}

	CopyFromOth(result);
	return *this;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const FlatMatrix<T>& oth) {
	if (BaseMatrix<T>::cols != oth.Rows()) {
		throw std::invalid_argument("Cannot perform multiplication with given matrix");
	}

	FlatMatrix<T> result(BaseMatrix<T>::Rows(), oth.Columns(), 0);
	for (int i = 0; i < BaseMatrix<T>::Rows(); ++i) {
		for (int j = 0; j < oth.Columns(); ++j) {
			for (int k = 0; k < oth.Rows(); ++k) {
				result[i][j] += Get(i, k) * oth.Get(k, j);
			}
		}
	}

	CopyFromOth(result);
	return *this;
}

template<typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const double num) noexcept
{
	for (int i = 0; i < BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < BaseMatrix<T>::cols; ++j) {
			Get(i, j) *= num;
		}
	}
	return *this;
}

template<typename T>
T* FlatMatrix<T>::Alloc(size_t r, size_t c, T value) {
	T* new_data = new T[r * c];
	std::fill(new_data, new_data + r * c, value);
	return new_data;
}

template<typename T>
void FlatMatrix<T>::CopyFromOth(const FlatMatrix<T>& oth)
{
	if (oth.Columns() != BaseMatrix<T>::cols || oth.Rows() != BaseMatrix<T>::rows) {
		Resize(oth.Rows(), oth.Columns());
	}

	for (int i = 0; i < BaseMatrix<T>::cols; ++i) {
		for (int j = 0; j < BaseMatrix<T>::rows; ++j) {
			Get(i, j) = oth.Get(i, j);
		}
	}
}

template<typename T>
void FlatMatrix<T>::CopyFromOth(const TableMatrix<T>& oth)
{
	if (oth.Columns() != BaseMatrix<T>::cols || oth.Rows() != BaseMatrix<T>::rows) {
		Resize(oth.Rows(), oth.Columns());
	}

	for (int i = 0; i < BaseMatrix<T>::cols; ++i) {
		for (int j = 0; j < BaseMatrix<T>::rows; ++j) {
			Get(i, j) = oth.Get(i, j);
		}
	}
}

template<typename T>
void FlatMatrix<T>::CopyData(T* oth_data) noexcept
{
	std::copy(oth_data, oth_data + BaseMatrix<T>::rows * BaseMatrix<T>::cols, data);
}

template<typename T>
void FlatMatrix<T>::DeleteData() {
	delete data;
}

template<typename T>
inline T* FlatMatrix<T>::Data() {
	return data;
}