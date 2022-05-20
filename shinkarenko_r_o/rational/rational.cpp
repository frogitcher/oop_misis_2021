#include <stdexcept>
#include "rational.h"
#include <cmath>

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else return gcd(b, a % b);
}


int lcm(int n, int m) 
{
	n = std::abs(n);
	m = std::abs(m);
	return n * m / gcd(n, m);
}

void Rational::Normalize()
{
	int t = gcd(std::abs(num), den);
	if (den < 0) {
		num *= -1;
		den *= -1;
	}
	num /= t;
	den /= t;
	
}

Rational::Rational(int _num)
	: num(_num)
	, den(1)
{}

Rational::Rational(int _num, int _den)
	: num(_num)
	, den(_den)
{
	if (_den == 0)
	{
		throw std::invalid_argument("Denominator must not be equal 0.");
	}
	Normalize();
}

Rational::Rational(const Rational& other)
	: num(other.num)
	, den(other.den)
{}

Rational& Rational::operator=(const Rational& rhs)
{
	num = rhs.num;
	den = rhs.den;
	return *this;
}

Rational& Rational::operator+=(const Rational& rhs)
{
	int lcm_1 = lcm(den, rhs.den);
	num *= lcm_1 / den;
	num += rhs.num * (lcm_1 / rhs.den);
	den = lcm_1;
	Normalize();
	return *this;
}

Rational& Rational::operator*=(const Rational& rhs) 
{
	num *= rhs.num;
	den *= rhs.den;
	Normalize();
	return *this;
}

Rational& Rational::operator-=(const Rational& rhs)
{
	int lcm_1 = lcm(den, rhs.den);
	num *= lcm_1 / den;
	num -= rhs.num * (lcm_1 / rhs.den);
	den = lcm_1;
	Normalize();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{
	if (rhs.num == 0) 
	{
		throw std::domain_error("Division by zero.");
	}
	num *= rhs.den;
	den *= rhs.num;
	Normalize();
	return *this;
}

Rational Rational::operator+(const Rational& rhs) const
{
	return (Rational(*this) += rhs); 
}

Rational Rational::operator-(const Rational& rhs) const
{
	return (Rational(*this) -= rhs);
}

Rational Rational::operator*(const Rational& rhs) const
{
	return (Rational(*this) *= rhs);
}

Rational Rational::operator/(const Rational& rhs) const
{
	return (Rational(*this) /= rhs);
}

Rational Rational::operator-() const 
{
	Rational r(*this);
	r.num *= -1;
	return r;
}

Rational Rational::operator+() const 
{
	Rational r(*this);
	return r;
}

bool Rational::operator==(const Rational& rhs) const
{
	return (num * rhs.den) == (rhs.num * den);
}

bool Rational::operator!=(const Rational& rhs) const
{
	return (num * rhs.den) != (rhs.num * den);
}

bool Rational::operator<(const Rational& rhs) const
{
	return (num * rhs.den) < (rhs.num * den);
}

bool Rational::operator>(const Rational& rhs) const
{
	return (num * rhs.den) > (rhs.num * den);
}

bool Rational::operator<=(const Rational& rhs) const
{
	return !(Rational(*this) > rhs);
}

bool Rational::operator>=(const Rational& rhs) const
{
	return !(Rational(*this) < rhs);
}

Rational& Rational::operator++()
{
	return *this += Rational(1);
}

Rational Rational::operator++(int t)
{
	Rational r(*this);
	*this += Rational(1);
	return r;
}

Rational& Rational::operator--()
{
	return *this -= Rational(1);
}

Rational Rational::operator--(int t)
{
	Rational r(*this);
	*this -= Rational(1);
	return r;
}


int Rational::GetNumerator()
{
	return num;
}

int Rational::GetDenominator()
{
	return den;
}
