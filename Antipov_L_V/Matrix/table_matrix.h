#ifndef MATRIX_TABLE_MATRIX_H
#define MATRIX_TABLE_MATRIX_H

#pragma once

#include "base_matrix.h"
#include <ostream>

template<class T>
class TableMatrix : public BaseMatrix<T> {
public:
    TableMatrix(size_t rows = 0, size_t cols = 0, T value = 0);

    TableMatrix(const TableMatrix<T> &copy);

    TableMatrix(std::initializer_list<std::initializer_list<T>> list);

    ~TableMatrix();


    T &Get(size_t row, size_t col) const override;

    void Resize(size_t rows, size_t cols) override;


    T *operator[](size_t row) const override;

    TableMatrix<T> operator+(const TableMatrix<T> &rhs) const;

    TableMatrix<T> operator+(const T &value) const;

    TableMatrix<T> operator-(const T &value) const;

    TableMatrix<T> operator-(const TableMatrix<T> &rhs) const;

    TableMatrix<T> operator*(const T &value) const;

    TableMatrix<T> operator*(const TableMatrix<T> &rhs) const;

    bool operator==(const TableMatrix<T> &rhs) const;

    bool operator!=(const TableMatrix<T> &rhs) const;

    void operator=(const TableMatrix<T> &rhs);

    void Print();

private:
    T **data = nullptr;
};


template<class T>
TableMatrix<T>::TableMatrix(size_t rows, size_t cols, T value) : BaseMatrix<T>(rows, cols) {
    data = new T *[rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = new T[cols];
        std::fill(data[i], data[i] + cols, value);
    }
}

template<class T>
TableMatrix<T>::TableMatrix(const TableMatrix<T> &copy) : BaseMatrix<T>(copy) {
    data = new T *[copy.num_rows];
    for (size_t i = 0; i < copy.num_rows; ++i) {
        data[i] = new T[copy.num_cols];
        std::copy(copy.data[i], copy.data[i] + copy.num_cols, data[i]);
    }
}

template<class T>
TableMatrix<T>::TableMatrix(std::initializer_list<std::initializer_list<T>> list) : BaseMatrix<T>(list) {
    data = new T *[(*this).num_rows];
    int k = 0;
    for (auto now: list) {
        data[k] = new T[(*this).num_cols];
        std::copy(now.begin(), now.end(), data[k]);
        k++;
    }
}

template<class T>
TableMatrix<T>::~TableMatrix() {
    for (size_t i = 0; i < (*this).num_rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

template<class T>
T *TableMatrix<T>::operator[](size_t ind) const {
    return data[ind];
}

template<class T>
T &TableMatrix<T>::Get(size_t row, size_t col) const {
    return (*this)[row][col];
}

template<class T>
void TableMatrix<T>::Resize(size_t rows, size_t cols) {
    T **new_data = new T *[rows];
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

template<class T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T> &rhs) const {
    if (rhs.num_rows != (*this).num_rows || (*this).num_cols != rhs.num_cols) {
        throw std::length_error("Error");
    }
    TableMatrix<T> temp(rhs.num_rows, rhs.num_cols);
    for (size_t i = 0; i < (*this).num_rows; ++i) {
        for (size_t j = 0; j < (*this).num_cols; ++j) {
            temp[i][j] += (*this)[i][j] + rhs[i][j];
        }
    }
    return temp;
}

template<class T>
TableMatrix<T> TableMatrix<T>::operator+(const T &value) const {
    if ((*this).num_rows != (*this).num_cols) {
        throw std::length_error("Error");
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

template<class T>
TableMatrix<T> TableMatrix<T>::operator-(const T &value) const {
    if ((*this).num_rows != (*this).num_cols) {
        throw std::length_error("Error");
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

template<class T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T> &rhs) const {
    if (rhs.num_rows != (*this).num_rows || (*this).num_cols != rhs.num_cols) {
        throw std::length_error("Error");
    }
    TableMatrix<T> temp(rhs.num_rows, rhs.num_cols);
    for (size_t i = 0; i < (*this).num_rows; ++i) {
        for (size_t j = 0; j < (*this).num_cols; ++j) {
            temp[i][j] += (*this)[i][j] - rhs[i][j];
        }
    }
    return temp;
}

template<class T>
TableMatrix<T> TableMatrix<T>::operator*(const T &value) const {
    TableMatrix<T> temp((*this));
    for (size_t i = 0; i < (*this).num_rows; ++i) {
        for (size_t j = 0; j < (*this).num_cols; ++j) {
            temp[i][j] *= value;
        }
    }
    return temp;
}

template<class T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T> &rhs) const {
    if ((*this).num_cols != rhs.num_rows) {
        throw std::length_error("Error");
    }
    TableMatrix<T> temp((*this).num_rows, rhs.num_cols);
    for (size_t i = 0; i < (*this).num_rows; i++) {
        for (size_t j = 0; j < rhs.num_cols; j++) {
            for (size_t k = 0; k < (*this).num_cols; k++) {
                temp[i][j] += data[i][k] * rhs[k][j];
            }
        }
    }
    return temp;
}

template<class T>
bool TableMatrix<T>::operator==(const TableMatrix<T> &rhs) const {
    if (rhs.num_rows != (*this).num_rows || (*this).num_cols != rhs.num_cols) {
        return false;
    }
    for (size_t i = 0; i < rhs.num_rows; ++i) {
        if (!(std::equal(rhs.data[i], rhs.data[i] + rhs.num_cols, data[i]))) {
            return false;
        }
    }
    return true;
}

template<class T>
bool TableMatrix<T>::operator!=(const TableMatrix<T> &rhs) const {
    return !(*this == rhs);
}

template<class T>
void TableMatrix<T>::operator=(const TableMatrix<T> &rhs) {
    T **new_data = new T *[rhs.num_rows];
    for (size_t i = 0; i < rhs.num_rows; ++i) {
        new_data[i] = new T[rhs.num_cols];
        std::copy(rhs.data[i], rhs.data[i] + rhs.num_cols, new_data[i]);
    }
    delete[] data;
    data = new_data;
    (*this).num_rows = rhs.num_rows;
    (*this).num_cols = rhs.num_cols;
}

template<class T>
void TableMatrix<T>::Print() {
    for (size_t i = 0; i < (*this).num_rows; ++i) {
        for (size_t j = 0; j < (*this).num_cols; ++j) {
            std::cout << (*this)[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<class T>
TableMatrix<T> operator*(const T &value, const TableMatrix<T> &rhs) {
    return rhs * value;
}

template<class T>
TableMatrix<T> operator+(const T &value, const TableMatrix<T> &rhs) {
    return rhs + value;
}

template<class T>
TableMatrix<T> operator-(const T &value, const TableMatrix<T> &rhs) {
    return rhs - value;
}


#endif //MATRIX_TABLE_MATRIX_H
