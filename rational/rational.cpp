#include "rational.h"
#include <stdexcept>
#include <algorithm>

int gcd(int a, int b) {
	a = std::abs(a);
	b = std::abs(b);
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}
int lcm(int a, int b) {
	return a / gcd(a, b) * b;
}

int Rational::getDen() const{
	return den;
}
int Rational::getNum() const{
	return num;
}

void Rational::setNum(int _num) {
	num = _num;
}
void Rational::setDen(int _den) {
	den = _den;
}

Rational::Rational(int _num)
	:num(_num)
	, den(1)
{
//	num = _num;
//	den = 1;
	normalize();
}
Rational::Rational(int _num, int _den) {
	if (_den < 0) {
		_den *= -1;
		_num *= -1;
	}
	if (den == 0) {
		throw std::invalid_argument("denominator mastnot be equal to 0");
	}
	else {
		num = _num;
		den = _den;
		normalize();
	}
}

Rational& Rational::operator=(const Rational& rhs) {
	num = rhs.num;
	den = rhs.den;
	return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
	int common = lcm(den, rhs.den);
	num *= common / den;
	num += (common / rhs.den) * rhs.num;
	den = common;
	normalize();
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
	int common = lcm(den, rhs.den);
	num *= common / den;
	num -= (common / rhs.den) * rhs.num;
	den = common;
	normalize();
	return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
	num *= rhs.num;
	den *= rhs.den;
	normalize();
	return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs.num == 0) {
		throw std::invalid_argument("division by 0");
	}
	else {
		num *= rhs.den;
		den *= rhs.num;
		normalize();
	}
	return *this;
}

Rational Rational::operator+(const Rational& rhs) const{
	Rational r(*this);
	return r += rhs;
}
Rational Rational::operator-(const Rational& rhs) const {
	Rational r(*this);
	return r -= rhs;
}
Rational Rational::operator*(const Rational& rhs) const {
	Rational r(*this);
	return r *= rhs;
}
Rational Rational::operator/(const Rational& rhs) const {
	Rational r(*this);
	return r /= rhs;
}

Rational Rational::operator+() const {
	Rational r(*this);
	return r;
}
Rational Rational::operator-() const {
	Rational r(*this);
	r.num *= -1;
	return r;
}

bool Rational::operator<(const Rational& rhs) const{
	return num * rhs.den < rhs.num * den;
}
bool Rational::operator>(const Rational& rhs) const {
	return num * rhs.den > rhs.num* den;
}

bool Rational::operator==(const Rational& rhs) const {
	return (num == rhs.num) && (rhs.den == den);
}
bool Rational::operator!=(const Rational& rhs) const {
	return (num != rhs.num) || (rhs.den != den);
}

bool Rational::operator<=(const Rational& rhs) const {
	return num * rhs.den <= rhs.num* den;
}
bool Rational::operator>=(const Rational& rhs) const {
	return num * rhs.den >= rhs.num* den;
}

Rational Rational::operator++() const{
	Rational rhs = Rational(1);
	return Rational(*this) += rhs;
}
Rational& Rational::operator++() {
	Rational a = (*this);
	Rational rhs = Rational(1);
	Rational(*this) += rhs;
	return a;
}
Rational Rational::operator--() const {
	Rational rhs = Rational(1);
	return Rational(*this) -= rhs;
}
Rational& Rational::operator--() {
	Rational a = (*this);
	Rational rhs = Rational(1);
	Rational(*this) -= rhs;
	return a;
}

void Rational::normalize() {
	int g = gcd(abs(num), den);
	num /= g;
	den /= g;
}

int main() {
	return 0;
}