#include "rational.h"
#include <iostream>
#include <numeric>

int gcd(int a, int b) {
	a = std::abs(a);
	b = std::abs(b);
	if (a == 0) {
		return b;
	}
	return gcd(b % a, a);
}

Rational::Rational(int _num) {
	num = _num;
	den = 1;
}

Rational::Rational(const int _num, const int _den) {
	num = _num;
	den = _den;
	if (den == 0) {
		throw std::invalid_argument("exception - denominator must be more then 0");
	}
	Normalize();
}

Rational::Rational(const Rational& other) {
	num = other.num;
	den = other.den;
}


Rational& Rational::Normalize() {
	if (den < 0)
	{
		num *= -1;
		den *= -1;
	}
		int _gcd = gcd(abs(num), den);
		num /= _gcd;
		den /= _gcd;
	return *this;
}

bool Rational::operator==(const Rational& rhs) const {
	return (num == rhs.num && den == rhs.den);
}

Rational& Rational::operator-=(const Rational& rhs) {
	num = num * rhs.den - abs(rhs.num) * den;
	den = den * rhs.den;
	Normalize();
	return *this;
}

Rational Rational::operator*(const Rational& rhs) const {
	return Rational(*this) *= rhs;
}

Rational Rational::operator/(const Rational& rhs) const {
	return Rational(*this) /= rhs;
}

Rational& Rational::operator++() {
	return *this += Rational(1);
}

Rational& Rational::operator--() {
	return *this -= Rational(1);
}

Rational Rational::operator++(int a) {
	Rational current = *this;
	*this += Rational(1,1);
	return current;
}

Rational Rational::operator--(int a) {
	Rational current = *this;
	*this -= Rational(1);
	return current;
}

Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs.num == 0)
	{
		throw std::invalid_argument("exception - denominator must be more then 0");
	}
	num *= rhs.den;
	den *= rhs.num;
	if (den < 0) {
		num *= -1;
		den *= -1;
	}
	Normalize();
	return *this;
}

Rational Rational::operator+(const Rational& rhs) const {
	return Rational(*this)+=rhs;
}

Rational Rational::operator-(const Rational& rhs) const {
	return Rational(*this) -= rhs;
}

Rational& Rational::operator+=(const Rational& rhs)
{
	num = num * rhs.den + rhs.num * den;
	den = den * rhs.den;
	Normalize();
	return *this; 
}

Rational& Rational::operator*=(const Rational& rhs) {
	num *= rhs.num;
	den *= rhs.den;
	Normalize();
	return *this;
}

bool Rational::operator!=(const Rational& rhs)const
{
	return (num != rhs.num || den != rhs.den);
}

bool Rational::operator>(const Rational& rhs) const {
	return (num * rhs.den > rhs.num * den);
}

bool Rational::operator<(const Rational& rhs) const {
	return (num * rhs.den < rhs.num* den);
}

bool Rational::operator>=(const Rational& rhs) const {
	return (num * rhs.den >= rhs.num * den);
}

bool Rational::operator<=(const Rational& rhs) const {
	return (num * rhs.den <= rhs.num* den);
}