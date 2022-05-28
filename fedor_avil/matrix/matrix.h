#pragma once
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <stddef.h>
template<typename T>
class BaseMatrix {
public:
	virtual void Resize(size_t row, size_t col) = 0;
	virtual T& Get(size_t row, size_t col) const = 0;
	virtual T* operator[] (size_t r) const = 0;
	virtual ~BaseMatrix() {};
	BaseMatrix& operator=(const BaseMatrix& rhs) {
		cols = rhs.cols;
		rows = rhs.rows;
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				(&this[i])[j] = (&rhs[i])[j];
			}
		}
		return *this;
	}
	size_t NumRows() const {
		return rows;
	}
	size_t NumCols() const {
		return cols;
	}
protected:
	size_t rows;
	size_t cols;
};
//Надо сделать проверку на типы 
template<typename T>
class FlatMatrix : public BaseMatrix<T>{
public:
	FlatMatrix(size_t r = 0, size_t c = 0) {
		data = new T[r*c];
		rows = r;
		cols = c;
	}
	inline T* operator[] (size_t r) const override {
		return (data + r * rows);
	}
	~FlatMatrix() = default; 
	T& Get(size_t r, size_t c) const override {
		if (r > rows || c > cols)
			throw std::out_of_range("Index Out Of Range");
		return data[r*rows+c];
	}
	void Resize(size_t row, size_t col) override {
		T* tempData = data;
		size_t rows_t = rows;
		size_t cols_t = cols;
		//delete[] data;
		data = new T[row * col];
		rows = row;
		cols = col;
		for (size_t i = 0; i < rows; i++){
			if (i < rows_t) {
				for (size_t j = 0; j < cols; j++) {
					if (j < cols_t) {
						data[i+j] = tempData[i+j];
					}
					else {
						break;
					}
				}
			}
			else {
				break;
			}
		}
		delete[] tempData;
	}
	FlatMatrix& operator=(const FlatMatrix& rhs) {
		cols = rhs.cols;
		rows = rhs.rows;
		delete[] data;
		data = new T[rows * cols];
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				data[i + j] = rhs.data[i + j];
			}
		}
		return *this;
	}
	FlatMatrix operator+(const FlatMatrix& rhs) const {
		return FlatMatrix(*this) += rhs;
	}
	FlatMatrix operator+(const T& rhs) const {
		return FlatMatrix(*this) += rhs;
	}
	FlatMatrix operator*(const T& rhs) const {
		return FlatMatrix(*this) *= rhs;
	}
	FlatMatrix operator/(const T& rhs) const {
		return FlatMatrix(*this) /= rhs;
	}
	FlatMatrix operator*(const FlatMatrix& rhs) {
		return FlatMatrix(*this) *= rhs;
	}
	FlatMatrix operator-(const FlatMatrix& rhs) const {
		return FlatMatrix(*this) -= rhs;
	}
	FlatMatrix operator-(const T& rhs) const {
		return FlatMatrix(*this) -= rhs;
	}
	FlatMatrix& operator+=(const FlatMatrix& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				*(data + j * i) += *(rhs.data + j * i);
			}
		}
		return *this;
	}
	FlatMatrix& operator-=(const FlatMatrix& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				*(data + j * i) *= *(rhs.data + j * i);
			}
		}
		return *this;
	}
	FlatMatrix& operator+=(const T& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				*(data + j * i) += rhs;
			}
		}
		return *this;
	}
	FlatMatrix& operator-=(const T& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				*(data + j * i) -= rhs;
			}
		}
		return *this;
	}
	FlatMatrix& operator*=(const T& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				*(data + j * i) *= rhs;
			}
		}
		return *this;
	}
	FlatMatrix& operator/=(const T& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				*(data + j * i) /= rhs;
			}
		}
		return *this;
	}
	FlatMatrix& operator*=(const FlatMatrix& rhs) {
		FlatMatrix tempMatr(rows, rhs.cols);
		if (rows != rhs.cols) {
			throw std::exception("You can't multiply these matrix!");
		}
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < rhs.cols; j++) {
				tempMatr.data[i+j]= 0;
				for (size_t k = 0; k < rhs.cols; k++) {
					tempMatr.data[i+j] += data[i+k] * rhs.data[k+j];
				}
			}
		}
		return tempMatr;
	}
private:
	T* data = nullptr;

};

template<typename T>
class TableMatrix : public BaseMatrix<T>{
public:
	TableMatrix(size_t r, size_t c) {
		data = new T*[r];
		for (size_t i = 0; i < r; ++i) {
			data[i] = new T[c];
		}
		cols = c;
		rows = r;
	}
	~TableMatrix() {
		for (size_t i = 0; i < rows; ++i) {
			delete[] data[i];
		}
	}
	T& Get(size_t r, size_t c) const override {
		if (r > rows || c > cols)
			throw std::out_of_range("Index Out Of Range");
		return (&*data[r])[c];
	}
	inline T* operator[] (size_t r) const override {
		return data[r];
	}
	void Resize(size_t row, size_t col) override {
		T** tempData = data;
		//delete[] data;
		data = new T*[row];
		rows = row;
		cols = col;
		for (size_t i = 0; i < rows; i++) {
			data[i] = new T[col];
			if (i < sizeof(tempData)) {
				for (size_t j = 0; j < cols; j++) {
					if (j < sizeof(tempData[i])) {
						data[i][j] = tempData[i][j];
					}
					else {
						break;
					}
				}
			}
			else {
				break;
			}
		}
		delete[] tempData;
	}
	TableMatrix operator+(const TableMatrix& rhs) const {
		return TableMatrix(*this) += rhs;
	}	
	TableMatrix operator+(const T& rhs) const {
		return TableMatrix(*this) += rhs;
	}
	TableMatrix operator*(const T& rhs) const {
	return TableMatrix(*this) *= rhs;
	}
	TableMatrix operator/(const T& rhs) const {
	return TableMatrix(*this) /= rhs;
	}
	TableMatrix operator*(const TableMatrix& rhs) {
		return TableMatrix(*this) *= rhs;
	}
	TableMatrix operator-(const TableMatrix& rhs) const {
		return TableMatrix(*this) -= rhs;
	}
	TableMatrix operator-(const T& rhs) const {
		return TableMatrix(*this) -= rhs;
	}
	/*T operator+(const TableMatrix& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				rhs.data[i][j] += *this;
			}
		}
		return rhs;
	}*/
	/*T operator-(const TableMatrix& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				rhs.data[i][j] -= *this;
			}
		}
		return rhs;
	}*/
	TableMatrix& operator+=(const TableMatrix& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				data[i][j] += rhs.data[i][j];
			}
		}
		return *this;
	}
	TableMatrix& operator-=(const TableMatrix& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				data[i][j] -= rhs.data[i][j];
			}
		}
		return *this;
	}
	TableMatrix& operator+=(const T& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				data[i][j] += rhs;
			}
		}
		return *this;
	}
	TableMatrix& operator-=(const T& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				data[i][j] -= rhs;
			}
		}
		return *this;
	}
	TableMatrix& operator*=(const T& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				data[i][j] *= rhs;
			}
		}
		return *this;
	}
	TableMatrix& operator/=(const T& rhs) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				data[i][j] /= rhs;
			}
		}
		return *this;
	}
	TableMatrix& operator*=(const TableMatrix& rhs) {
		TableMatrix tempMatr (rows, rhs.cols);
		if (rows != rhs.cols) {
			throw std::exception("You can't multiply these matrix!");
		}
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < rhs.cols; j++) {
				tempMatr.data[i][j] = 0;
				for (size_t k = 0; k < rhs.cols; k++) {
					tempMatr.data[i][j] += data[i][k] * rhs.data[k][j];
				}
			}
		}
		return tempMatr;
	}
	/*TableMatrix& operator=(const FlatMatrix& rhs) {
		cols = rhs.cols;
		rows = rhs.rows;
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				data[i][j] = rhs.data[i][j];
			}
		}
		return *this;
	}*/
private:
	T** data = nullptr;	
};