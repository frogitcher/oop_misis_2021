#include "rational.h"
#include <stdexcept>
#include <algorithm>
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
	return abs(a * b) / gcd(a, b);
}

Rational::Rational(int _num) {
	num = _num;
	den = 1;
}
Rational::Rational(int _num, int _den) {
	num = _num;
	den = _den;
	if (den == 0) {
		throw std::invalid_argument("Den can't be 0");
	}
	Rational::Normal();
}
Rational::Rational(const Rational& other) {
	num = other.GetNum();
	den = other.GetDen();
	Rational::Normal();
}

//Definition of arithmetic operations
Rational Rational::operator+(const Rational& rhs) const
{
	return Rational(*this) += rhs;
}
Rational& Rational::operator=(const Rational& rhs)
{
	num = rhs.GetNum();
	den = rhs.GetDen();
	return *this;
}
Rational Rational::operator-(const Rational& rhs) const
{
	return Rational(*this) -= rhs;
}
Rational& Rational::operator+=(const Rational& rhs) {
	int common = lcm(GetDen(), rhs.GetDen());
	num = GetNum() * (common / GetDen()) + rhs.GetNum() * (common / rhs.GetDen());
	den = common;
	Rational::Normal();
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
	int common = lcm(GetDen(), rhs.GetDen());
	num = GetNum() * (common / GetDen()) - rhs.GetNum() * (common / rhs.GetDen());
	den = common;
	Rational::Normal();
	return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
	num *= rhs.GetNum();
	den *= rhs.GetDen();
	Normal();
	return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs == Rational(0)) {
		throw std::domain_error("Division by 0!!!");
	}
	num *= rhs.GetDen();
	den *= rhs.GetNum();
	Normal();
	return *this;
}
Rational Rational::operator/(const Rational& rhs) const {
	return Rational(*this) /= rhs;
}
Rational Rational::operator*(const Rational& rhs) const {
	return Rational(*this) *= rhs;
}
int Rational::GetDen() const {
	return den;
}

int Rational::GetNum() const {
	return num;
}

//Definition of boolean functions
bool Rational::operator<(const Rational& rhs) const {
	return GetNum() * rhs.GetDen() < rhs.GetNum() * GetDen();
}
bool Rational::operator<=(const Rational& rhs) const {
	return GetNum() * rhs.GetDen() <= rhs.GetNum() * GetDen();
}
bool Rational::operator>(const Rational& rhs) const {
	return GetNum() * rhs.GetDen() > rhs.GetNum() * GetDen();
}
bool Rational::operator>=(const Rational& rhs) const {
	return GetNum() * rhs.GetDen() >= rhs.GetNum() * GetDen();
}
bool Rational::operator==(const Rational& rhs) const {
	return GetNum() * rhs.GetDen() == rhs.GetNum() * GetDen();
}
bool Rational::operator!=(const Rational& rhs) const {
	return GetNum() * rhs.GetDen() != rhs.GetNum() * GetDen();
}

//Definition of unarian operators
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

//Definition of normalization
void Rational::Normal() {
	if (GetDen() < 0 && GetNum() >= 0) {
		den = -den;
		num = -num;
	}
	int g = gcd(abs(GetNum()), GetDen());
	num /= g;
	den /= g;

}

//Definition of output operator
std::ostream& operator<<(std::ostream& os, const Rational& r) {
	return os << r.GetNum() << "/" << r.GetDen();
}
