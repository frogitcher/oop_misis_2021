#include "Rational.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>

Rational::Rational(int _num) 
    : num(_num)
    , den(1) {
}

Rational Rational::operator+(const Rational& rhs) { 
    return (Rational(*this) += rhs);
}

Rational Rational::operator-(const Rational& rhs) { 
    return (Rational(*this) -= rhs);
}

Rational Rational::operator*(const Rational& rhs) { 
    return (Rational(*this) *= rhs);
}

Rational Rational::operator/(const Rational& rhs) { 
    return (Rational(*this) /= rhs);
}

bool Rational::operator<(const Rational& rhs) { 
    return (num * rhs.den < rhs.num * den);
}

bool Rational::operator>(const Rational& rhs) {
    return (num * rhs.den > rhs.num * den);
}

bool Rational::operator<=(const Rational& rhs) {
    return (!(num * rhs.den > rhs.num * den));
}

bool Rational::operator>=(const Rational& rhs) {
    return (!(num * rhs.den < rhs.num * den));
}

bool Rational::operator==(const Rational& rhs) {
    return (num * rhs.den == rhs.num * den);
}

bool Rational::operator!=(const Rational& rhs) {
    return (num * rhs.den != rhs.num * den);
}

Rational& Rational::operator+=(const Rational& rhs){ 
    num = num * rhs.den + rhs.num * den;
    den = den * rhs.den;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    num = num * rhs.den - rhs.num * den;
    den = den * rhs.den;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    num = num * rhs.num;
    den = den * rhs.den;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    num = num * rhs.den;
    den = den * rhs.num;
    Normalize();
    return *this;
}

Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.num;
    den = rhs.den;
    return *this;
}

Rational::Rational(int _num, int _den) 
    : num(_num)
    , den(_den) {
        if (den == 0) {
            throw std::invalid_argument("denominator must not be 0");
        }
}

Rational::Rational(const Rational& other)
    : num(other.num)
    , den(other.den)
{}

void Rational::Normalize() {
    if (den < 0) {
        num *= -1;
        den *= -1;
    }
    int g = gcd(num, den);
    num /= g;
    den /= g;
}

int Rational::gcd(int num, int den) {
    if (num == 1) {
        return num;
    }

    if (num == 0) {
        return den;
    }

    if (den == 0) {
        return num;
    }

    if (num == den) {
        return num;
    }  

    if (num > den) {
        return gcd(num % den, den);
    }      
    return gcd(num, den % num);
}

Rational Rational::operator-() {
    num *= -1;
    return *this;
}

Rational& Rational::operator--() {
    return (Rational(*this) -= Rational(1, 1));
}

Rational& Rational::operator++() {
    return (Rational(*this) += Rational(1, 1));
}




