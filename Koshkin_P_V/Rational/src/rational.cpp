#include "rational.h"
#include <cmath>
#include <stdexcept>
#include <numeric>

using namespace std;

int gcd(int x, int y) 
{
    x = abs(x);
    y = abs(y);
    if (x == 0) {
        return y;
    }
    return gcd(y % x, x);
}

int lcm(int x, int y)
{
    return (x * y)/gcd(x, y);
}

void Rational::Normalize()
{
    int del = gcd(num, den);
    num /= del;
    den /= del;
    if (den < 0) 
    {
    den *= -1;
    num *= -1;
    }
}

Rational::Rational(int _num)
    : num(_num)
    , den(1) 
    {
        Normalize();
    }
Rational::Rational(int _num, int _den)
    : num(_num)
    , den(_den) 
    {
    if (den == 0) 
    {
        throw invalid_argument("Denominator can`t be zero!");
    }
    Normalize();
    }
Rational::Rational(const Rational& other)
    : num(other.num)
    , den(other.den) 
    { }

Rational& Rational::operator=(const Rational& rhs) 
{
    num = rhs.num;
    den = rhs.den;
    return *this;
}

Rational& Rational::operator+=(const Rational& rhs)
{
    num = num*rhs.den + rhs.num*den;
    den *= rhs.den;
    Normalize();
    return *this;
}

Rational Rational::operator+(const Rational& rhs) const
{
    return Rational(*this) += rhs;
}

Rational& Rational::operator-=(const Rational& rhs)
{
    num = num*rhs.den - rhs.num*den;
    den *= rhs.den;
    Normalize();
    return *this;
}

Rational Rational::operator-(const Rational& rhs) const
{
    return Rational(*this) -= rhs;
}

Rational& Rational::operator*=(const Rational& rhs)
{
    num *= rhs.num;
    den *= rhs.den;
    Normalize();
    return *this;
}

Rational Rational::operator*(const Rational& rhs) const
{
    return Rational(*this) *= rhs;
}

Rational& Rational::operator/=(const Rational& rhs)
{
    if(rhs.num == 0)
    {
        throw domain_error("Division can`t be equal to zero!");
    }
    num *= rhs.den;
    den *= rhs.num;
    Normalize();
    return *this;
}

Rational Rational::operator/(const Rational& rhs) const
{
    return Rational(*this) /= rhs;
}

Rational Rational::operator-() const{
    Rational blub =*this;
    blub.num *= -1;
    return blub;
}

Rational& Rational::operator++() 
{
    return (*this += Rational(1,1));
}

Rational Rational::operator++(int a) 
{
    Rational blub = *this;
    *this += Rational(1,1);
    return blub;
}

Rational& Rational::operator--() 
{
    return (*this -= Rational(1,1));
}

Rational Rational::operator--(int a) 
{
    Rational blub = *this;
    *this -= Rational(1,1);
    return blub;
}

bool Rational::operator==(const Rational& rhs) const 
{
    return (num == rhs.num) && (den == rhs.den);
}

bool Rational::operator!=(const Rational& rhs) const 
{
    return !((num == rhs.num) && (den == rhs.den));
}

bool Rational::operator<(const Rational& rhs) const 
{
    return (num * rhs.den) < (den * rhs.num);
}

bool Rational::operator>(const Rational& rhs) const 
{
    return (num * rhs.den) > (den * rhs.num);
}

bool Rational::operator<=(const Rational& rhs) const 
{
    return !((num * rhs.den) > (den * rhs.num));
}

bool Rational::operator>=(const Rational& rhs) const 
{
    return !((num * rhs.den) < (den * rhs.num));
}

int Rational::GetNum() const 
{
    return num;
}

int Rational::GetDenom() const 
{
    return den;
}


ostream& operator<<(ostream& os, const Rational& r) 
{
    return os << r.GetNum() << "/" << r.GetDenom();
}