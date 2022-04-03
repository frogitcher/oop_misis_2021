#include "rational.h"
#include <stdexcept>
#include <algorithm>

int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

int lcm(int a, int b) {
    return std::abs(a * b) / gcd(a, b);
}


Rational::Rational(int _num) {
    num = _num;
    den = 1;
}

Rational::Rational(int _num, int _den) {
    num = _num;
    den = _den;
    if (den == 0) {
        throw std::invalid_argument("denominator must not be equal to 0");
    }
    Normalize();
}

Rational::Rational(const Rational& other) {
    num = other.num;
    den = other.den;
}


Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.num;
    den = rhs.den;
    Normalize();
    return *this;
}


Rational& Rational::operator+=(const Rational& rhs) {
    int common = lcm(den, rhs.den);
    num = num * (common / den) + rhs.num * (common / rhs.den);
    den = common;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    int common = lcm(den, rhs.den);
    num = num * (common / den) - rhs.num * (common / rhs.den);
    den = common;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    num *= rhs.num;
    den *= rhs.den;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num == 0) {
        throw std::invalid_argument("it is impossible to divide by 0");
    }
    num *= rhs.den;
    den *= rhs.num;
    Normalize();
    return *this;
}


Rational Rational::operator+(const Rational& rhs) const {
    return Rational(*this) += rhs;
}

Rational Rational::operator-(const Rational& rhs) const {
    return Rational(*this) -= rhs;
}

Rational Rational::operator*(const Rational& rhs) const {
    return Rational(*this) *= rhs;
}

Rational Rational::operator/(const Rational& rhs) const {
    return Rational(*this) /= rhs;
}


Rational Rational::operator+() const {
    return Rational(*this);
}

Rational Rational::operator-() const{
    Rational temp(*this);
    temp *= Rational(-1);
    return temp;

    // return -this...
}

bool Rational::operator<(const Rational& rhs) const {
    return num * rhs.den < rhs.num * den;
}

bool Rational::operator<=(const Rational& rhs) const {
    return num * rhs.den <= rhs.num * den;
}

bool Rational::operator>(const Rational& rhs) const {
    return num * rhs.den > rhs.num * den;
}

bool Rational::operator>=(const Rational& rhs)const {
    return num * rhs.den >= rhs.num * den;
}

bool Rational::operator==(const Rational& rhs)const {
    return num * rhs.den == rhs.num * den;
}

bool Rational::operator!=(const Rational& rhs) const {
    return num * rhs.den != rhs.num * den;
}


Rational& Rational::operator++() {
    num += den;
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp(*this);
    ++*this;
    return temp;
}

Rational& Rational::operator--() {
    num -= den;
    return *this;
}

Rational Rational::operator--(int) {
    Rational temp(*this);
    --*this;
    return temp;
}


int Rational::getNominator() const {
    return num;
}

int Rational::getDenominator() const {
    return den;
}


void Rational::Normalize() {
    int g = gcd(abs(num), den);
    num /= g;
    den /= g;
}
