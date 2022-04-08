#include "rational.h"
#include <stdexcept>
#include <iostream>
#include <numeric>


Rational::Rational(int _num, int _den):num(_num), den(_den)
{
    if (_den == 0) {
        throw std::invalid_argument("invalid denominator(den == 0)");
    }
    this->Normalize();
}

Rational::Rational(const Rational& other) = default;

Rational& Rational::operator=(const Rational& rhs) = default;

Rational& Rational::operator-=(const Rational& rhs) {
    return *this += -rhs;
}

Rational& Rational::operator+=(const Rational& rhs) {
    int common = std::lcm(den, rhs.den);
    num = num * (common / den) + rhs.num * (common / rhs.den);
    den = common;
    this->Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    *this={num*rhs.num, den*rhs.den};
    this->Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num == 0) {
        throw std::invalid_argument("Invalid divisor(divisor == 0)");
    }
    *this={num*rhs.den, den*rhs.num};
    this->Normalize();
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

Rational Rational::operator-() const {
    return {-num, den};
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
/* in c++20 without it, we can just write only one operator <=>
 */

bool Rational::operator==(const Rational& rhs) const {
    return (num * rhs.den == rhs.num* den);
}

bool Rational::operator!=(const Rational& rhs) const {
    return !((*this)==rhs);
}


Rational& Rational::operator++() {
    return *this += Rational(1);
}

Rational Rational::operator++(int a) {
    Rational b(*this);
    ++*this;
    return b;
}

Rational& Rational::operator--() {
    return *this -= Rational(1);
}

Rational Rational::operator--(int a) {
    Rational b(*this);
    --*this;
    return b;
}

int Rational::getnumerator() const {
    return num;
}

int Rational::getdenumerator() const {
    return den;
}

void Rational::Normalize() {
    if (num == 0) {
        den=1;
        return;
    }
    int g = std::gcd(abs(num), den);
    num/=g;
    den/=g;
    if (den < 0) {
        num*=-1;
        den*=-1
    };
}
