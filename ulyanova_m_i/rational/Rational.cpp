#include <iostream>
#include "Rational.h"
#include <stdexcept>
#include <math.h>
#include <algorithm>

Rational::Rational(double _num) {
    num = _num;
    den = 1.0;
}

Rational Rational::operator+(const Rational& rhs) { 
    if (den == rhs.den) {
        return ((num + rhs.num) / den * 1.0);
    }
    else {
        return ((1.0 * num * rhs.den + 1.0 * rhs.num * den) / (den * rhs.den) * 1.0);
    }
}

Rational Rational::operator-(const Rational& rhs) { 
    if (den == rhs.den) {
        return ((num - rhs.num) / den);
    }
    else {
        return ((num * rhs.den - rhs.num * den) / (den * rhs.den));
    }
}

Rational Rational::operator*(const Rational& rhs) { 
    return ((num * rhs.num) / (den * rhs.den));
}

Rational Rational::operator/(const Rational& rhs) { 
    return ((num * rhs.den) / (den * rhs.num));
}

bool Rational::operator<(const Rational& rhs) { 
    return (num * rhs.den < rhs.num* den);
}

bool Rational::operator>(const Rational& rhs) {
    return (num * rhs.den > rhs.num * den);
}

bool Rational::operator<=(const Rational& rhs) {
    return (num * rhs.den <= rhs.num * den);
}

bool Rational::operator>=(const Rational& rhs) {
    return (num * rhs.den >= rhs.num * den);
}

bool Rational::operator==(const Rational& rhs) {
    return (num * rhs.den == rhs.num * den);
}

bool Rational::operator!=(const Rational& rhs) {
    return (num * rhs.den != rhs.num * den);
}

Rational& Rational::operator+=(const Rational& rhs){ 
    double x = num * rhs.den * 1.0 + rhs.num * den * 1.0;
    double y = den * rhs.den * 1.0;
    *this = x / y;
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    double x = num * rhs.den * 1.0 - rhs.num * den * 1.0;
    double y = den * rhs.den * 1.0;
    *this = x / y;
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    double x = num * rhs.num * 1.0;
    double y = den * rhs.den * 1.0;
    *this = x / y;
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    double x = num * rhs.den * 1.0;
    double y = den * rhs.num * 1.0;
   *this = x / y;
    return *this;
}

Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.num;
    den = rhs.den;
    //*this = num / den;
    return *this;
}

Rational::Rational(double _num, double _den) 
    : num(_num)
    , den(_den) {
    if (den == 0) {
        throw std::invalid_argument("denominator must not be 0");
    }
}

void Rational::Normalize() {
    int g = gcd(abs(num), den);
    num /= g;
    den /= g;
}

int Rational::gcd(int num, int den) {
    if (num == den) {
        return num;
    }   
    if (num > den) {
        return gcd(num % den, den);
    }      
    return gcd(num, den % num);
}

Rational Rational::operator-() {
    int res = -(num / den);
    return res;
}


