#include "rational.h"
#include <stdexcept>
#include <numeric>                                     

Rational::Rational(int _num)
	: num (_num)
	, denum (1) {}

Rational::Rational(int _num, int _denum)
	: num (_num)
	, denum (_denum)
{
    Normalize();
}

Rational::Rational(const Rational& other)
    : num(other.num)
    , denum(other.denum) {}

bool Rational::operator==(const Rational& rhs) const
{
    return num == rhs.num && denum == rhs.denum;
}
bool Rational::operator!=(const Rational& rhs) const
{
    return !(num == rhs.num && denum == rhs.denum);
}
bool Rational::operator>(const Rational& rhs) const
{
	return (num*rhs.denum > rhs.num*denum);
;
}
bool Rational::operator>=(const Rational& rhs) const
{
	return (num*rhs.denum >= rhs.num*denum);
}
bool Rational::operator<(const Rational& rhs) const
{
	return (num*rhs.denum < rhs.num*denum);
}
bool Rational::operator<=(const Rational& rhs) const
{
	return (num*rhs.denum <= rhs.num*denum);
}

Rational Rational::operator+(const Rational& rhs) const
{
    return Rational(*this) += rhs;
}

Rational Rational::operator-(const Rational& rhs) const
{
    return Rational(*this) -= rhs;
}

Rational Rational::operator*(const Rational& rhs) const
{
    return Rational(*this) *= rhs;
}

Rational Rational::operator/(const Rational& rhs) const
{
    return Rational(*this) /= rhs;
}

Rational& Rational::operator=(const Rational& rhs)
{
    num = rhs.num;
    denum = rhs.denum;
    return *this;
}

Rational& Rational::operator+=(const Rational& rhs)
{
    num *= rhs.denum;
    num += rhs.num * denum;
    denum *= rhs.denum;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs)
{
    num *= rhs.denum;
    num -= rhs.num * denum;
    denum *= rhs.denum;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs)
{
    num *= rhs.num;
    denum *= rhs.denum;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{  
    num *= rhs.denum;
    denum *= rhs.num;
    Normalize();
    return *this;
}

Rational Rational::operator-() const
{
    Rational a(*this);
    a.num *= -1;
    return a;
}

Rational Rational::operator+() const
{
    return Rational(*this);
}

Rational& Rational::operator++()
{
    return *this += Rational(1,1);
}

Rational Rational::operator++(int a)
{
    Rational r(*this);
    *this += Rational(1,1);
    return r;
}

Rational& Rational::operator--()
{
    return *this -= Rational(1,1);
}

Rational Rational::operator--(int a)
{
    Rational r(*this);
    *this -= Rational(1,1);
    return r;
}

int Rational::GetNum() const
{
	return num;
}
int Rational::GetDenum() const
{
	return denum;
}

void Rational::Normalize()
{
    if(denum == 0)
    {
        throw std::domain_error("invalid denum - 0!");
    }

    int gc = std::gcd(num, denum);
    num /= gc;
    denum /= gc;
    if (denum < 0)
    {
        denum *= -1;
        num *= -1;
    }
}

std::ostream& operator<<(std::ostream& os, const Rational& r)
{
    return os << r.GetNum() << "/" << r.GetDenum();
}
