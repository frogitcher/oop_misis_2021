#include "rational.h"
int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}
void rational::normalize() {
	if (denom == 0) {
		throw "Division by zero!";
	}
	if (denom < 0) {
		num = -num;
		denom = -denom;
	}
}
rational::rational(int n, int d) : num(n), denom(d)
{
	normalize();
	reduce();
}
rational& rational::reduce()
{
	int d = gcd(abs(num), abs(denom));
	num /= d;
	denom /= d;
	return (*this);
}
bool rational::operator< (const rational& r) const
{
	return num * r.denom < r.num* denom;
}
bool rational::operator> (const rational& r) const
{
	return num * r.denom > r.num * denom;
}
bool rational::operator<= (const rational& r) const
{
	return !(*this > r);
}
bool rational::operator>= (const rational& r) const
{
	return !(*this < r);
}
bool rational::operator== (const rational& r) const
{
	return num * r.denom == r.num * denom;
}
bool rational::operator!= (const rational& r) const
{
	return !(*this == r);
}
rational rational::operator+ (const rational& r) const
{
	int new_num = this->num * r.denom + r.num * this->denom;
	int new_denom = r.denom * this->denom;
	return rational(new_num, new_denom);
}
rational rational::operator- (const rational& r) const
{
	int new_num = this->num * r.denom - r.num * this->denom;
	int new_denom = r.denom * this->denom;
	return rational(new_num, new_denom);
}
rational rational::operator* (const rational& r) const
{
	int new_num = this->num * r.num;
	int new_denom = r.denom * this->denom;
	return rational(new_num, new_denom);
}
rational rational::operator/ (const rational& r) const
{
	int new_num = this->num * r.denom;
	int new_denom = this->denom * r.num;
	return rational(new_num, new_denom);
}
rational& rational::operator+= (const rational& r)
{
	*this = *this + r;
	return *this;
}
rational& rational::operator-= (const rational& r)
{
	*this = *this - r;
	return *this;
}
rational& rational::operator*= (const rational& r)
{
	*this = *this * r;
	return *this;
}
rational& rational::operator/= (const rational& r)
{
	*this = *this / r;
	return *this;
}

rational& rational::operator++ ()
{
	*this += rational(1, 1);
	return *this;
}
rational& rational::operator++ (int r)
{
	*this += rational(1, 1);
	return *this;
}
rational rational::operator-- ()
{
	*this -= rational(1, 1);
	return *this;
}
rational rational::operator-- (int r)
{
	*this -= rational(1, 1);
	return *this;
}
rational& rational::operator= (const rational& r) 
{
	num = r.num;
	denom = r.denom;
	return *this;
}