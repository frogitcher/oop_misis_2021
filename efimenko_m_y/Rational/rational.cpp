#include "rational.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <numeric>

Rational::Rational(const int _num, const int _den) 
	: num(_num)
	, den(_den){
	if (den == 0) {
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	Normalize();
}
Rational::Rational(const int _num)
	: num(_num)
	, den(1) {
	Normalize();
}
Rational::Rational(const Rational& other)
	:num(other.num)
	, den(other.den)
{}

Rational Rational::operator+(const Rational& rhs) const {
	return Rational (num * rhs.den + rhs.num * den, den * rhs.den);
}
Rational Rational:: operator-(const Rational& rhs) const {
	return Rational (num * rhs.den - rhs.num * den, den * rhs.den);

}
Rational Rational:: operator*(const Rational& rhs) const {
	return Rational{ num * rhs.num, den * rhs.den };
}
Rational Rational:: operator/(const Rational& rhs) const {
	if (rhs == Rational(0)) {
		throw std::domain_error("Division by zero");
	}
	return Rational{ num * rhs.den, den * rhs.num };
}


Rational& Rational:: operator =(const Rational& rhs) {
	num = rhs.num;
	den = rhs.den;
	return *this;
}

Rational& Rational:: operator+=(const Rational& rhs) {
	*this = *this + rhs;
	return* this;
}
Rational& Rational::operator-=(const Rational& rhs) {
	*this = *this - rhs;
	return *this;
}
Rational& Rational::operator *=(const Rational& rhs) {
	*this = *this * rhs;
	Normalize();
	return *this;
}
Rational& Rational::operator /=(const Rational& rhs) {
	*this = *this / rhs;
	return *this;
}

Rational& Rational:: operator++() {
	*this = *this + 1;
	Normalize();
	return *this;
}
Rational Rational:: operator++(int) {
	Rational before = *this;
	*this = *this + 1;
	return before;
}
Rational& Rational:: operator--() {
	*this = *this - 1;
	Normalize();
	return *this;
}
Rational Rational:: operator--(int) {
	Rational before = *this;
	*this = *this - 1;
	return before;
}

Rational Rational:: operator +() const {
	return *this;
}
Rational Rational::operator -() const {
	return Rational(-num ,den);
}


bool Rational:: operator> (const Rational& rhs) const { return num * rhs.den > den * rhs.num; }
bool Rational:: operator<= (const Rational& rhs) const { return !(*this> rhs); }
bool Rational:: operator<(const Rational& rhs) const { return num * rhs.den < den * rhs.num; }
bool Rational:: operator>= (const Rational& rhs) const { return !(*this < rhs); }
bool Rational::operator==(const Rational& rhs) const {return num == rhs.num && den == rhs.den;}
bool Rational::operator != (const Rational& rhs) const { return !(*this == rhs); };

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int Rational::getdenominator() {
	return den;
}
int Rational::getnumerator() {
	return num;
}
void Rational::Normalize() {
	int g = gcd(abs(num), den);
	num /= g;
	den /= g;
}
std::ostream& operator<<(std::ostream& out, const Rational& value) {
	return out << value.num << '/' << value.den;
}

std::istream& operator>>(std::istream& in, Rational& value) {
	char slash(0);
	in >> value.num >>slash>> value.den;
	if (slash == '/') {
		if (value.den == 0) {
			throw std::invalid_argument("Denominator must not be equal to zero");
		}
		if (value.den < 0) {
			throw std::invalid_argument("Denominator must be a natural number");
		}
		value.Normalize();
	}
	else { throw std::invalid_argument("Wrong slash used"); }
	return in;
}


