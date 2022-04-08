#include "Rational.h"
#include <stdexcept>
#include <math.h>
#include <algorithm>

Rational::Rational()
	: n(0), d(1) {
}
	
Rational::Rational(int _n)
	: n(_n), d(1) {
}
	
long long gcd(long long a, long long b){
	if (b==0)
	{
		return a;
	}
	long long ans = gcd (b,a%b);
	return ans;
}
Rational::Rational(int _n, int _d)
	: n(_n), d(_d) 
	{
		if (d == 0)
		{
			throw std::invalid_argument("The denominator is just not 0");
		}
		Norm();
	}
void Rational::Norm()
{
	if (n < 0 && d < 0)
	{
		n = std::abs(n);
	        d = std::abs(d);
	}
	if (n > 0 && d < 0)
	{
		n = n * (-1);
	        d = std::abs(d);
	}
	int g = gcd(std::abs(n), d);
	n /= g;
	d /= g;
}
bool Rational::operator==(const Rational& rhs) const 
{
	return n == rhs.n && d == rhs.d;
}
bool Rational::operator!=(const Rational& rhs) const 
{
	return !(n == rhs.n && d == rhs.d);
}
bool Rational::operator<(const Rational& rhs) const 
{
	return n*rhs.d < d*rhs.n;
}
bool Rational::operator>(const Rational& rhs) const 
{
	return n*rhs.d > d*rhs.n;
}
bool Rational::operator>=(const Rational& rhs) const 
{
	return n*rhs.d >= d*rhs.n;
}
bool Rational::operator<=(const Rational& rhs) const 
{
	return n*rhs.d <= d*rhs.n;
}
Rational Rational::operator+(const Rational& rhs) const
{
	int n_result = n*rhs.d + rhs.n*d;
	int d_result = d*rhs.d;
	return Rational(n_result, d_result);
}
Rational Rational::operator-(const Rational& rhs) const
{
	int n_result = n*rhs.d - rhs.n*d;
	int d_result = d*rhs.d;
	return Rational(n_result, d_result);
}
Rational Rational::operator/(const Rational& rhs) const
{
	int n_result = n * rhs.d;
	int d_result = d * rhs.n;
	return Rational(n_result, d_result);
}
Rational Rational::operator*(const Rational& rhs) const
{
	int n_result = n * rhs.n;
	int d_result = d * rhs.d;
	return Rational(n_result, d_result);
}
Rational& Rational::operator+=(const Rational& rhs)
{
	*this = *this + rhs;
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs)
{
	*this = *this - rhs;
	return *this;
}
Rational& Rational::operator/=(const Rational& rhs)
{
	*this = *this / rhs;
	return *this;
}
Rational& Rational::operator*=(const Rational& rhs)
{
	*this = *this * rhs;
	return *this;
}
Rational& Rational::operator++()
{
	n = n + d;
	return *this;
}
Rational& Rational::operator--()
{
	n = n - d;
	return *this;
}
Rational Rational::operator++(int)
{
	Rational initValue(*this);
	++(*this);
	return initValue;
}
Rational Rational::operator--(int)
{
	Rational initValue(*this);
	--(*this);
	return initValue;
}
