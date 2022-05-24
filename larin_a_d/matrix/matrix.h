#pragma once
#include <stdexcept>

template <typename T>
class BaseMatrix {
public:
	BaseMatrix();
	~BaseMatrix();
	BaseMatrix(size_t rows, size_t cols);
	BaseMatrix(std::initializer_list<std::initializer_list<T>>& list);
	virtual T& Get(size_t i, size_t j) const = 0;
	virtual T* operator[](size_t i) const = 0;
	virtual void Resize(size_t new_rows, size_t new_cols, T value = T()) = 0;
	size_t Get_rows() const {
		return rows;
	}
	size_t Get_cols() const {
		return cols;
	}
	bool IsSquare() const{
		return rows == cols;
	}
protected:
	size_t rows = 0;
	size_t cols = 0;
};

template <typename T>
class TableMatrix: public BaseMatrix<T> {
public:
	TableMatrix();
	TableMatrix(const TableMatrix<T>& oth);
	~TableMatrix();
	TableMatrix(std::initializer_list<std::initializer_list<T>> list);
	TableMatrix(size_t rows, size_t cols, T value = T());

	T& Get(size_t i, size_t j) const override;
	void Resize(size_t new_rows, size_t new_cols, T value = T()) override;

	T* operator[](size_t i) const override;
	TableMatrix<T> operator+(const TableMatrix<T>& oth) const;
	TableMatrix<T>& operator+=(const TableMatrix<T>& oth);
	TableMatrix<T> operator-(const TableMatrix<T>& oth) const;
	TableMatrix<T>& operator-=(const TableMatrix<T>& oth);
	TableMatrix<T> operator*(const TableMatrix<T>& oth) const;
	TableMatrix<T>& operator*=(const TableMatrix<T>& oth);
	bool operator==(const TableMatrix<T>& oth) const;
	void operator=(const TableMatrix<T>& oth);
private:
	T** alloc(size_t rows, size_t cols, T value = T());
	T** data = nullptr;
	void Delete() {
		for (int i = 0; i < (int)BaseMatrix<T>::rows; i++) {
			delete[] data[i];
		}
		delete[] data;
		BaseMatrix<T>::rows = 0;
		BaseMatrix<T>::cols = 0;
	}
	void Copy(const TableMatrix<T>& oth) {
		if (oth.BaseMatrix<T>::Get_cols() != BaseMatrix<T>::cols || oth.BaseMatrix<T>::Get_cols() != BaseMatrix<T>::rows) {
			Resize(oth.BaseMatrix<T>::Get_rows(), oth.BaseMatrix<T>::Get_cols());
		}

		for (int i = 0; i < BaseMatrix<T>::cols; i++) {
			for (int j = 0; j < BaseMatrix<T>::rows; j++) {
				Get(i, j) = oth.Get(i, j);
			}
		}
	}
};

template <typename T>
class FlatMatrix : public BaseMatrix<T> {
public:
	FlatMatrix();
	FlatMatrix(const FlatMatrix<T>& oth);
	~FlatMatrix();
	FlatMatrix(std::initializer_list<std::initializer_list<T>> list);
	FlatMatrix(size_t rows, size_t cols, T value = T());

	T& Get(size_t i, size_t j) const override;
	T* operator[](size_t i) const override;
	void Resize(size_t new_rows, size_t new_cols, T value = T()) override;

	FlatMatrix<T> operator+(const FlatMatrix<T>& oth) const;
	FlatMatrix<T>& operator+=(const FlatMatrix<T>& oth);
	FlatMatrix<T> operator-(const FlatMatrix<T>& oth) const;
	FlatMatrix<T>& operator-=(const FlatMatrix<T>& oth);
	FlatMatrix<T> operator*(const FlatMatrix<T>& oth) const;
	FlatMatrix<T>& operator*=(const FlatMatrix<T>& oth);
	bool operator==(const FlatMatrix<T>& oth) const;
	void operator=(const FlatMatrix<T>& oth);
private:
	T* alloc(size_t rows, size_t cols, T value = T());
	T* data = nullptr;
	void Delete() {
		BaseMatrix<T>::rows = 0;
		BaseMatrix<T>::cols = 0;
		delete[] data;
	}
	void Copy(const FlatMatrix<T>& oth) {
		if (oth.BaseMatrix<T>::Get_cols() != BaseMatrix<T>::cols || oth.BaseMatrix<T>::Get_cols() != BaseMatrix<T>::rows) {
			Resize(oth.BaseMatrix<T>::Get_rows(), oth.BaseMatrix<T>::Get_cols());
		}

		for (int i = 0; i < BaseMatrix<T>::cols; i++) {
			for (int j = 0; j < BaseMatrix<T>::rows; j++) {
				Get(i, j) = oth.Get(i, j);
			}
		}
	}
};

template<typename T>
inline BaseMatrix<T>::BaseMatrix()
{

}

template<typename T>
inline BaseMatrix<T>::~BaseMatrix()
{

}

template<typename T>
inline BaseMatrix<T>::BaseMatrix(size_t rows, size_t cols) : rows(rows), cols(cols)
{
	
}

template<typename T>
BaseMatrix<T>::BaseMatrix(std::initializer_list<std::initializer_list<T>>& list) {
	int r = list.size();
	int c = -1;
	for (const auto& elem : list) {
		if (elem.size() != c && c != -1) {
			throw std::invalid_argument("Invalid argument!");
		}
		c = elem.size();
	}
	rows = r;
	cols = c;
}