#include "rational.h"
#include <cmath>
#include <numeric>
#include <stdexcept>

Rational::Rational(int _num)
    : num(_num)
    , den(1) {
        Normalize();
}

Rational::Rational(int _num, int _den)
    : num(_num)
    , den(_den) {
        if (den == 0) {
            throw std::invalid_argument("The denominator cannot be equal to zero!");
        }
        Normalize();
}

Rational::Rational(const Rational& other)
    : num(other.num)
    , den(other.den)
{}

Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.num;
    den = rhs.den;
    return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
    int a = std::lcm(den, rhs.den);
    num *= a / den;
    num += rhs.num * (a / rhs.den);
    den = a;
    Normalize();
    return *this;
}

Rational Rational::operator+(const Rational& rhs) const {
    return Rational(*this) += rhs;
}

Rational& Rational::operator-=(const Rational& rhs) {
    int a = std::lcm(den, rhs.den);
    num *= a / den;
    num -= rhs.num * (a / rhs.den);
    den = a;
    Normalize();
    return *this;
}

Rational Rational::operator-(const Rational& rhs) const {
    return Rational(*this) -= rhs;
}

Rational& Rational::operator*=(const Rational& rhs) {
    num *= rhs.num;
    den *= rhs.den;
    Normalize();
    return *this;
}

Rational Rational::operator*(const Rational& rhs) const {
    return Rational(*this) *= rhs;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs == Rational(0)) {
        throw std::domain_error("Division by zero!");
    }
    den *= rhs.num;
    num *= rhs.den;
    Normalize();
    return *this;
}

Rational Rational::operator/(const Rational& rhs) const {
    return Rational(*this) /= rhs;
}

Rational Rational::operator-() const {
    Rational a(*this);
    a.num *= -1;
    return a;
}

Rational Rational::operator+() const {
    return Rational(*this);
}

Rational& Rational::operator++() {
    return *this += Rational(1, 1);
}

Rational Rational::operator++(int a) {
    Rational r(*this);
    *this += Rational(1, 1);
    return r;
}

Rational& Rational::operator--() {
    return *this -= Rational(1, 1);
}

Rational Rational::operator--(int a) {
    Rational r(*this);
    *this -= Rational(1, 1);
    return r;
}

bool Rational::operator==(const Rational& rhs) const {
    return (num == rhs.num) && (den == rhs.den);
}

bool Rational::operator!=(const Rational& rhs) const {
    return !(*this == rhs);
}

bool Rational::operator>(const Rational& rhs) const {
    return (num * rhs.den) > (rhs.num * den);
}

bool Rational::operator>=(const Rational& rhs) const {
    return !(*this < rhs);
}

bool Rational::operator<(const Rational& rhs) const {
    return (num * rhs.den) < (rhs.num * den);
}

bool Rational::operator<=(const Rational& rhs) const {
    return !(*this > rhs);
}

int Rational::GetNumerator() const {
    return num;
}

int Rational::GetDenominator() const {
    return den;
}

void Rational::Normalize() {
    if (den < 0) {
        den *= -1;
        num *= -1;
    }
    int mult = std::gcd(num, den);
    num /= mult;
    den /= mult;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.GetNumerator() << "/" << r.GetDenominator();
}
