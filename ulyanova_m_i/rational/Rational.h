#pragma once
#include <iostream>
#include <fstream>

class Rational {

public:

    int num, den;

    Rational() = default;
    Rational(int _num); 
    Rational(int _num, int _den); 
    Rational(const Rational& other); 
    ~Rational() = default; 

    Rational operator+(const Rational& rhs); 
    Rational operator-(const Rational& rhs);
    Rational operator*(const Rational& rhs);
    Rational operator/(const Rational& rhs);

    Rational& operator=(const Rational& rhs); 
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);
 
    Rational& operator++();
    Rational& operator--();
    Rational operator--(int x);
    Rational operator++(int x);

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
