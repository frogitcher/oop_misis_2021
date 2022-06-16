#include "rational.h"
#include <stdexcept>
#include <numeric>
#include <iostream>

Rational::Rational(int _num, int _den) {
	if (_den == 0) throw std::invalid_argument("Denominator != 0");
	num = _num;
	den = _den;
	this->Normalize();
}

Rational& Rational::operator+=(const Rational& rhs) {
	num = num * rhs.den + rhs.num * den;
	den *= rhs.den;
	this->Normalize();
	return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
	return *this += -rhs;
}

Rational& Rational::operator*=(const Rational& rhs) {
	num *= rhs.num;
	den *= rhs.den;
	this->Normalize();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs.num == 0) throw std::invalid_argument("Division by 0");
	num *= rhs.den;
	den *= rhs.num;
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
	return Rational(num * -1, den);
}

Rational& Rational::operator++() {
	return *this += Rational(1);
}

Rational Rational::operator++(int a) {
	*this += Rational(1);
	return *this - Rational(1);
}

Rational& Rational::operator--() {
	return *this -= Rational(1);
}

Rational Rational::operator--(int a) {
	*this -= Rational(1);
	return *this + Rational(1);
}

bool Rational::operator<(const Rational& rhs) const {return (num * rhs.den < rhs.num * den);}
bool Rational::operator<=(const Rational& rhs) const {return !(*this > rhs);}
bool Rational::operator>(const Rational& rhs) const {return (num * rhs.den > rhs.num* den);}
bool Rational::operator>=(const Rational& rhs) const {return !(*this < rhs);}
bool Rational::operator==(const Rational& rhs) const {return (num * rhs.den == rhs.num * den);}
bool Rational::operator!=(const Rational& rhs) const {return (num * rhs.den != rhs.num * den);}

int Rational::get_numerator() const { return num; }
int Rational::get_denumerator() const { return den; }

void Rational::Normalize() {
	if (num == 0) {
		den = 1;
		return;
	}
	int g = std::gcd(abs(num), den);
	num /= g;
	den /= g;
	if (den < 0) {
		num *= -1;
		den *= -1;
	}
}
