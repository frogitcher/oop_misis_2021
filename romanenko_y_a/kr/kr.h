#pragma once
#include <iostream>

class Vector 
{
public:
    Vector(double[] idata);
    Vector(Vector& other);
    ~Vector() = default;
    double& operator[](int i);
    double at(int i);
    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;
    Vector operator*(const double rhs) const;
    Vector operator/(const double rhs) const;
    Vector& operator+=(Vector& rhs);
    Vector& operator-=(Vector& rhs);
    Vector& operator*=(double rhs);
    Vector& operator/=(double rhs);

    bool Vector operator==(Vector& rhs) const;
    bool Vector operator!=(Vector& rhs) const;

    Vector& operator=(Vector& rhs);

    double Norm();
    double Scal(Vector& rhs);
private:
    *double data;
    int size;
}