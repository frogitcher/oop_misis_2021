#pragma once

#include <stdexcept>
#include <initializer_list>

template<typename T>
class TableMatrix;
template<typename T>
class FlatMatrix;

template<typename T>
class BaseMatrix {
public:
	BaseMatrix(size_t r = 0, size_t c = 0, T value = T());
	BaseMatrix(std::initializer_list<std::initializer_list<T>>& list);
	virtual void Resize(size_t r, size_t c, T value = T()) = 0;
	virtual T& Get(size_t r, size_t c) const = 0;
	virtual T* operator[](size_t i) const = 0;
	~BaseMatrix();

	virtual TableMatrix<T>& operator+=(const TableMatrix<T>& oth) = 0;
	virtual FlatMatrix<T>& operator+=(const TableMatrix<T>& oth) = 0;
	virtual TableMatrix<T>& operator+=(const FlatMatrix<T>& oth) = 0;
	virtual FlatMatrix<T>& operator+=(const FlatMatrix<T>& oth) = 0;

	size_t Rows() const;
	size_t Columns() const;
protected:
	size_t rows = 0;
	size_t cols = 0;
};

template<typename T>
class TableMatrix : public BaseMatrix<T> {
public:
	TableMatrix(size_t r = 0, size_t c = 0, T value = T());
	TableMatrix(std::initializer_list<std::initializer_list<T>> list);
	void Resize(size_t r, size_t c, T value = T()) override;
	T& Get(size_t r, size_t c) const override;
	T* operator[](size_t i) const override;
	~TableMatrix();

	TableMatrix<T>& operator+=(const TableMatrix<T>& oth) override;
	FlatMatrix<T>& operator+=(const TableMatrix<T>& oth) override;
	TableMatrix<T>& operator+=(const FlatMatrix<T>& oth) override;
	FlatMatrix<T>& operator+=(const FlatMatrix<T>& oth) override;
private:
	T** Alloc(size_t r, size_t c) const;
	void DeleteData();
private:
	T** data = nullptr;
};

template<typename T>
class FlatMatrix : public BaseMatrix<T> {
public:
	FlatMatrix(size_t r = 0, size_t c = 0, T value = T());
	FlatMatrix(std::initializer_list<std::initializer_list<T>> list);
	void Resize(size_t r, size_t c, T value = T()) override;
	T& Get(size_t r, size_t c) const override;
	T* operator[](size_t i) const override;
	~FlatMatrix();

	TableMatrix<T>& operator+=(const TableMatrix<T>& oth) override;
	FlatMatrix<T>& operator+=(const TableMatrix<T>& oth) override;
	TableMatrix<T>& operator+=(const FlatMatrix<T>& oth) override;
	FlatMatrix<T>& operator+=(const FlatMatrix<T>& oth) override;
private:
	T* Alloc(size_t r, size_t c) const;
	void DeleteData();
private:
	T* data = nullptr;
};

template<typename T>
BaseMatrix<T>::BaseMatrix(size_t r, size_t c, T value) : rows(r), cols(c) {
	
}

template<typename T>
BaseMatrix<T>::BaseMatrix(std::initializer_list<std::initializer_list<T>>& list) {
	int r = list.size();
	int c = -1;
	for (const auto& elem : list) {
		if (elem.size() != c && c != -1) {
			throw std::invalid_argument("Cannot initialize matrix with rows of different length");
		}
		c = elem.size();
	}
}

template<typename T>
size_t BaseMatrix<T>::Rows() const {
	return rows;
}

template<typename T>
size_t BaseMatrix<T>::Columns() const {
	return cols;
}

template<typename T>
BaseMatrix<T>::~BaseMatrix() {

}

//TABLE MATRIX
template<typename T>
TableMatrix<T>::TableMatrix(size_t r, size_t c, T value) : BaseMatrix<T>(r, c, value) {
	data = Alloc(r, c);
}

template<typename T>
TableMatrix<T>::TableMatrix(std::initializer_list<std::initializer_list<T>> list) : BaseMatrix<T>(list) {
	int r = list.size();
	int c = r == 0 ? 0 : list.begin()->size();
	data = Alloc(r, c);
}

template<typename T>
TableMatrix<T>::~TableMatrix() {
	DeleteData();
}

template<typename T>
void TableMatrix<T>::Resize(size_t r, size_t c, T value) {
	T** new_data = Alloc(r, c);
}

template<typename T>
T& TableMatrix<T>::Get(size_t r, size_t c) const {
	return data[r][c];
}

template<typename T>
T* TableMatrix<T>::operator[](size_t i) const {
	return data[i];
}

template<typename T>
T** TableMatrix<T>::Alloc(size_t r, size_t c) const {
	T** new_data = new T* [r];
	for (int i = 0; i < r; ++i) {
		new_data[i] = new T[c];
	}
	return new_data;
}

template<typename T>
void TableMatrix<T>::DeleteData() {
	for (int i = 0; i < BaseMatrix<T>::rows; ++i) {
		delete[] data[i];
	}
	delete[] data;
}

template<typename T>
TableMatrix<T>& TableMatrix<T>::operator+=(const TableMatrix<T>& oth) {
	if (BaseMatrix<T>::rows != oth.BaseMatrix<T>::rows || BaseMatrix<T>::cols != oth.BaseMatrix<T>::cols) {
		throw std::invalid_argument("Cannot perform += operation with given matrix");
	}
	for (int i = 0; i < BaseMatrix<T>::rows; ++i) {
		for (int j = 0; j < BaseMatrix<T>::cols; ++j) {
			data[i][j] += oth.data[i][j];
		}
	}
	return *this;
}

//FLAT MATRIX
template<typename T>
FlatMatrix<T>::FlatMatrix(size_t r, size_t c, T value) : BaseMatrix<T>(r, c, value) {
	data = Alloc(r, c);
}

template<typename T>
FlatMatrix<T>::~FlatMatrix() {
	DeleteData();
}

template<typename T>
FlatMatrix<T>::FlatMatrix(std::initializer_list<std::initializer_list<T>> list) {
	int r = list.size();
	int c = r == 0 ? 0 : list.begin()->size();
	data = Alloc(r, c);
}

template<typename T>
void FlatMatrix<T>::Resize(size_t r, size_t c, T value) {
	T* new_data = Alloc(r, c);
	DeleteData();
	data = new_data;
}

template<typename T>
T& FlatMatrix<T>::Get(size_t r, size_t c) const {
	return data[r * BaseMatrix<T>::rows + c];
}

template<typename T>
T* FlatMatrix<T>::operator[](size_t i) const {
	return data[i * BaseMatrix<T>::rows][i];
}

template<typename T>
T* FlatMatrix<T>::Alloc(size_t r, size_t c) const {
	return new T[r * c];
}

template<typename T>
void FlatMatrix<T>::DeleteData() {
	delete data;
}
