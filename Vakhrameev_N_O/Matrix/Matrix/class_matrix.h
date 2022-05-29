#pragma once
#include <stdexcept>
#include <string>
#include <stddef.h>
#include <iostream>
template<typename T>

class BaseMatrix
{
public:
	BaseMatrix(size_t r, size_t c);
	~BaseMatrix();

	virtual void resize(size_t n, size_t m,T value=T(0))=0;
	virtual T& Get(size_t n, size_t m) const =0;
	virtual void diag(size_t n=0,T value=T(0)) = 0;


	bool is_square() const;
	size_t get_columns() const;
	size_t get_rows() const;
protected:
	size_t columns = 0;
	size_t rows = 0;
};

template<typename T>
BaseMatrix<T>::BaseMatrix(size_t r, size_t c)
	: rows(r)
	, columns(c) {}

template<typename T>
BaseMatrix<T>::~BaseMatrix()=default;

template<typename T>
bool BaseMatrix<T>::is_square() const
{
	return rows == columns;
}

template<typename T>
size_t BaseMatrix<T>::get_columns() const
{
	return columns;
}

template<typename T>
size_t BaseMatrix<T>::get_rows() const
{
	return rows;
}


