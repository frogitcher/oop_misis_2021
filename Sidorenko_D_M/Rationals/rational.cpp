#include "rational.h"
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <mutex>
#include <iostream>
int gcd(int a, int b)
{
	if (a == 0)
		return b;
	else if (b == 0)
		return a;
	while (a != b) {
		if (a > b)
			a = a - b;
		else
			b = b - a;
	}
	return a;
}


Rational::Rational(int _num)
{
	SetNum(_num);
	SetDen(1);
}
Rational::Rational(int _num, int _den)
{
	SetNum(_num);
	SetDen(_den);
	if (GetDen() == 0)
		throw std::invalid_argument("denominator can't contain zero value");
	if (GetDen() < 0)
	{
		SetDen(-GetDen());
		SetNum(-GetNum());
	}
	simplify();
}

Rational::Rational(const Rational& other)
{
	SetNum(other.GetNum());
	SetDen(other.GetDen());
}

Rational Rational::operator=(const Rational& rhs)
{
	SetNum(rhs.GetNum());
	SetDen(rhs.GetDen());
	return *this;
}

Rational Rational::operator+(const Rational& rhs) const
{
	Rational ans;
	ans.SetNum(GetNum() * rhs.GetDen() + rhs.GetNum() * GetDen());
	ans.SetDen(GetDen() * rhs.GetDen());
	ans.simplify();
	return ans;
}

Rational Rational::operator-(const Rational& rhs) const
{
	Rational ans;
	ans = *this + (-rhs);
	//std::cout << ans.GetNum() << ' ' << ans.GetDen() << std::endl;
	//std::cout << ans.GetNum() << ' ' << ans.GetDen() << std::endl;
	return ans;
}

Rational Rational::operator*(const Rational& rhs) const
{
	Rational ans;
	ans.SetDen(GetDen() * rhs.GetDen());
	ans.SetNum(GetNum() * rhs.GetNum());
	ans.simplify();
	return ans;
	//return Rational(1);
}

Rational Rational::operator/(const Rational& rhs) const
{
	Rational ans(GetNum() * rhs.GetDen(), GetDen() * rhs.GetNum());
	ans.simplify();
	return ans;
}

Rational Rational::operator+=(const Rational& rhs)
{
	*this = *this + rhs;
	return *this;
}

Rational Rational::operator-=(const Rational& rhs)
{
	*this = *this - rhs;
	return *this;
}

Rational Rational::operator*=(const Rational& rhs)
{
	*this = *this * rhs;
	return *this;
}

Rational Rational::operator/=(const Rational& rhs)
{
	*this = *this / rhs;
	return *this;
}

Rational Rational::operator-() const
{
	Rational ans(-GetNum(), GetDen());
	return ans;
}

bool Rational::operator<(const Rational& rhs) const
{
	return (GetNum() * rhs.GetDen() < GetDen() * rhs.GetNum());
}

bool Rational::operator>(const Rational& rhs) const
{
	return rhs < *this;
}

bool Rational::operator<=(const Rational& rhs) const
{
	return (*this < rhs || *this == rhs);
}

bool Rational::operator>=(const Rational& rhs) const
{
	return (*this > rhs || *this == rhs);
}


bool Rational::operator==(const Rational& rhs) const
{
	return (GetNum() == rhs.GetNum() && GetDen() == rhs.GetDen());
}

bool Rational::operator!=(const Rational& rhs) const
{
	return !(*this == rhs);
}

Rational Rational::operator++(int)
{
	Rational q = *this;
	*this += 1;
	return q;
}

Rational& Rational::operator++() {
	*this = *this + Rational(1);
	return *this;
}

Rational& Rational::operator--()
{
	*this = *this - Rational(1);
	return *this;
}

Rational Rational::operator--(int)
{
	Rational q = *this;
	*this -= 1;
	return q;
}

int Rational::GetNum() const
{
	return num;
}

void Rational::SetNum(int _num)
{
	num = _num;
}

int Rational::GetDen() const
{
	return den;
}

void Rational::SetDen(int _den)
{
	if (_den == 0)
		throw std::invalid_argument("denominator can't contain zero value");
	den = _den;
}

void Rational::simplify()
{
	int g = gcd(std::abs(GetNum()), GetDen());
	SetNum(GetNum() / g);
	SetDen(GetDen() / g);
	if (GetDen() < 0)
	{
		SetDen(-GetDen());
		SetNum(-GetNum());
	}
}