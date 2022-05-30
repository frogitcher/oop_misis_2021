#pragma once
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

template <typename T>
class BaseMatrix {
public:
	BaseMatrix() = default;
	BaseMatrix(size_t n, size_t m, T value = 0);
	BaseMatrix(const std::initializer_list<std::initializer_list<T>>& mtr);
	BaseMatrix(const BaseMatrix& other);
	~BaseMatrix() = default;

	size_t Rows() const;
	size_t Columns() const;

	virtual void Resize(size_t n, size_t m) = 0;
	virtual T& Get(size_t n, size_t m) const = 0;
	virtual T* operator[](size_t index) const = 0;

	bool IsSquare() const;

protected:
	size_t rows = 0;
	size_t columns = 0;
};

template <typename T>
size_t BaseMatrix<T>::Rows() const {
	return rows;
}

template <typename T>
size_t BaseMatrix<T>::Columns() const {
	return columns;
}

template <typename T>
BaseMatrix<T>::BaseMatrix(size_t n, size_t m, T value) {
	rows = n;
	columns = m;
}

template <typename T>
BaseMatrix<T>::BaseMatrix(const std::initializer_list<std::initializer_list<T>>& mtr) {
	for (auto i : mtr) {
		if (i.size() != mtr.begin()->size()) {
			throw std::invalid_argument("Rows must be equal!");
		}
	}
	rows = mtr.size();
	columns = mtr.begin()->size();
}

template <typename T>
BaseMatrix<T>::BaseMatrix(const BaseMatrix& other) {
	rows = other.Rows();
	columns = other.Columns();
}

template <typename T>
bool BaseMatrix<T>::IsSquare() const {
	return (rows == columns);
}

//..........................................................................................

template <typename T>
class FlatMatrix: public BaseMatrix<T> {
public:
	FlatMatrix()=default;
	FlatMatrix(size_t n, size_t m, T value = 0);
	FlatMatrix(const std::initializer_list<std::initializer_list<T>>& mtr);
	FlatMatrix(const FlatMatrix& other);
	~FlatMatrix();

	void Resize(size_t n, size_t m);
	T& Get(size_t n, size_t m) const;
	T* operator[](size_t index) const;

	FlatMatrix<T> operator+(const T& a) const;
	FlatMatrix<T> operator+(const FlatMatrix<T>& other) const;
	FlatMatrix<T> operator-(const T& a) const;
	FlatMatrix<T> operator-(const FlatMatrix<T>& other) const;
	FlatMatrix<T> operator*(const T& a) const;
	FlatMatrix<T> operator*(const FlatMatrix<T>& other) const;

	bool operator==(const FlatMatrix<T>& other) const;
	bool operator!=(const FlatMatrix<T>& other) const;

	FlatMatrix<T> operator= (const FlatMatrix<T>& other);
private:
	T* data = nullptr;
	void reallocate(size_t n, size_t m);
};

template <typename T>
void FlatMatrix<T>::reallocate(size_t n, size_t m) {
	T* new_data = new T [n*m];
	for (int i=0; i<BaseMatrix<T>::rows; i++) {
		std::copy(data+i*BaseMatrix<T>::columns, data+(i+1)*BaseMatrix<T>::columns, new_data+i*m);
	}
	delete[]data;
	data = new_data;
}

template <typename T>
FlatMatrix<T>::FlatMatrix(size_t n, size_t m, T value): BaseMatrix<T>(n, m) {
	data = new T[BaseMatrix<T>::rows*BaseMatrix<T>::columns];
	std::fill(data, data+BaseMatrix<T>::rows*BaseMatrix<T>::columns, value);
}

template <typename T>
FlatMatrix<T>::FlatMatrix(const std::initializer_list<std::initializer_list<T>>& mtr): BaseMatrix<T>(mtr) {
	data = new T[BaseMatrix<T>::rows*BaseMatrix<T>::columns];
	int ind_i=0;
	for (auto i : mtr) {
        int ind_j = 0;
		for (auto j : i) {
			data[ind_i*BaseMatrix<T>::columns+ind_j]=j;
            ++ind_j;
		}
		++ind_i;
	}
}

template <typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix& other): BaseMatrix<T>(other.Rows(), other.Columns()){
	data = new T[BaseMatrix<T>::rows*BaseMatrix<T>::columns];
	for (int i=0; i<BaseMatrix<T>::rows; i++) {
		for (int j=0; j<BaseMatrix<T>::columns; j++) {
			data[i*BaseMatrix<T>::columns+j]=other.Get(i, j);
		}
	}
}

template <typename T>
FlatMatrix<T>::~FlatMatrix() {
	delete[]data;
}

template <typename T>
void FlatMatrix<T>::Resize(size_t n, size_t m) {
	if (n>BaseMatrix<T>::rows && m>BaseMatrix<T>::columns) {
        reallocate(n, m);
        for (int i=0; i<BaseMatrix<T>::rows; i++) {
			std::fill(data+i*m+BaseMatrix<T>::columns, data+(i+1)*m, 0);
		}
		std::fill(data+BaseMatrix<T>::rows*m, data+m*n, 0);
		BaseMatrix<T>::rows = n;
        BaseMatrix<T>::columns = m;
	}
	else {
        if (n>BaseMatrix<T>::rows) {
            reallocate(n, m);
            std::fill(data+BaseMatrix<T>::rows*BaseMatrix<T>::columns, data+m*n, 0);
        }
        if (m>BaseMatrix<T>::columns) {
            reallocate(n, m);
            for (int i=0; i<n; i++) {
                std::fill(data+i*m+BaseMatrix<T>::columns, data+(i+1)*m, 0);
            }
        }
        BaseMatrix<T>::rows = n;
        BaseMatrix<T>::columns = m;
	}

}

template <typename T>
T& FlatMatrix<T>::Get(size_t n, size_t m) const {
	if (n>= BaseMatrix<T>::rows || m >= BaseMatrix<T>::columns) {
		throw std::invalid_argument("Index is out of range!");
	}
	return data[n*BaseMatrix<T>::columns+m];
}

template <typename T>
T* FlatMatrix<T>::operator[](size_t index) const {
	if (index >= BaseMatrix<T>::rows) {
		throw std::invalid_argument("Index is out of range!");
	}
	return data+index*BaseMatrix<T>::columns;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const T& a) const {
	if (BaseMatrix<T>::IsSquare()) {
		FlatMatrix<T> matrix(*this);
		for (int i=0; i<BaseMatrix<T>::rows; i++) {
			for (int j=0; j<BaseMatrix<T>::columns; j++) {
				if (i==j) {
					matrix.data[i*BaseMatrix<T>::columns+j]+=a;
				}
			}
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Matrix must be square!");
	}



}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T>& other) const {
	if (BaseMatrix<T>::columns==other.Columns() && BaseMatrix<T>::rows==other.Rows()) {
		FlatMatrix<T> matrix(other);
		for (int i=0; i<BaseMatrix<T>::columns*BaseMatrix<T>::rows; i++) {
			matrix.data[i]+=data[i];
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}

}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const T& a) const {
	if (BaseMatrix<T>::IsSquare()) {
		FlatMatrix<T> matrix(*this);
		for (int i=0; i<BaseMatrix<T>::Rows(); i++) {
			for (int j=0; j<BaseMatrix<T>::Columns(); j++) {
				if (i==j) {
					matrix.data[i*BaseMatrix<T>::Columns()+j]-=a;
				}
			}
		}
        return matrix;
	}
	else {
		throw std::invalid_argument("Matrix must be square!");
	}

}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T>& other) const {
	if (BaseMatrix<T>::Columns()==other.BaseMatrix<T>::Columns() && BaseMatrix<T>::Rows()==other.BaseMatrix<T>::Rows()) {
		FlatMatrix<T> matrix(other);
		for (int i=0; i<BaseMatrix<T>::Columns()*BaseMatrix<T>::Rows(); i++) {
			matrix.data[i]-=data[i];
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}

}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const T& a) const {
	FlatMatrix<T> matrix(*this);
	for (int i=0; i<BaseMatrix<T>::rows*BaseMatrix<T>::columns; i++) {
		matrix.data[i]*=a;
	}
	return matrix;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& other) const {
	if (BaseMatrix<T>::columns==other.BaseMatrix<T>::Rows()) {
		FlatMatrix<T> matrix(BaseMatrix<T>::Rows(), other.BaseMatrix<T>::Columns());
		for (int i=0; i<BaseMatrix<T>::rows; i++) {
			for (int j=0; j<other.BaseMatrix<T>::Columns(); j++) {
				T sum = 0;
				for (int index=0; index< BaseMatrix<T>::columns; i++) {
					sum+=data[i*BaseMatrix<T>::columns+index]*other.data[index*other.BaseMatrix<T>::columns+j];
				}
				matrix.data[i*other.BaseMatrix<T>::Columns()+j]=sum;
			}
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}

}

template <typename T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T>& other) const {
	if (BaseMatrix<T>::rows!=other.BaseMatrix<T>::Rows() || BaseMatrix<T>::columns!=other.BaseMatrix<T>::Columns()) {
		return false;
	}
	return std::equal(data, data+BaseMatrix<T>::columns*BaseMatrix<T>::rows, other.data, other.data+other.BaseMatrix<T>::Columns()*other.BaseMatrix<T>::Rows());
}

template <typename T>
bool FlatMatrix<T>::operator!=(const FlatMatrix<T>& other) const {
	return !(*this==other);
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator=(const FlatMatrix<T>& other) {
	Resize(other.BaseMatrix<T>::rows, other.BaseMatrix<T>::columns);
	for (int i=0; i<BaseMatrix<T>::rows*BaseMatrix<T>::columns; i++) {
        data[i] = other.data[i];
	}
	return *this;
}

//..........................................................................................

template <typename T>
class TableMatrix: public BaseMatrix<T> {
public:
	TableMatrix()=default;
	TableMatrix(size_t n, size_t m, T value = 0);
	TableMatrix(const std::initializer_list<std::initializer_list<T>>& mtr);
	TableMatrix(const TableMatrix<T>& other);
	~TableMatrix();

	void Resize(size_t n, size_t m);
	T& Get(size_t n, size_t m) const;
	T* operator[](size_t index) const;

	TableMatrix<T> operator+(const T& a) const;
	TableMatrix<T> operator+(const TableMatrix<T>& other) const;
	TableMatrix<T> operator-(const T& a) const;
	TableMatrix<T> operator-(const TableMatrix<T>& other) const;
	TableMatrix<T> operator*(const T& a) const;
	TableMatrix<T> operator*(const TableMatrix<T>& other) const;

	bool operator==(const TableMatrix<T>& other) const;
	bool operator!=(const TableMatrix<T>& other) const;

	TableMatrix<T> operator= (const TableMatrix<T>& other);
private:
	T** data = nullptr;
	void reallocate(size_t n, size_t m);
};

template <typename T>
void TableMatrix<T>::reallocate(size_t n, size_t m) {
	T** new_data = new T* [n];
	for (int i=0; i<BaseMatrix<T>::rows; i++) {
		new_data[i] = new T[m];
		std::copy(data[i], data[i]+BaseMatrix<T>::columns, new_data[i]);
	}
	for (int i=BaseMatrix<T>::rows; i<n; i++) {
        new_data[i] = new T[m];
	}
	delete[]data;
	data = new_data;
}

template <typename T>
TableMatrix<T>::TableMatrix(size_t n, size_t m, T value): BaseMatrix<T>(n, m) {
	data = new T* [n];
	for (int i=0; i<BaseMatrix<T>::columns; i++) {
		data[i] = new T[m];
		std::fill(data[i], data[i]+BaseMatrix<T>::columns, value);
	}
}

template <typename T>
TableMatrix<T>::TableMatrix(const std::initializer_list<std::initializer_list<T>>& mtr): BaseMatrix<T>(mtr) {
	data = new T* [BaseMatrix<T>::rows];
	int ind_i = 0;
	for (auto i : mtr) {
		data[ind_i] = new T[BaseMatrix<T>::columns];
		std::copy(i.begin(), i.end(), data[ind_i]);
		++ind_i;
	}
}

template <typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& other): BaseMatrix<T>(other.BaseMatrix<T>::Rows(), other.BaseMatrix<T>::Columns()) {
	data = new T* [other.BaseMatrix<T>::Rows()];
	for (int i=0; i<BaseMatrix<T>::rows; i++) {
		data[i] = new T[other.BaseMatrix<T>::Columns()];
		std::copy(other.data[i], other.data[i]+other.BaseMatrix<T>::Columns(), data[i]);
	}
}

template <typename T>
TableMatrix<T>::~TableMatrix() {
	for (int i=0; i<BaseMatrix<T>::rows; i++) {
		delete[]data[i];
	}
	delete[]data;
}

template <typename T>
void TableMatrix<T>::Resize(size_t n, size_t m) {
	if (n>BaseMatrix<T>::rows && m>BaseMatrix<T>::columns) {
        reallocate(n, m);
        for (int i=0; i<BaseMatrix<T>::rows; i++) {
			std::fill(data[i]+BaseMatrix<T>::columns, data[i]+m, 0);
		}
		for (int i=BaseMatrix<T>::rows; i<n; i++) {
			std::fill(data[i], data[i]+m, 0);
		}

		BaseMatrix<T>::rows=n;
        BaseMatrix<T>::columns=m;
        return;
	}

	if (n>BaseMatrix<T>::rows) {
		reallocate(n, m);
		for (int i=BaseMatrix<T>::rows; i<n; i++) {
			std::fill(data[i], data[i]+BaseMatrix<T>::columns, 0);
		}
	}

	if (m>BaseMatrix<T>::columns) {
		reallocate(n, m);
		for (int i=0; i<n; i++) {
			std::fill(data[i]+BaseMatrix<T>::columns, data[i]+m, 0);
		}
	}

	BaseMatrix<T>::rows=n;
	BaseMatrix<T>::columns=m;
}

template <typename T>
T& TableMatrix<T>::Get(size_t n, size_t m) const {
	if (n>= BaseMatrix<T>::rows || m >= BaseMatrix<T>::columns) {
		throw std::invalid_argument("Index is out of range!");
	}
	return data[n][m];
}

template <typename T>
T* TableMatrix<T>::operator[](size_t index) const {
	if (index >= BaseMatrix<T>::rows) {
		throw std::invalid_argument("Index is out of range!");
	}
	return data[index];
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const T& a) const {
	if (BaseMatrix<T>::IsSquare()) {
		TableMatrix<T> matrix(*this);
		for (int i=0; i<BaseMatrix<T>::rows; i++) {
			matrix.data[i][i]+=a;
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Matrix must be square!");
	}
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const T& a) const {
	if (BaseMatrix<T>::IsSquare()) {
		TableMatrix<T> matrix(*this);
		for (int i=0; i<BaseMatrix<T>::rows; i++) {
			matrix.data[i][i]-=a;
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Matrix must be square!");
	}
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const T& a) const {
	TableMatrix<T> matrix(*this);
	for (int i=0; i<BaseMatrix<T>::rows; i++) {
		for (int j=0; j<BaseMatrix<T>::columns; j++) {
			matrix.data[i][j]*=a;
		}
	}
	return matrix;
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T>& other) const {
	if (BaseMatrix<T>::rows == other.BaseMatrix<T>::Rows() && BaseMatrix<T>::columns == other.BaseMatrix<T>::Columns()) {
		TableMatrix<T> matrix(other);
		for (int i=0; i<BaseMatrix<T>::rows; i++) {
			for (int j=0; j<BaseMatrix<T>::columns; j++) {
				matrix.data[i][j]+=data[i][j];
			}
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T>& other) const {
	if (BaseMatrix<T>::rows == other.BaseMatrix<T>::Rows() && BaseMatrix<T>::columns == other.BaseMatrix<T>::Columns()) {
		TableMatrix<T> matrix(other);
		for (int i=0; i<BaseMatrix<T>::rows; i++) {
			for (int j=0; j<BaseMatrix<T>::columns; j++) {
				matrix.data[i][j]-=data[i][j];
			}
		}
		return matrix;
	}
	else {
		throw std::invalid_argument("Operation isn't permitted !");
	}
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T>& rhs) const{
    if (BaseMatrix<T>::columns != rhs.BaseMatrix<T>::Rows()){
        throw std::invalid_argument("Operation isn't permitted !");
    } else{
        TableMatrix<T> answer(BaseMatrix<T>::rows, rhs.BaseMatrix<T>::Columns());
        for (int i=0; i < answer.BaseMatrix<T>::Rows(); ++i){
            for (int j=0; j < answer.BaseMatrix<T>::Columns(); ++j){
                size_t index = 0;
                while (index < BaseMatrix<T>::columns){
                    answer[i][j] += (data[i][index] * rhs.data[index][j]);
                    ++index;
                }
            }
        }
        return answer;
    }
}

template <typename T>
bool TableMatrix<T>::operator==(const TableMatrix<T>& other) const {
	if (BaseMatrix<T>::rows!=other.BaseMatrix<T>::Rows() || BaseMatrix<T>::columns!=other.BaseMatrix<T>::Columns()) {
		return false;
	}
	for (int i=0; i<BaseMatrix<T>::rows; i++) {
		if (! std::equal(data[i], data[i]+BaseMatrix<T>::columns, other.data[i], other.data[i]+BaseMatrix<T>::columns)) {
			return false;
		}
	}
	return true;
}

template <typename T>
bool TableMatrix<T>::operator!=(const TableMatrix<T>& other) const {
	return !(*this==other);
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator= (const TableMatrix<T>& other) {
	if (other.BaseMatrix<T>::Rows()>BaseMatrix<T>::rows || other.BaseMatrix<T>::Columns()>BaseMatrix<T>::columns) {
		reallocate(other.BaseMatrix<T>::Rows(), other.BaseMatrix<T>::Columns());
	}
	BaseMatrix<T>::rows=other.BaseMatrix<T>::Rows();
	BaseMatrix<T>::columns=other.BaseMatrix<T>::Columns();

	for (int i=0; i<BaseMatrix<T>::columns; i++) {
		std::copy(other.data[i], other.data[i]+other.BaseMatrix<T>::Columns(), data[i]);
	}
	return *this;

}

