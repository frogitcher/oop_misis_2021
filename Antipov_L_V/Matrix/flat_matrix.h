#ifndef MATRIX_FLAT_MATRIX_H
#define MATRIX_FLAT_MATRIX_H

#pragma once

#include "base_matrix.h"
#include <ostream>
#include <stdexcept>

template<class T>
class FlatMatrix : public BaseMatrix<T> {
public:
    FlatMatrix(size_t rows = 0, size_t cols = 0, T value = 0);

    FlatMatrix(const FlatMatrix<T> &copy);

    FlatMatrix(std::initializer_list<std::initializer_list<T>> list);

    ~FlatMatrix();


    T *operator[](size_t row) const override;

    T &Get(size_t row, size_t col) const override;

    FlatMatrix<T> operator+(const FlatMatrix<T> &rhs) const;

    FlatMatrix<T> operator-(const FlatMatrix<T> &rhs) const;

    FlatMatrix<T> operator+(const T &value) const;

    FlatMatrix<T> operator-(const T &value) const;

    FlatMatrix<T> operator*(const FlatMatrix<T> &rhs) const;

    FlatMatrix<T> operator*(const T &value) const;

    void operator=(const FlatMatrix<T> &rhs);

    bool operator==(const FlatMatrix<T> &rhs) const;

    bool operator!=(const FlatMatrix<T> &rhs) const;


    void Resize(size_t rows, size_t cols) override;

    void Print();

private:
    T *data = nullptr;
};


template<class T>
FlatMatrix<T>::FlatMatrix(size_t rows, size_t cols, T value) : BaseMatrix<T>(rows, cols) {
    data = new T[rows * cols];
    std::fill(data, data + rows * cols, value);
}

template<class T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T> &copy) : BaseMatrix<T>(copy) {
    data = new T[copy.num_rows * copy.num_cols];
    std::copy(copy.data, copy.data + copy.num_rows * copy.num_cols, data);
}

template<class T>
FlatMatrix<T>::FlatMatrix(std::initializer_list<std::initializer_list<T>> list) : BaseMatrix<T>(list) {
    data = new T[(*this).num_rows * (*this).num_cols];
    int k = 0;
    for (auto now: list) {
        std::copy(now.begin(), now.end(), data + k * now.size());
        ++k;
    }
}

template<class T>
FlatMatrix<T>::~FlatMatrix() {
    delete[] data;
}

template<class T>
void FlatMatrix<T>::Resize(size_t rows, size_t cols) {
    T *new_data = new T[rows * cols];
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

template<class T>
void FlatMatrix<T>::Print() {
    for (size_t i = 0; i < BaseMatrix<T>::num_rows; ++i) {
        for (size_t j = 0; j < BaseMatrix<T>::num_cols; ++j) {
            std::cout << data[i * BaseMatrix<T>::num_cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

template<class T>
T *FlatMatrix<T>::operator[](size_t row) const {
    return data + (*this).num_cols * row;
}

template<class T>
T &FlatMatrix<T>::Get(size_t row, size_t col) const {
    return (*this)[row][col];
}

template<class T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T> &rhs) const {
    if (rhs.num_rows != (*this).num_rows || (*this).num_cols != rhs.num_cols) {
        throw std::length_error("Error");
    }
    FlatMatrix<T> temp(rhs.num_rows, rhs.num_cols);
    for (size_t i = 0; i < rhs.num_rows * rhs.num_cols; ++i) {
        temp.data[i] = data[i] + rhs.data[i];
    }
    return temp;
}

template<class T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T> &rhs) const {
    if (rhs.num_rows != (*this).num_rows || (*this).num_cols != rhs.num_cols) {
        throw std::length_error("Error");
    }
    FlatMatrix<T> temp(rhs.num_rows, rhs.num_cols);
    for (size_t i = 0; i < rhs.num_rows * rhs.num_cols; ++i) {
        temp.data[i] = data[i] - rhs.data[i];
    }
    return temp;
}

template<class T>
FlatMatrix<T> FlatMatrix<T>::operator+(const T &value) const {
    if ((*this).num_rows != (*this).num_cols) {
        throw std::length_error("Error");
    }
    FlatMatrix<T> temp(*this);
    for (size_t i = 0; i < (*this).num_rows * (*this).num_cols; i += (*this).num_cols + 1) {
        temp.data[i] += value;
    }
    return temp;
}

template<class T>
FlatMatrix<T> FlatMatrix<T>::operator-(const T &value) const {
    if ((*this).num_rows != (*this).num_cols) {
        throw std::length_error("Error");
    }
    FlatMatrix<T> temp(*this);
    for (size_t i = 0; i < (*this).num_rows * (*this).num_cols; i += (*this).num_cols + 1) {
        temp.data[i] -= value;
    }
    return temp;
}


template<class T>
FlatMatrix<T> FlatMatrix<T>::operator*(const T &value) const {
    FlatMatrix<T> temp(*this);
    for (size_t i = 0; i < (*this).num_rows * (*this).num_cols; ++i) {
        temp.data[i] *= value;
    }
    return temp;
}


template<class T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T> &rhs) const {
    if ((*this).num_cols != rhs.num_rows) {
        throw std::length_error("Error");
    }
    FlatMatrix<T> temp((*this).num_rows, rhs.num_cols);
    for (size_t i = 0; i < (*this).num_rows; i++) {
        for (size_t j = 0; j < rhs.num_cols; j++) {
            for (size_t k = 0; k < (*this).num_cols; k++) {
                temp[i][j] += (*this)[i][k] * rhs[k][j];
            }
        }
    }
    return temp;
}

template<class T>
void FlatMatrix<T>::operator=(const FlatMatrix<T> &rhs) {
    T *new_data = new T[rhs.num_rows * rhs.num_cols];
    std::copy(rhs.data, rhs.data + rhs.num_rows * rhs.num_cols, new_data);
    delete[] data;
    data = new_data;
    (*this).num_rows = rhs.num_rows;
    (*this).num_cols = rhs.num_cols;
}

template<class T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T> &rhs) const {
    if (rhs.num_rows == (*this).num_rows && (*this).num_cols == rhs.num_cols &&
        std::equal(data, data + (*this).num_rows * (*this).num_cols, rhs.data)) {
        return true;
    }
    return false;
}

template<class T>
bool FlatMatrix<T>::operator!=(const FlatMatrix<T> &rhs) const {
    return !(*this == rhs);
}

template<class T>
FlatMatrix<T> operator*(const T &value, const FlatMatrix<T> &rhs) {
    return rhs * value;
}

template<class T>
FlatMatrix<T> operator+(const T &value, const FlatMatrix<T> &rhs) {
    return rhs + value;
}

template<class T>
FlatMatrix<T> operator-(const T &value, const FlatMatrix<T> &rhs) {
    return rhs - value;
}

#endif //MATRIX_FLAT_MATRIX_H
