#ifndef MATRIX_BASE_MATRIX_H
#define MATRIX_BASE_MATRIX_H

#pragma once

#include <initializer_list>

template<class T>
class BaseMatrix {
public:
    BaseMatrix(size_t rows, size_t cols);

    BaseMatrix(const BaseMatrix<T> &copy);

    BaseMatrix(std::initializer_list<std::initializer_list<T>> list);

    ~BaseMatrix() = default;

    size_t Cols();

    size_t Rows();

    virtual void Resize(size_t rows, size_t cols) = 0;

    virtual T &Get(size_t row, size_t col) const = 0;

    virtual T *operator[](size_t row) const = 0;


protected:
    size_t num_rows = 0;
    size_t num_cols = 0;
};


template<class T>
BaseMatrix<T>::BaseMatrix(size_t rows, size_t cols) {
    num_rows = rows;
    num_cols = cols;
}

template<class T>
BaseMatrix<T>::BaseMatrix(const BaseMatrix<T> &copy) {
    num_rows = copy.num_rows;
    num_cols = copy.num_cols;
}

template<class T>
BaseMatrix<T>::BaseMatrix(std::initializer_list<std::initializer_list<T>> list) {
    num_rows = list.size();
    num_cols = (*(list.begin())).size();
}

template<class T>
size_t BaseMatrix<T>::Cols() {
    return num_cols;
}

template<class T>
size_t BaseMatrix<T>::Rows() {
    return num_rows;
}

#endif //MATRIX_BASE_MATRIX_H
