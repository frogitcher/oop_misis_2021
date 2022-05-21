#pragma once

#include <ostream>

class Vector {
public:
    Vector() = default;

    Vector(Vector &vector);

    Vector(int size);

    ~Vector() = default;

    Vector operator+(const double &value) const;

    Vector operator-(const double &value) const;

    Vector operator*(const double &value) const;

    Vector operator*(const Vector &vector) const;

    Vector operator=(const Vector &vector);

    const bool operator==(const Vector &vector);

    const bool operator!=(const Vector &vector);

    const double operator[](int index);

    void norm();

    int get_size();

    double[]

    get_data();


private:
    int size;
    double[]
    data;
}
