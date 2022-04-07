#include <iostream>
#include <fstream>
#pragma once
#ifndef RATIONAL_RATIONAL_H_20220311
#define RATIONAL_RATIONAL_H_20220311

class Rational {
public:

    Rational() = default;
    Rational(double _num); 
    Rational(double _num, double _den); 
    Rational(const Rational& other); 
    ~Rational() = default; 

    double num, den; 

    Rational operator+(const Rational& rhs); 
    Rational operator-(const Rational& rhs);
    Rational operator*(const Rational& rhs);
    Rational operator/(const Rational& rhs);

    Rational& operator=(const Rational& rhs); 
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    bool operator<(const Rational& rhs);
    bool operator>(const Rational& rhs);
    bool operator<=(const Rational& rhs);
    bool operator>=(const Rational& rhs);
    bool operator==(const Rational& rhs);
    bool operator!=(const Rational& rhs);

    void Normalize();
    int gcd(int num, int den);

    Rational operator-();
};

inline std::ostream& operator<<(std::ostream& os, const Rational& rhs)
{
    os << rhs.num / rhs.den;
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& rhs)
{
    is >> rhs.num >> rhs.den;
    return is;
}
#endif 