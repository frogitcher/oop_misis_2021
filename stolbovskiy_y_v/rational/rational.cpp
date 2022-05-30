#include "rational.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

int gcd(int a, int b) {
	if (!a) return b;
	while (a != b) {
		if (a > b) a -= b;
		else b -= a;
	}
	return a;
}

int lcm(int a, int b) {
	return a * b / gcd(a, b);
}

rational::rational(int _num)
	: num(_num)
	, den(1)
{}

rational::rational(int _num, int _den)
	: num(_num)
	, den(_den) {
	if (_den == 0) {
		throw std::domain_error("denominator must not be equal to 0");
	}
	normalize();
}

rational::rational(const rational& other) {
	num = other.num;
	den = other.den;
}

rational& rational::operator=(const rational& rhs)
{
	num = rhs.num;
	den = rhs.den;
	return *this;
}

rational& rational::operator+=(const rational& rhs) {
	int temp = lcm(den, rhs.den);
	num = num * temp / den + rhs.num * temp / rhs.den;
	den = temp;
	normalize();
	return *this;
}

rational& rational::operator-=(const rational& rhs) {
	int temp = lcm(den, rhs.den);
	num = num * temp / den - rhs.num * temp / rhs.den;
	den = temp;
	normalize();
	return *this;
}

rational& rational::operator*=(const rational& rhs) {
	num *= rhs.num;
	den *= rhs.den;
	normalize();
	return *this;
}

rational& rational::operator/=(const rational& rhs) {
	if (rhs.num == 0) {
		throw std::domain_error("cannot divide by 0");
	}
	num *= rhs.den;
	den *= rhs.num;
	normalize();
	return *this;
}

rational rational::operator+(const rational& rhs) const {
	return rational(*this) += rhs;
}

rational rational::operator-(const rational& rhs) const {
	return rational(*this) -= rhs;
}

rational rational::operator*(const rational& rhs) const {
	return rational(*this) *= rhs;
}

rational rational::operator/(const rational& rhs) const {
	return rational(*this) /= rhs;
}

rational rational::operator-() const {
	return rational(-num, den);
}

rational rational::operator+() const{
	return *this;
}

bool rational::operator<=(const rational& rhs) const {
	return num * rhs.den <= den* rhs.num;
}

bool rational::operator>(const rational& rhs) const {
	return !(*this<=rhs);
}

bool rational::operator>=(const rational& rhs) const {
	return num * rhs.den >= den* rhs.num;
}

bool rational::operator<(const rational& rhs) const {
	return !(*this >= rhs);
}

bool rational::operator==(const rational& rhs) const {
	return num * rhs.den == den* rhs.num;
}

bool rational::operator!=(const rational& rhs) const {
	return num * rhs.den != den* rhs.num;
}

int rational::getnum() const {
	return num;
}

int rational::getden() const {
	return den;
}

void rational::setnum(const int& _num)
{
	num = _num;
}

void rational::setden(const int& _den)
{
	if (_den== 0) {
		throw std::domain_error("denominator must not be equal to 0");
	}
	den = _den;
	normalize();
}

void rational::normalize() {
	if (den < 0) {
		num = -num;
		den = -den;
	}
	int g = gcd(std::abs(num), den);
	num /= g;
	den /= g;
}
