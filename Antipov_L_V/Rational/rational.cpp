#include "rational.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>

using namespace std;


// Greatest Common Divisor
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

// Least Common Multiple
int lcm(int a, int b) {
    return abs(a * b) / gcd(a, b);
}

// Constructors
Rational::Rational(int num) {
    this->num = num;
    den = 1;
}

Rational::Rational(int num, int den) {
    this->num = num;
    this->den = den;
    if (den == 0) {
        throw std::invalid_argument("Denominator can't be a zero.");
    }

    // Normalize
    Normal();
}

Rational::Rational(const Rational &copy) {
    num = copy.GetNum();
    den = copy.GetDen();
}

Rational& Rational::operator=(const Rational &rhs) {
    num = rhs.GetNum();
    den = rhs.GetDen();
    return *this;
}

Rational Rational::operator+(const Rational &rhs) const {
    return Rational(*this) += rhs;
}

Rational Rational::operator-(const Rational &rhs) const {
    return Rational(*this) -= rhs;
}

Rational& Rational::operator+=(const Rational &rhs) {
    int common = lcm(GetDen(), rhs.GetDen());
    num = GetNum() * (common / GetDen()) + rhs.GetNum() * (common / rhs.GetDen());
    den = common;
    Normal();
    return *this;
}

Rational& Rational::operator-=(const Rational &rhs) {
    int common = lcm(GetDen(), rhs.GetDen());
    num = GetNum() * (common / GetDen()) - rhs.GetNum() * (common / rhs.GetDen());
    den = common;
    Normal();
    return *this;
}

Rational& Rational::operator*=(const Rational &rhs) {
    num *= rhs.GetNum();
    den *= rhs.GetDen();
    Normal();
    return *this;
}

Rational& Rational::operator/=(const Rational &rhs) {
    if (rhs == Rational(0)) {
        throw domain_error("Can't divide by zero.");
    }
    num *= rhs.GetDen();
    den *= rhs.GetNum();
    Normal();
    return *this;
}

Rational Rational::operator/(const Rational &rhs) const {
    return Rational(*this) /= rhs;
}

Rational Rational::operator*(const Rational &rhs) const {
    return Rational(*this) *= rhs;
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

Rational Rational::operator++(int) {
    Rational temp(*this);
    ++*this;
    return temp;
}

Rational& Rational::operator--() {
    return *this -= Rational(1, 1);
}

Rational Rational::operator--(int) {
    Rational temp(*this);
    --*this;
    return temp;
}

bool Rational::operator<(const Rational &rhs) const {
    return !(*this > rhs);
}

bool Rational::operator<=(const Rational &rhs) const {
    return !(*this > rhs);
}

bool Rational::operator>(const Rational &rhs) const {
    return GetNum() * rhs.GetDen() > rhs.GetNum() * GetDen();
}

bool Rational::operator>=(const Rational &rhs) const {
    return !(*this < rhs);
}

bool Rational::operator==(const Rational &rhs) const {
    return GetNum() * rhs.GetDen() == rhs.GetNum() * GetDen();
}

bool Rational::operator!=(const Rational &rhs) const {
    return !(*this == rhs);
}


void Rational::Normal() {
    if (GetDen() < 0 && GetNum() >= 0) {
        den = -den;
        num = -num;
    }
    int g = gcd(GetNum(), GetDen());
    num /= g;
    den /= g;
}

std::ostream& operator<<(std::ostream &os, const Rational &rhs) {
    return (rhs.GetNum() % rhs.GetDen() != 0)
           ? (os << rhs.GetNum() << "/" << rhs.GetDen())
           : os << rhs.GetNum() / rhs.GetDen();
}

// Getters
int Rational::GetDen() const {
    return den;
}


int Rational::GetNum() const {
    return num;
}