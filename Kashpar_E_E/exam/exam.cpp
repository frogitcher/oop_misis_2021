#include "exam.h"
#include <stdexcept>
#include <stddef.h>
#include <algorithm>

Vector::Vector(size_t _size) {
    size = _size;
    data = new double[_size];
    std::fill(data, data + _size, 0);
}

Vector::Vector(size_t _size, double value) {
    size = _size;
    data = new double[_size];
    std::fill(data, data + _size, value);
}

Vector::Vector(const Vector &other) {
    size = other.size;
    data = new double[size];
    std::copy(data, data + size, other.data);
}

Vector::~Vector() {
    delete[] data;
}

double& Vector::operator[](const size_t i) {
    if (i < size)
        return data[i];
    else
        throw std::invalid_argument("NO");
}

double& Vector::at(size_t i) {
    if (i < size)
        return data[i];
    else
        throw std::invalid_argument("NO");
}

Vector& Vector::operator+=(const Vector &other) {
    for (int i = 0; i < size; i++) {
        data[i] += other.data[i];
    }
    return *(this);
}

Vector& Vector::operator-=(const Vector &other) {
    for (int i = 0; i < size; i++) {
        data[i] -= other.data[i];
    }
    return *(this);
}

Vector& Vector::operator*=(double n) {
    for (int i = 0; i < size; i++) {
        data[i] *= n;
    }
    return *(this);
}

Vector Vector::operator+(const Vector &other) {
    return Vector(*this) += other;
}

Vector Vector::operator-(const Vector &other) {
    return Vector(*this) -= other;
}

Vector Vector::operator*(double n) {
    return Vector(*this) *= n;
}

double Vector::scalar_mult(const Vector &other) {
    if (size != other.size) {
        throw std::invalid_argument("NO");
    }
    double ans = 0;
    for (int i = 0; i < size; i++) {
        ans += data[i] * other.data[i];
    }
    return ans;
}

bool Vector::operator==(const Vector &other) {
    if (size == other.size) {
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }
    return false;
}

bool Vector::operator!=(const Vector &other) {
    return !(*this == other);
}
