#include "rational.h"
#include <stdexcept>
#include <algorithm>

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

Rational::Rational(int _num)
	: num(_num)
	, den(1)
{}
Rational::Rational(int _num, int _den)
	: num(_num)
	, den(_den){
	if (den == 0)
	{
		throw std::invalid_argument("denominator must not be equal to zero");
	}
    Rational::Normalize();
}
Rational::Rational(const Rational& other)
{
    num = other.GetNumerator();
    den = other.GetDenominator();
    Rational::Normalize();
}

Rational& Rational::operator=(const Rational& rhs)
{
    num = rhs.GetNumerator();
    den = rhs.GetDenominator();
    return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
	int common = lcm(GetDenominator(), rhs.GetDenominator());
	num = GetNumerator() * (common / GetDenominator()) + rhs.GetNumerator() * (common / rhs.GetDenominator());
    den = common;
	Rational::Normalize();
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
    int common = lcm(GetDenominator(), rhs.GetDenominator());
    num = GetNumerator() * (common / GetDenominator()) - rhs.GetNumerator() * (common / rhs.GetDenominator());
    den = common;
    Rational::Normalize();
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
    num *= rhs.GetNumerator();
    den *= rhs.GetDenominator();
    Rational::Normalize();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs == Rational(0))
    {
        throw std::invalid_argument("You can't divide by zero");
    }
    num *= rhs.GetDenominator();
    den *= rhs.GetNumerator();
    Rational::Normalize();
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

bool Rational::operator<(const Rational& rhs) const {
	return num * rhs.den < rhs.num * den;
}
bool Rational::operator>(const Rational& rhs) const {
    return num * rhs.den > rhs.num * den;
}
bool Rational::operator<=(const Rational& rhs) const {
    return num * rhs.den <= rhs.num * den;
}
bool Rational::operator>=(const Rational& rhs) const {
    return num * rhs.den >= rhs.num * den;
}

bool Rational::operator==(const Rational& rhs) const {
    return num * rhs.den == rhs.num * den;
}
bool Rational::operator!=(const Rational& rhs) const {
    return num * rhs.den != rhs.num * den;
}

int Rational::GetNumerator() const { return  num; }
int Rational::GetDenominator() const { return  den; }

void Rational::Normalize() {
	int g = gcd(abs(num), den);
	num /= g;
	den /= g;
}