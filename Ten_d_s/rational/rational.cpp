#include "rational.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>

Rational::Rational(int numm)
	: num(numm)
	, den(1)
{}

Rational::Rational(const Rational& rhs){
    num = rhs.num;
    den = rhs.den;
}

Rational::Rational(int numm, int denn)
	: num(numm)
	, den(denn) {
	  if (den == 0) {
		  throw std::invalid_argument("demonitation must not be equal to 0");
		}
    Normalize();
}

int gcd(int a, int b) {
	a = std::abs(a);
	b = std::abs(b);
	if (a == 0) {
		return b;
	}
	return gcd(b % a, a);
}

int lcm(int a, int b) {
	a = std::abs(a);
	b = std::abs(b);
	return a * b / gcd(a, b);
}

Rational& Rational::operator+=(const Rational& rhs) {
	int n = lcm(GetDenominator(), rhs.GetDenominator());
	num *= n / den;
	num += rhs.num * (n / rhs.den);
	den = n;
	Normalize();
	return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
	int n = lcm(GetDenominator(), rhs.GetDenominator());
	num *= n / den;
	num -= rhs.num * (n / rhs.den);
	den = n;
	Normalize();
	return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
	num = num * rhs.num;
	den = den * rhs.den;
	Normalize();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs == Rational(0)) {
		throw std::domain_error("Division by 0!");
	}
	num *= rhs.den;
	den *= rhs.num;
	Normalize();
	return *this;
}

Rational& Rational::operator=(const Rational& rhs) {
	if (rhs == Rational(0)) {
		throw std::domain_error("Division by 0!");
	}
	num = rhs.num;
	den = rhs.den;
	return *this;
}

Rational Rational::operator-(const Rational& rhs) const {
	return Rational(*this) -= rhs;
}

Rational Rational::operator+(const Rational& rhs) const {
	return Rational(*this) += rhs;
}

Rational Rational::operator*(const Rational& rhs) const {
	return Rational(*this) *= rhs;
}

Rational Rational::operator/(const Rational& rhs) const {
	return Rational(*this) /= rhs;
}

bool Rational::operator<(const Rational& rhs) const{
	return num * rhs.den < rhs.num* den;
}

bool Rational::operator>(const Rational& rhs) const{
	return num * rhs.den > rhs.num* den;
}

bool Rational::operator<=(const Rational& rhs) const{
	return num * rhs.den <= rhs.num* den;
}

bool Rational::operator>=(const Rational& rhs) const{
	return num * rhs.den >= rhs.num * den;
}

bool Rational::operator==(const Rational& rhs) const{
	return ((num == rhs.num) && (den == rhs.den));
}

bool Rational::operator!=(const Rational& rhs) const{
	return !((num == rhs.num) && (den == rhs.den));
}

void Rational::Normalize() {
    if (den < 0){
        den *= -1;
        num *= -1;
    }
	int g = gcd(abs(num), den);
	num /= g;
	den /= g;
}

int Rational::GetNumerator() const {
	return num;
}

int Rational::GetDenominator() const {
	return den;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.GetNumerator() << "/" << r.GetDenominator();
}
