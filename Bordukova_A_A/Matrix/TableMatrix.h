#pragma once
#include "BaseMatrix.h"
#include <ostream>

template <typename T>
class TableMatrix : public BaseMatrix<T> {
public:
	//Constructors and destructors
	TableMatrix(const size_t& r = 0, const size_t& c = 0, const T& value = 0);
	TableMatrix(const std::initializer_list<std::initializer_list<T>>& list);
	TableMatrix(const TableMatrix<T>& other);
	~TableMatrix();
	void Resize(const size_t& r, const size_t& c, const T& value) override;

	//Pointers
	inline T& Get(const size_t& r, const size_t& c) const override {
		return *(*(data + r) + c);
	}
	inline T* operator[](const size_t& r) const override {
		return *(data + r);
	}

	//Assignment
	TableMatrix<T>& operator=(const TableMatrix<T>& rhs);

	//Logical operators
	inline bool operator==(const TableMatrix<T>& rhs) const {
		if (this->num_rows != rhs.num_rows || this->num_columns != rhs.num_columns) {
			return false;
		}
		for (size_t i = 0; i < this->num_rows; ++i) {
			for (size_t j = 0; j < this->num_columns; ++j) {
				if (data[i][j] != rhs.data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
	inline bool operator!=(const TableMatrix<T>& rhs) const {
		return !(*this == rhs);
	}

	//Arithmetical operators
	TableMatrix<T> operator+(const TableMatrix<T>& rhs) const;
	TableMatrix<T>& operator+=(const TableMatrix<T>& rhs);
	TableMatrix<T> operator-(const TableMatrix<T>& rhs) const;
	TableMatrix<T>& operator-=(const TableMatrix<T>& rhs);
	TableMatrix<T> operator*(const TableMatrix<T>& rhs) const;
	TableMatrix<T>& operator*=(const TableMatrix<T>& rhs);

	/*inline friend T* Get_Data(const TableMatrix<T>& fm) {
		return fm.data;
	}*/

private:
	T** data = nullptr;

	void Reallocate(const size_t& r, const size_t& c) override;
};

//Constructors and destructors
template<typename T>
TableMatrix<T>::TableMatrix(const size_t& r, const size_t& c, const T& value) {
	this->num_rows = r;
	this->num_columns = c;
	data = new T * [r];
	for (size_t i = 0; i < r; ++i) {
		data[i] = new T[c];
		std::fill(data[i], data[i] + c, value);
	}
}

template<typename T>
TableMatrix<T>::TableMatrix(const std::initializer_list<std::initializer_list<T>>& list) {
	this->num_rows = list.size();
	this->num_columns = list.begin()->size();
	data = new T * [this->num_rows];
	size_t row = 0;
	size_t col = 0;
	for (auto row_ : list) {
		data[row] = new T[this->num_columns];
		for (auto element_ : row_) {
			data[row][col] = element_;
			++col;
		}
		col = 0;
		++row;
	}
}

template<typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& other) {
	*this = other;
}

template<typename T>
TableMatrix<T>::~TableMatrix() {
	for (size_t i = 0; i < this->num_rows; ++i) {
		delete[] data[i];
	}
	delete[] data;
}

template<typename T>
void TableMatrix<T>::Resize(const size_t& r, const size_t& c, const T& value) {
	Reallocate(r, c);
	if (this->num_rows < r) {
		for (size_t i = this->num_rows; i < r; ++i) {
			for (size_t j = 0; j < std::min(c, this->num_columns); ++j) {
				data[i][j] = value;
			}
		}
	}
	if (this->num_columns < c) {
		for (size_t i = 0; i < std::min(r, this->num_rows); ++i) {
			for (size_t j = this->num_columns; j < c; ++j) {
				data[i][j] = value;
			}
		}
	}
	this->num_rows = r;
	this->num_columns = c;
}

//Assignment
template<typename T>
TableMatrix<T>& TableMatrix<T>::operator=(const TableMatrix<T>& rhs) {
	Reallocate(rhs.num_rows, rhs.num_columns);
	this->num_rows = rhs.num_rows;
	this->num_columns = rhs.num_columns;
	for (size_t i = 0; i < this->num_rows; ++i) {
		std::copy(rhs.data, rhs.data + this->num_rows, data);
		for (size_t j = 0; j < this->num_columns; ++j) {
			std::copy(rhs.data[i], rhs.data[i] + this->num_columns, data[i]);
		}
	}
	return *this;
}

//Arithmetical operators
template<typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T>& rhs) const {
	if (this->num_rows != rhs.num_rows || this->num_columns != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	return TableMatrix<T>(*this) += rhs;
}

template<typename T>
TableMatrix<T>& TableMatrix<T>::operator+=(const TableMatrix<T>& rhs) {
	if (this->num_rows != rhs.num_rows || this->num_columns != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	for (size_t i = 0; i < this->num_rows; ++i) {
		for (size_t j = 0; j < this->num_columns; ++j) {
			data[i][j] += rhs.data[i][j];
		}
	}
	return *this;
}

template<typename T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T>& rhs) const {
	if (this->num_rows != rhs.num_rows || this->num_columns != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	return TableMatrix<T>(*this) -= rhs;
}

template<typename T>
TableMatrix<T>& TableMatrix<T>::operator-=(const TableMatrix<T>& rhs) {
	if (this->num_rows != rhs.num_rows || this->num_columns != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	for (size_t i = 0; i < this->num_rows; ++i) {
		for (size_t j = 0; j < this->num_columns; ++j) {
			data[i][j] -= rhs.data[i][j];
		}
	}
	return *this;
}

template<typename T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T>& rhs) const {
	if (this->num_rows != rhs.num_columns) {
		throw std::invalid_argument("Matrix must be the same size!");
	}
	return TableMatrix<T>(*this) *= rhs;
}

template<typename T>
TableMatrix<T>& TableMatrix<T>::operator*=(const TableMatrix<T>& rhs) {
	if (this->num_columns != rhs.num_rows) {
		throw std::invalid_argument("Number of the rows in the first matrix must be the same as the number of columns in the second one!");
	}
	TableMatrix<T> res(this->num_rows, rhs.num_columns);
	for (size_t i = 0; i < this->num_rows; ++i) {
		for (size_t j = 0; j < rhs.num_columns; ++j) {
			T sum = 0;
			for (size_t k = 0; k < rhs.num_rows; ++k) {
				sum += data[i][k] * rhs.data[k][j];
			}
			res.data[i][j] = sum;
		}
	}
	return *this = res;
}


template<typename T>
void TableMatrix<T>::Reallocate(const size_t& r, const size_t& c) {
	if (this->num_rows < r || this->num_columns < c) {
		T** new_data = new T * [r];
		for (size_t i = 0; i < r; ++i) {
			new_data[i] = new T[c];
		}
		for (size_t i = 0; i < std::min(r, this->num_rows); ++i) {
			for (size_t j = 0; j < std::min(c, this->num_columns); ++j) {
				new_data[i][j] = data[i][j];
			}
			delete[] data[i];
		}
		delete[] data;
		data = new_data;
	}
}

/*template <typename T>
std::ostream& operator<<(std::ostream& os, const TableMatrix<T>& tm) {
	for (size_t i = 0; i < tm.Rows(); ++i) {
		for (size_t j = 0; j < tm.Columns(); ++j) {
			os << Get_Data(tm)[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}*/