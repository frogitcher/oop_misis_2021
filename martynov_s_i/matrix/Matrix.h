#pragma once
#include <initializer_list>
template <typename T>
class BaseMatrix {
public:
	BaseMatrix(size_t rows, size_t cols);
	BaseMatrix(const BaseMatrix<T>& bm);
	BaseMatrix(std::initializer_list<std::initializer_list<T>> list);
	size_t Cols();
	size_t Rows();
	virtual void Resize(size_t rows, size_t cols) = 0;
	virtual T& Get(size_t row, size_t col) const = 0;
	virtual T* operator[](size_t row) const = 0;
	~BaseMatrix() = default;
protected:
	size_t num_rows = 0;
	size_t num_cols = 0;
};


template <typename T>
BaseMatrix<T>::BaseMatrix(size_t rows, size_t cols) {
	num_rows = rows;
	num_cols = cols;
}
template <typename T>
BaseMatrix<T>::BaseMatrix(const BaseMatrix<T>& bm) {
	num_rows = bm.num_rows;
	num_cols = bm.num_cols;
}
template <typename T>
BaseMatrix<T>::BaseMatrix(std::initializer_list<std::initializer_list<T>> list) {
	num_rows = list.size();
	num_cols = (*(list.begin())).size();
}
template <typename T>
size_t BaseMatrix<T>::Cols() {
	return num_cols;
}
template <typename T>
size_t BaseMatrix<T>::Rows() {
	return num_rows;
}


template <typename T>
class FlatMatrix : public BaseMatrix<T> {
public:
	FlatMatrix(size_t rows = 0, size_t cols = 0, T value = 0);
	FlatMatrix(const FlatMatrix<T>& fm);
	FlatMatrix(std::initializer_list<std::initializer_list<T>> list);
	~FlatMatrix();
	void Resize(size_t rows, size_t cols) override;
	void Print();
	T* operator[](size_t row) const override;
	T& Get(size_t row, size_t col) const override;
	FlatMatrix<T> operator+(const FlatMatrix<T>& fm) const;
	FlatMatrix<T> operator-(const FlatMatrix<T>& fm) const;
	FlatMatrix<T> operator+(const T& value) const;
	FlatMatrix<T> operator-(const T& value) const;
	FlatMatrix<T> operator*(const FlatMatrix<T>& fm) const;
	FlatMatrix<T> operator*(const T& value) const;
	void operator=(const FlatMatrix<T>& fm);
	bool operator==(const FlatMatrix<T>& fm) const;
	bool operator!=(const FlatMatrix<T>& fm) const;
private:
	T* data = nullptr;
};


template <typename T>
FlatMatrix<T>::FlatMatrix(size_t rows, size_t cols, T value) : BaseMatrix<T>(rows, cols) {
	data = new T[rows * cols];
	std::fill(data, data + rows * cols, value);
}
template <typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T>& fm) : BaseMatrix<T>(fm) {
	data = new T[fm.num_rows * fm.num_cols];
	std::copy(fm.data, fm.data + fm.num_rows * fm.num_cols, data);
}
template <typename T>
FlatMatrix<T>::FlatMatrix(std::initializer_list<std::initializer_list<T>> list) : BaseMatrix<T>(list) {
	data = new T[(*this).num_rows * (*this).num_cols];
	int k = 0;
	for (auto now : list) {
		std::copy(now.begin(), now.end(), data + k * now.size());
		++k;
	}
}
template <typename T>
FlatMatrix<T>::~FlatMatrix() {
	delete[] data;
}
template <typename T>
void FlatMatrix<T>::Resize(size_t rows, size_t cols) {
	T* new_data = new T[rows * cols];
	std::fill(new_data, new_data + rows * cols, 0);
	for (size_t i = 0; i < std::min(rows, (*this).num_rows); ++i) {
		for (size_t j = 0; j < std::min(cols, (*this).num_cols); ++j) {
			new_data[i * cols + j] = data[i * (*this).num_cols + j];
		}
	}
	delete[] data;
	data = new_data;
	(*this).num_rows = rows;
	(*this).num_cols = cols;
}
template <typename T>
void FlatMatrix<T>::Print() {
	for (size_t i = 0; i < BaseMatrix<T>::num_rows; ++i) {
		for (size_t j = 0; j < BaseMatrix<T>::num_cols; ++j) {
			std::cout << data[i * BaseMatrix<T>::num_cols + j] << " ";
		}
		std::cout << std::endl;
	}
}
template <typename T>
T* FlatMatrix<T>::operator[](size_t row) const {
	return data + (*this).num_cols * row;
}
template <typename T>
T& FlatMatrix<T>::Get(size_t row, size_t col) const {
	return (*this)[row][col];
}
template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T>& fm) const {
	if (fm.num_rows != (*this).num_rows || (*this).num_cols != fm.num_cols) {
		throw "different matrices";
	}
	FlatMatrix<T> temp(fm.num_rows, fm.num_cols);
	for (size_t i = 0; i < fm.num_rows * fm.num_cols; ++i) {
		temp.data[i] = data[i] + fm.data[i];
	}
	return temp;
}
template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T>& fm) const {
	if (fm.num_rows != (*this).num_rows || (*this).num_cols != fm.num_cols) {
		throw "different matrices";
	}
	FlatMatrix<T> temp(fm.num_rows, fm.num_cols);
	for (size_t i = 0; i < fm.num_rows * fm.num_cols; ++i) {
		temp.data[i] = data[i] - fm.data[i];
	}
	return temp;
}
template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const T& value) const {
	if ((*this).num_rows != (*this).num_cols) {
		throw "not square";
	}
	FlatMatrix<T> temp(*this);
	for (size_t i = 0; i < (*this).num_rows * (*this).num_cols; i += (*this).num_cols + 1) {
		temp.data[i] += value;
	}
	return temp;
}
template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const T& value) const {
	if ((*this).num_rows != (*this).num_cols) {
		throw "not square";
	}
	FlatMatrix<T> temp(*this);
	for (size_t i = 0; i < (*this).num_rows * (*this).num_cols; i += (*this).num_cols + 1) {
		temp.data[i] -= value;
	}
	return temp;
}
template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& fm) const {
	if ((*this).num_cols != fm.num_rows) {
		throw "impossible";
	}
	FlatMatrix<T> temp((*this).num_rows, fm.num_cols);
	for (size_t i = 0; i < (*this).num_rows; i++) {
		for (size_t j = 0; j < fm.num_cols; j++) {
			for (size_t k = 0; k < (*this).num_cols; k++) {
				temp[i][j] += (*this)[i][k] * fm[k][j];
			}
		}
	}
	return temp;
}
template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const T& value) const {
	FlatMatrix<T> temp(*this);
	for (size_t i = 0; i < (*this).num_rows * (*this).num_cols; ++i) {
		temp.data[i] *= value;
	}
	return temp;
}
template <typename T>
void FlatMatrix<T>::operator=(const FlatMatrix<T>& fm) {
	T* new_data = new T[fm.num_rows * fm.num_cols];
	std::copy(fm.data, fm.data + fm.num_rows * fm.num_cols, new_data);
	delete[] data;
	data = new_data;
	(*this).num_rows = fm.num_rows;
	(*this).num_cols = fm.num_cols;
}
template <typename T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T>& fm) const {
	if (fm.num_rows == (*this).num_rows && (*this).num_cols == fm.num_cols && std::equal(data, data + (*this).num_rows * (*this).num_cols, fm.data)) {
		return true;
	}
	return false;
}
template <typename T>
bool FlatMatrix<T>::operator!=(const FlatMatrix<T>& fm) const {
	return !(*this == fm);
}
template <typename T>
FlatMatrix<T> operator*(const T& value, const FlatMatrix<T>& fm) {
	return fm * value;
}
template <typename T>
FlatMatrix<T> operator+(const T& value, const FlatMatrix<T>& fm) {
	return fm + value;
}
template <typename T>
FlatMatrix<T> operator-(const T& value, const FlatMatrix<T>& fm) {
	return fm - value;
}


template <typename T>
class TableMatrix : public BaseMatrix<T> {
public:
	TableMatrix(size_t rows = 0, size_t cols = 0, T value = 0);
	TableMatrix(const TableMatrix<T>& tm);
	TableMatrix(std::initializer_list<std::initializer_list<T>> list);
	~TableMatrix();
	T* operator[](size_t row) const override;
	T& Get(size_t row, size_t col) const override;
	void Resize(size_t rows, size_t cols) override;
	TableMatrix<T> operator+(const TableMatrix<T>& tm) const;
	TableMatrix<T> operator+(const T& value) const;
	TableMatrix<T> operator-(const T& value) const;
	TableMatrix<T> operator-(const TableMatrix<T>& tm) const;
	TableMatrix<T> operator*(const T& value) const;
	TableMatrix<T> operator*(const TableMatrix<T>& tm) const;
	bool operator==(const TableMatrix<T>& tm) const;
	bool operator!=(const TableMatrix<T>& tm) const;
	void operator=(const TableMatrix<T>& tm);
	void Print();
private:
	T** data = nullptr;
};


template <typename T>
TableMatrix<T>::TableMatrix(size_t rows, size_t cols, T value) : BaseMatrix<T>(rows, cols) {
	data = new T * [rows];
	for (size_t i = 0; i < rows; ++i) {
		data[i] = new T[cols];
		std::fill(data[i], data[i] + cols, value);
	}
}
template <typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& tm) : BaseMatrix<T>(tm) {
	data = new T * [tm.num_rows];
	for (size_t i = 0; i < tm.num_rows; ++i) {
		data[i] = new T[tm.num_cols];
		std::copy(tm.data[i], tm.data[i] + tm.num_cols, data[i]);
	}
}
template <typename T>
TableMatrix<T>::TableMatrix(std::initializer_list<std::initializer_list<T>> list) : BaseMatrix<T>(list) {
	data = new T * [(*this).num_rows];
	int k = 0;
	for (auto now : list) {
		data[k] = new T[(*this).num_cols];
		std::copy(now.begin(), now.end(), data[k]);
		k++;
	}
}
template <typename T>
TableMatrix<T>::~TableMatrix() {
	for (size_t i = 0; i < (*this).num_rows; ++i) {
		delete[] data[i];
	}
	delete[] data;
}
template <typename T>
T* TableMatrix<T>::operator[](size_t ind) const {
	return data[ind];
}
template <typename T>
T& TableMatrix<T>::Get(size_t row, size_t col) const {
	return (*this)[row][col];
}
template <typename T>
void TableMatrix<T>::Resize(size_t rows, size_t cols) {
	T** new_data = new T * [rows];
	for (size_t i = 0; i < rows; ++i) {
		new_data[i] = new T[cols];
		std::fill(new_data[i], new_data[i] + cols, 0);
	}
	for (size_t i = 0; i < std::min(rows, (*this).num_rows); ++i) {
		for (size_t j = 0; j < std::min(cols, (*this).num_cols); ++j) {
			new_data[i][j] = data[i][j];
		}
	}
	delete[] data;
	data = new_data;
	(*this).num_rows = rows;
	(*this).num_cols = cols;
}
template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T>& tm) const {
	if (tm.num_rows != (*this).num_rows || (*this).num_cols != tm.num_cols) {
		throw "different matrices";
	}
	TableMatrix<T> temp(tm.num_rows, tm.num_cols);
	for (size_t i = 0; i < (*this).num_rows; ++i) {
		for (size_t j = 0; j < (*this).num_cols; ++j) {
			temp[i][j] += (*this)[i][j] + tm[i][j];
		}
	}
	return temp;
}
template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const T& value) const {
	if ((*this).num_rows != (*this).num_cols) {
		throw "not square";
	}
	TableMatrix<T> temp(*this);
	for (size_t i = 0; i < (*this).num_rows; ++i) {
		for (size_t j = i; j < (*this).num_cols; ++j) {
			temp[i][j] += value;
			break;
		}
	}
	return temp;
}
template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const T& value) const {
	if ((*this).num_rows != (*this).num_cols) {
		throw "not square";
	}
	TableMatrix<T> temp(*this);
	for (size_t i = 0; i < (*this).num_rows; ++i) {
		for (size_t j = i; j < (*this).num_cols; ++j) {
			temp[i][j] -= value;
			break;
		}
	}
	return temp;
}
template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T>& tm) const {
	if (tm.num_rows != (*this).num_rows || (*this).num_cols != tm.num_cols) {
		throw "different matrices";
	}
	TableMatrix<T> temp(tm.num_rows, tm.num_cols);
	for (size_t i = 0; i < (*this).num_rows; ++i) {
		for (size_t j = 0; j < (*this).num_cols; ++j) {
			temp[i][j] += (*this)[i][j] - tm[i][j];
		}
	}
	return temp;
}
template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const T& value) const {
	TableMatrix<T> temp((*this));
	for (size_t i = 0; i < (*this).num_rows; ++i) {
		for (size_t j = 0; j < (*this).num_cols; ++j) {
			temp[i][j] *= value;
		}
	}
	return temp;
}
template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T>& tm) const {
	if ((*this).num_cols != tm.num_rows) {
		throw "impossible";
	}
	TableMatrix<T> temp((*this).num_rows, tm.num_cols);
	for (size_t i = 0; i < (*this).num_rows; i++) {
		for (size_t j = 0; j < tm.num_cols; j++) {
			for (size_t k = 0; k < (*this).num_cols; k++) {
				temp[i][j] += data[i][k] * tm[k][j];
			}
		}
	}
	return temp;
}
template <typename T>
bool TableMatrix<T>::operator==(const TableMatrix<T>& tm) const {
	if (tm.num_rows != (*this).num_rows || (*this).num_cols != tm.num_cols) {
		return false;
	}
	for (size_t i = 0; i < tm.num_rows; ++i) {
		if (!(std::equal(tm.data[i], tm.data[i] + tm.num_cols, data[i]))) {
			return false;
		}
	}
	return true;
}
template <typename T>
bool TableMatrix<T>::operator!=(const TableMatrix<T>& tm) const {
	return !(*this == tm);
}
template <typename T>
void TableMatrix<T>::operator=(const TableMatrix<T>& tm) {
	T** new_data = new T * [tm.num_rows];
	for (size_t i = 0; i < tm.num_rows; ++i) {
		new_data[i] = new T[tm.num_cols];
		std::copy(tm.data[i], tm.data[i] + tm.num_cols, new_data[i]);
	}
	delete[] data;
	data = new_data;
	(*this).num_rows = tm.num_rows;
	(*this).num_cols = tm.num_cols;
}
template <typename T>
void TableMatrix<T>::Print() {
	for (size_t i = 0; i < (*this).num_rows; ++i) {
		for (size_t j = 0; j < (*this).num_cols; ++j) {
			std::cout << (*this)[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
template <typename T>
TableMatrix<T> operator*(const T& value, const TableMatrix<T>& tm) {
	return tm * value;
}
template <typename T>
TableMatrix<T> operator+(const T& value, const TableMatrix<T>& tm) {
	return tm + value;
}
template <typename T>
TableMatrix<T> operator-(const T& value, const TableMatrix<T>& tm) {
	return tm - value;
}
