#pragma once
#include "matrix.h"

template <typename T>

TableMatrix<T>::TableMatrix(){

}

template<typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& oth) : BaseMatrix<T>(oth.Get_rows(), oth.Get_cols())
{
	data = alloc(oth.BaseMatrix<T>::Get_rows(), oth.BaseMatrix<T>::Get_cols(), 0);
	Copy(oth);
}

template<typename T>
TableMatrix<T>::TableMatrix(std::initializer_list<std::initializer_list<T>> list) : BaseMatrix<T>(list) {
	int r = list.size();
	int c = r == 0 ? 0 : list.begin()->size();
	data = alloc(r, c);
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

template <typename T>
TableMatrix<T>::~TableMatrix()
{
	Delete();
}

template <typename T>
TableMatrix<T>::TableMatrix(size_t rows, size_t cols, T value) : BaseMatrix<T>(rows, cols)
{
	data = alloc(rows, cols, value);
}

template <typename T>
T& TableMatrix<T>::Get(size_t i, size_t j) const
{
	if (i >= BaseMatrix<T>::rows || j >= BaseMatrix<T>::cols) {
		throw std::out_of_range("Out of range!");
	}
	return data[i][j];
}

template <typename T>
void TableMatrix<T>::Resize(size_t new_rows, size_t new_cols, T value)
{
	T** new_data = alloc(new_rows, new_cols, value);
	Delete();
	data = new_data;
	BaseMatrix<T>::rows = new_rows;
	BaseMatrix<T>::cols = new_cols;
}

template <typename T>
T* TableMatrix<T>::operator[](size_t i) const
{
	return data[i];
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T>& oth) const
{
	return TableMatrix<T>(*this)  += oth;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator+=(const TableMatrix<T>& oth)
{
	if (BaseMatrix<T>::Get_rows() != oth.BaseMatrix<T>::Get_rows() || BaseMatrix<T>::Get_cols() != oth.BaseMatrix<T>::Get_cols()) {
		throw std::invalid_argument("Invalid argument!");
	}

	for (int i = 0; i < BaseMatrix<T>::rows; i++) {
		for (int j = 0; j < BaseMatrix<T>::cols; j++) {
			Get(i, j) += oth.Get(i, j);
		}
	}
	return *this;
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T>& oth) const
{
	return TableMatrix<T>(*this) -= oth;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator-=(const TableMatrix<T>& oth)
{
	if (BaseMatrix<T>::Get_rows() != oth.BaseMatrix<T>::Get_rows() || BaseMatrix<T>::Get_cols() != oth.BaseMatrix<T>::Get_cols()) {
		throw std::invalid_argument("Invalid argument!");
	}

	for (int i = 0; i < BaseMatrix<T>::rows; i++) {
		for (int j = 0; j < BaseMatrix<T>::cols; j++) {
			Get(i, j) -= oth.Get(i, j);
		}
	}
	return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator*=(const TableMatrix<T>& oth)
{
	if (BaseMatrix<T>::cols != oth.BaseMatrix<T>::Get_rows()) {
		throw std::invalid_argument("Invalid argument!");
	}

	TableMatrix<T> result(BaseMatrix<T>::Get_rows(), oth.BaseMatrix<T>::Get_cols(), 0);
	for (int i = 0; i < BaseMatrix<T>::Get_rows(); i++) {
		for (int j = 0; j < oth.BaseMatrix<T>::Get_cols(); j++) {
			for (int k = 0; k < oth.BaseMatrix<T>::Get_rows(); k++) {
				result[i][j] += Get(i, k) * oth.Get(k, j);
			}
		}
	}

	Copy(result);
	return *this;
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T>& oth) const
{
	return TableMatrix<T>(*this) *= oth;
}

template <typename T>
bool TableMatrix<T>::operator==(const TableMatrix<T>& oth) const
{
	if (BaseMatrix<T>::Get_rows() != oth.BaseMatrix<T>::Get_rows() || BaseMatrix<T>::Get_cols() != oth.BaseMatrix<T>::Get_cols()) {
		return false;
	}
	for (int i = 0; i < BaseMatrix<T>::Get_rows(); i++) {
		for (int j = 0; j < BaseMatrix<T>::Get_cols(); j++) {
			if (Get(i, j) != oth.Get(i, j)) {
				return false;
			}
		}
	}
	return true;
}

template <typename T>
void TableMatrix<T>::operator=(const TableMatrix<T>& oth)
{
	Delete();
	Copy(oth);
}

template <typename T>
T** TableMatrix<T>::alloc(size_t rows, size_t cols, T value)
{
	T** new_data = new T * [rows];
	for (int i = 0; i < (int)rows; i++) {
		new_data[i] = new T[cols];
		std::fill(new_data[i], new_data[i] + cols, value);
	}
	return new_data;
}
