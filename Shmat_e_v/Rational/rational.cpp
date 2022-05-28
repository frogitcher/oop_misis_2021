#include "rational.h"

#include <numeric>
#include <stdexcept>

Rational::Rational(int _numerator) : numerator(_numerator), denominator(1) {}

Rational::Rational(int _numerator, int _denominator) : numerator(_numerator), denominator(_denominator) {
    if (_denominator == 0) {
        throw std::invalid_argument("Denominator must not be 0");
    }
    Normalize();
}

Rational::Rational(const Rational &rhs) : numerator(rhs.numerator), denominator(rhs.denominator) {}

Rational &Rational::operator=(const Rational &rhs) {
    numerator = rhs.numerator;
    denominator = rhs.denominator;

    return *this;
}

Rational Rational::operator+(const Rational &rhs) const {
    return Rational(*this) += rhs;
}

Rational Rational::operator-(const Rational &rhs) const {
    return Rational(*this) -= rhs;
}

Rational Rational::operator*(const Rational &rhs) const {
    return Rational(*this) *= rhs;
}

Rational Rational::operator/(const Rational &rhs) const {
    return Rational(*this) /= rhs;
}

Rational &Rational::operator+=(const Rational &rhs) {
    int lcm = std::lcm(denominator, rhs.denominator);
    numerator = numerator * lcm / denominator + rhs.numerator * lcm / rhs.denominator;
    denominator = lcm;
    Normalize();

    return *this;
}

Rational &Rational::operator-=(const Rational &rhs) {
    int lcm = std::lcm(denominator, rhs.denominator);
    numerator = numerator * lcm / denominator - rhs.numerator * lcm / rhs.denominator;
    denominator = lcm;
    Normalize();

    return *this;
}

Rational &Rational::operator*=(const Rational &rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    Normalize();

    return *this;
}

Rational &Rational::operator/=(const Rational &rhs) {
    if (rhs.numerator != 0) {
        numerator *= rhs.denominator;
        denominator *= rhs.numerator;
        Normalize();
    } else {
        throw std::invalid_argument("Division by 0");
    }

    return *this;
}

Rational Rational::operator+() const {
    return *this;
}

Rational Rational::operator-() const {
    return Rational(-numerator, denominator);
}

bool Rational::operator==(const Rational &rhs) const {
    return (numerator * rhs.denominator == rhs.numerator * denominator);
}

bool Rational::operator!=(const Rational &rhs) const {
    return !(*this == rhs);
}

bool Rational::operator<(const Rational &rhs) const {
    return (numerator * rhs.denominator < denominator * rhs.numerator);
}

bool Rational::operator>(const Rational &rhs) const {
    return (numerator * rhs.denominator > rhs.numerator * denominator);
}

bool Rational::operator<=(const Rational &rhs) const {
    return (numerator * rhs.denominator <= rhs.numerator * denominator);
}

bool Rational::operator>=(const Rational &rhs) const {
    return (numerator * rhs.denominator >= rhs.numerator * denominator);
}

int Rational::getNum() const {
    return numerator;
}

int Rational::getDen() const {
    return denominator;
}

void Rational::Normalize() {
    if (denominator < 0) {
        denominator *= -1;
        numerator *= -1;
    }
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

std::ostream &operator<<(std::ostream &os, const Rational &r) {
    return os << r.getNum() << "/" << r.getDen();
}
