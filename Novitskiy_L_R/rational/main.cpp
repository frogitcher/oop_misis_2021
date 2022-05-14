#include "rational.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

Rational::normalize() {
    if (num == 0) {
        den = 1;
        return;
    }

    int g = gcd(abs(num), den);
    num /= g;
    den /= g;
    if (den < 0) {
        num *= -1;
        den *= -1;
    }
}

Rational::Rational(int _num) {
    num = _num;
    den = 1
}

Rational::Rational(int _num, int _den) {
    if (den == 0) {
        throw std::invalid_argument("Denominator must not be equal to 0")
    }
    num = _num;
    den = _den;
    normalize();
}

Rational::Rational(const Rational &other) {
    num = other.num;
    den = other.den;
}

Rational &Rational::operator=(const Rational &rhs) {
    num = rhs.num;
    den = rhs.den;
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    int common = lcm(den, rhs.den);
    num = num * (common / den) - rhs.num * (common / rhs.den);
    den = common;
    this->Normalize();
    return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
    int common = lcm(den, rhs.den);
    num = num * (common / den) + rhs.num * (common / rhs.den);
    den = common;
    this->Normalize();
    return *this;
}

Rational &operator*=(const Rational &rhs) {
    num *= ths.num;
    den *= ths.den;

    normalize();

    return this;
}

Rational &operator/=(const Rational &rhs){
    num *= ths.den;
    den *= ths.num;

    normalize();

    return this;
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

Rational Rational::operator-() const {
    return Rational(num*-1, den);
}

bool Rational::operator<(const Rational& rhs) const {
    return (num * rhs.den < rhs.num * den);
}

bool Rational::operator<=(const Rational& rhs) const {
    return !(*this > rhs);
}

bool Rational::operator>(const Rational& rhs) const {
    return (num * rhs.den > rhs.num* den);
}

bool Rational::operator>=(const Rational& rhs) const {
    return !(*this < rhs);
}

bool Rational::operator==(const Rational& rhs) const {
    return (num * rhs.den == rhs.num* den);
}

bool Rational::operator!=(const Rational& rhs) const {
    return (num * rhs.den != rhs.num* den);
}

Rational& Rational::operator++() {
    *this += Rational(1);
    return *this;
}

Rational Rational::operator++(int a) {
    Rational b(*this);
    *this += Rational(1);
    return b;
}

Rational& Rational::operator--() {
    *this -= Rational(1);
    return *this;
}

Rational Rational::operator--(int a) {
    Rational b(*this);
    *this -= Rational(1);
    return b;
}

int Rational::get_numerator() const {
    return num;
}

int Rational::get_denominator() const {
    return den;
}
