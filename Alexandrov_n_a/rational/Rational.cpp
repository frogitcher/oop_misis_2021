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

rational rational::get_reduced()const {
	int d = gcd(num, denom);
	return rational(num / d, denom / d);
}
bool rational::operator< (const rational& r) const
{
	return (long long)this->num * r.denom < (long long)r.num* this->denom;
}
bool rational::operator> (const rational& r) const
{
	return (long long)this->num * r.denom > (long long)r.num * this->denom;
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
	return (long long)this->num * r.denom == (long long)r.num * this->denom;
}
bool rational::operator!= (const rational& r) const
{
	return !(*this == r);
}

rational rational::operator+ (const rational& r)
{
	long long new_num = this->num * r.denom + r.num * this->denom;
	long long new_denom = r.denom * this->denom;
	return rational(new_num, new_denom);
}
rational rational::operator- (const rational& r)
{
	long long new_num = this->num * r.denom - r.num * this->denom;
	long long new_denom = r.denom * this->denom;
	return rational(new_num, new_denom);
}
rational rational::operator* (const rational& r)
{
	long long new_num = this->num * r.num;
	long long new_denom = r.denom * this->denom;
	return rational(new_num, new_denom);
}
rational rational::operator/ (const rational& r)
{
	long long new_num = this->num * r.denom;
	long long new_denom = this->denom * r.num;
	return rational(new_num, new_denom);
}
rational rational::operator+= (const rational& r)
{
	return *this + r;
}
rational rational::operator-= (const rational& r)
{
	return *this - r;
}
rational rational::operator*= (const rational& r)
{
	return *this * r;
}
rational rational::operator/= (const rational& r)
{
	return *this / r;
}

rational rational::operator++ ()
{
	return *this + rational(1, 1);
}
rational rational::operator++ (int r)
{
	return *this + rational(1, 1);
}
rational rational::operator-- ()
{
	return *this - rational(1, 1);
}
rational rational::operator-- (int r)
{
	return *this - rational(1, 1);
}