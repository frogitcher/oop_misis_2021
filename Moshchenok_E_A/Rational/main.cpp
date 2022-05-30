#include "rational.h"
#include <iostream>


int gcd(int a, int b) {
	while (b > 0) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

int lcm (int a, int b) {
	return a / gcd(a, b) * b;
}

void Rational::normalize() {
    if (den == 0) {
        throw std::invalid_argument("Denominator must not be equal to 0");
    }
	if (num == 0) {
		den = 1;
		return;
	}
	if (den < 0){ 
		num *= -1;
		den *= -1;
	}
	int x = gcd(std::abs(num), den);
	num /= x;
	den /= x;
	return;
}

Rational::Rational(int _num) {
    num = _num;
    den = 1;
}

Rational::Rational(int _num, int _den) {
    num = _num;
    den = _den;
    normalize();
}

Rational::Rational(const Rational &other) {
    num = other.num;
    den = other.den;
}


Rational& Rational::operator=(const Rational &rhs) {
    num = rhs.num;
    den = rhs.den;
    return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
    int x = lcm(den, rhs.den);
    num = num * (x / den) + rhs.num * (x / rhs.den);
    den = x;
    this->normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    int x = lcm(den, rhs.den);
    num = num * (x / den) - rhs.num * (x / rhs.den);
    den = x;
    this->normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational &rhs) {
    num *= rhs.num;
    den *= rhs.den;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational &rhs){
    num *= rhs.den;
    den *= rhs.num;
    normalize();
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
    return Rational(-num, den);
}

bool Rational::operator<(const Rational& rhs) const {
    return (num * rhs.den < rhs.num * den);
}

bool Rational::operator==(const Rational& rhs) const {
    return (num == rhs.num && den == rhs.den);
}

bool Rational::operator>(const Rational& rhs) const {
	return !(*this < rhs || *this == rhs);
}

bool Rational::operator<=(const Rational& rhs) const {
    return !(*this > rhs);
}

bool Rational::operator>=(const Rational& rhs) const {
    return !(*this < rhs);
}

bool Rational::operator!=(const Rational& rhs) const {
    return !(*this == rhs);
}

Rational& Rational::operator++() {
    *this += Rational(1);
    return *this;
}

Rational& Rational::operator--() {
    *this -= Rational(1);
    return *this;
}

Rational Rational::operator++(int) {
    Rational x(*this);
    *this += Rational(1);
    return x;
}

Rational Rational::operator--(int) {
    Rational x(*this);
    *this -= Rational(1);
    return x;
}

int Rational::get_numerator() const {
    return num;
}

int Rational::get_denominator() const {
    return den;
}