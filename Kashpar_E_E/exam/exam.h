#pragma once
#include <stddef.h>


class Vector {
public:
    Vector() = default;
    Vector(size_t _size);
    Vector(size_t _size, double value);
    Vector(const Vector &other);
    ~Vector();

    double& operator[](const size_t i);
    double& at(size_t i);

    Vector& operator+=(const Vector &other);
    Vector& operator-=(const Vector &other);
    Vector& operator*=(double n);

    Vector operator+(const Vector &other);
    Vector operator-(const Vector &other);
    Vector operator*(double n);

    double length();

    double scalar_mult(const Vector &other);

    bool operator==(const Vector &other);
    bool operator!=(const Vector &other);
private:
    double *data = new double[0];
    size_t size = 0;
};
