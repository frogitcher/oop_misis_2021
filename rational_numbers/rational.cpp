#include "rational.h"
#include <stdexcept>
#include <cmath>

int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

int lcm(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    return a*b/gcd(a, b);
}

Rational::Rational(int _num)
    : num(_num)
    , den(1) {
        Normalize();
}

Rational::Rational(int _num, int _den)
    : num(_num)
    , den(_den) {
        if (den == 0) {
            throw std::invalid_argument("Denominator must not be equal to 0!");
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
    int l = lcm(den, rhs.den);
    num *= l / den;
    num += rhs.num * (l / rhs.den);
    den = l;
    Normalize();
    return *this;
}

Rational Rational::operator+(const Rational& rhs) const {
    return Rational(*this) += rhs;
}

Rational& Rational::operator-=(const Rational& rhs) {
    int l = lcm(den, rhs.den);
    num *= l / den;
    num -= rhs.num * (l / rhs.den);
    den = l;
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
        throw std::domain_error("Division by 0!");
    }
    num *= rhs.den;
    den *= rhs.num;
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

const Rational Rational::operator++(int a) {
    Rational r(*this);
    *this += Rational(1, 1);
    return r;
}

Rational& Rational::operator--() {
    return *this -= Rational(1, 1);
}

const Rational Rational::operator--(int a) {
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

bool Rational::operator<(const Rational& rhs) const {
    return (num * rhs.den) < (rhs.num * den);
}

bool Rational::operator>(const Rational& rhs) const {
    return (num * rhs.den) > (rhs.num * den);
}

bool Rational::operator<=(const Rational& rhs) const {
    return !(*this > rhs);
}

bool Rational::operator>=(const Rational& rhs) const {
    return !(*this < rhs);
}

int Rational::GetNumerator() const {
    return num;
}

int Rational::GetDenominator() const {
    return den;
}

void Rational::Normalize() {
    if (den < 0) {
        num *= -1;
        den *= -1;
    }
    int g = gcd(num, den);
    num /= g;
    den /= g;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.GetNumerator() << "/" << r.GetDenominator();
}
