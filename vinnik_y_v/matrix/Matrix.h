#pragma once

#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template<typename T>
class TableMatrix;
template<typename T>
class FlatMatrix;

template<typename T>
class BaseMatrix {
public:
	BaseMatrix(const size_t r = 0, const size_t c = 0, const T value = T());
	BaseMatrix(std::initializer_list<std::initializer_list<T>>& list);
	virtual void Resize(size_t r, size_t c, T value = T()) = 0;
	virtual T& Get(size_t r, size_t c) const = 0;
	virtual T* operator[](size_t i) const = 0;
	~BaseMatrix();

	virtual void Transponse() noexcept = 0;
	virtual double Determinant() const = 0;
	virtual void Inverse() = 0;

	size_t Rows() const;
	size_t Columns() const;
	bool isSquare() const;
protected:
	size_t rows = 0;
	size_t cols = 0;
};

template<typename T>
class TableMatrix : public BaseMatrix<T> {
public:
	TableMatrix(size_t r = 0, size_t c = 0, T value = T());
	TableMatrix(std::initializer_list<std::initializer_list<T>> list);
	TableMatrix(const TableMatrix<T>& oth) noexcept;
	void Resize(size_t r, size_t c, T value = T()) override;
	T& Get(size_t r, size_t c) const override;
	T* operator[](size_t i) const override;
	~TableMatrix();

	TableMatrix<T>& operator+=(const TableMatrix<T>& oth);
	TableMatrix<T>& operator+=(const FlatMatrix<T>& oth);
	TableMatrix<T> operator+(const TableMatrix<T>& oth) const;
	TableMatrix<T> operator+(const FlatMatrix<T>& oth) const;

	TableMatrix<T>& operator-=(const TableMatrix<T>& oth);
	TableMatrix<T>& operator-=(const FlatMatrix<T>& oth);
	TableMatrix<T> operator-(const TableMatrix<T>& oth) const;
	TableMatrix<T> operator-(const FlatMatrix<T>& oth) const;

	TableMatrix<T>& operator*=(const TableMatrix<T>& oth);
	TableMatrix<T>& operator*=(const FlatMatrix<T>& oth);
	TableMatrix<T>& operator*=(const double num) noexcept;
	TableMatrix<T> operator*(const TableMatrix<T>& oth) const;
	TableMatrix<T> operator*(const FlatMatrix<T>& oth) const;
	TableMatrix<T> operator*(const double num) const noexcept;

	TableMatrix<T>& operator/=(const double num);
	TableMatrix<T>& operator/(const double num) const;

	bool operator==(const TableMatrix<T>& oth) const noexcept;
	bool operator==(const FlatMatrix<T>& oth) const noexcept;

	void Transponse() noexcept override;
	double Determinant() const override;
	void Inverse() override;

	inline T** Data();
	void CopyFromOth(const FlatMatrix<T>& oth);
	void CopyFromOth(const TableMatrix<T>& oth);
private:
	static T** Alloc(size_t r, size_t c, T value = T()) noexcept;
	void CopyData(T** oth_data) noexcept;
	void DeleteData() noexcept;
private:
	T** data = nullptr;
};

template<typename T>
class FlatMatrix : public BaseMatrix<T> {
public:
	FlatMatrix(size_t r = 0, size_t c = 0, T value = T());
	FlatMatrix(std::initializer_list<std::initializer_list<T>> list);
	FlatMatrix(const FlatMatrix<T>& oth) noexcept;
	void Resize(size_t r, size_t c, T value = T()) override;
	T& Get(size_t r, size_t c) const override;
	T* operator[](size_t i) const override;
	~FlatMatrix();

	FlatMatrix<T>& operator+=(const TableMatrix<T>& oth);
	FlatMatrix<T>& operator+=(const FlatMatrix<T>& oth);
	FlatMatrix<T> operator+(const TableMatrix<T>& oth) const;
	FlatMatrix<T> operator+(const FlatMatrix<T>& oth) const;

	FlatMatrix<T>& operator-=(const TableMatrix<T>& oth);
	FlatMatrix<T>& operator-=(const FlatMatrix<T>& oth);
	FlatMatrix<T> operator-(const TableMatrix<T>& oth) const;
	FlatMatrix<T> operator-(const FlatMatrix<T>& oth) const;

	FlatMatrix<T>& operator*=(const TableMatrix<T>& oth);
	FlatMatrix<T>& operator*=(const FlatMatrix<T>& oth);
	FlatMatrix<T>& operator*=(const double num) noexcept;
	FlatMatrix<T> operator*(const TableMatrix<T>& oth) const;
	FlatMatrix<T> operator*(const FlatMatrix<T>& oth) const;
	FlatMatrix<T> operator*(const double num) const noexcept;

	FlatMatrix<T>& operator/=(const double num);
	FlatMatrix<T>& operator/(const double num) const;

	bool operator==(const TableMatrix<T>& oth) const noexcept;
	bool operator==(const FlatMatrix<T>& oth) const noexcept;

	void Transponse() noexcept override;
	double Determinant() const override;
	void Inverse() override;

	inline T* Data();
	void CopyFromOth(const FlatMatrix<T>& oth);
	void CopyFromOth(const TableMatrix<T>& oth);
private:
	static T* Alloc(size_t r, size_t c, T value = T());
	void CopyData(T* oth_data) noexcept;
	void DeleteData();
private:
	T* data = nullptr;
};

template<typename T>
BaseMatrix<T>::BaseMatrix(const size_t r, const size_t c, const T value) : rows(r), cols(c) {

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
	rows = r;
	cols = c;
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
bool BaseMatrix<T>::isSquare() const {
	return rows == cols;
}

template<typename T>
BaseMatrix<T>::~BaseMatrix() {

}

