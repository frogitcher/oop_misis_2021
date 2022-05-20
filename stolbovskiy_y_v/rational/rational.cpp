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

rational::rational(const rational& r) {
	this->setnum(r.getnum());
	this->setden(r.getden());
}

rational& rational::operator=(const rational& rhs)
{
	rational& lhs = *this;
	lhs.setnum(rhs.getnum());
	lhs.setden(rhs.getden());
	return *this;
}

rational& rational::operator+=(const rational& rhs) {
	rational& lhs = *this;
	int tem = lcm(lhs.getden(), rhs.getden());
	lhs.setnum(lhs.getnum()*tem/lhs.getden() + rhs.getnum()*tem/rhs.getden());
	lhs.setden(tem);
	lhs.normalize();
	return *this;
}

rational& rational::operator-=(const rational& rhs) {
	rational& lhs = *this;
	int tem = lcm(lhs.getden(), rhs.getden());
	lhs.setnum(lhs.getnum() * tem / lhs.getden() - rhs.getnum() * tem / rhs.getden());
	lhs.setden(tem);
	lhs.normalize();
	return *this;
}

rational& rational::operator*=(const rational& rhs) {
	rational& lhs = *this;
	lhs.setnum(lhs.getnum() * rhs.getnum());
	lhs.setden(lhs.getden() * rhs.getden());
	lhs.normalize();
	return *this;
}

rational& rational::operator/=(const rational& rhs) {
	if (rhs.getnum() == 0) {
		throw std::domain_error("cannot divide by 0");
	}
	rational& lhs = *this;
	lhs.setnum(lhs.getnum() * rhs.getden());
	lhs.setden(lhs.getden() * rhs.getnum());
	lhs.normalize();
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
	const rational r = *this;
	return rational(-r.getnum(), r.getden());
}

rational rational::operator+() const{
	return *this;
}

bool rational::operator<(const rational& rhs) const {
	const rational& lhs = *this;
	return lhs.getnum() * rhs.getden() < lhs.getden() * rhs.getnum();
}

bool rational::operator<=(const rational& rhs) const {
	const rational& lhs = *this;
	return lhs.getnum() * rhs.getden() <= lhs.getden() * rhs.getnum();
}

bool rational::operator>(const rational& rhs) const {
	const rational& lhs = *this;
	return lhs.getnum() * rhs.getden() > lhs.getden() * rhs.getnum();
}

bool rational::operator>=(const rational& rhs) const {
	const rational& lhs = *this;
	return lhs.getnum() * rhs.getden() >= lhs.getden() * rhs.getnum();
}

bool rational::operator==(const rational& rhs) const {
	const rational& lhs = *this;
	return lhs.getnum() * rhs.getden() == lhs.getden() * rhs.getnum();
}

bool rational::operator!=(const rational& rhs) const {
	const rational& lhs = *this;
	return lhs.getnum() * rhs.getden() != lhs.getden() * rhs.getnum();
}

int rational::getnum() const {
	return num;
}

int rational::getden() const {
	return den;
}

void rational::setnum(const int& _num)
{
	this->num = _num;
}

void rational::setden(const int& _den)
{
	this->den = _den;
}

void rational::normalize() {
	rational& r = *this;
	if (r.getden() < 0) {
		r.setnum(-r.getnum());
		r.setden(-r.getden());
	}
	int g = gcd(std::abs(num), den);
	r.setnum(r.getnum() / g);
	r.setden(r.getden() / g);
}