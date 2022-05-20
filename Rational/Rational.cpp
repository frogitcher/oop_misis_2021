#include "Rational.h"
#include <stdexcept>
#include <algorithm>
#include <numeric>
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
int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}


Rational::Rational(int _num) // construction of Egypt's fraction)))
    : num(_num)
    , den(1)
{}

Rational::Rational(int _num, int _den)
    : num(_num)
    , den(_den)
{
    if (den == 0)
    {
        throw std::invalid_argument("denominator must be != 0");
    }
    Rational::Normalize();
}

Rational::Rational(const Rational& other)
{
    this->setden(other.getden());
    this->setnum(other.getnum());
}


Rational& Rational::operator+=(const Rational& rhs)
{
    Rational& lhs = *this;
    int common = lcm(lhs.getden(), rhs.getden()); //NOK ot znaminat
    lhs.setnum(lhs.getnum() * (common / lhs.getden()));          //num *= (common / den);   
    lhs.setnum(lhs.getnum() + (rhs.getnum() * (common / rhs.getden())));        //num = num + (rhs.num * (common / rhs.den));
    lhs.setden(common);
    lhs.Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs)
{
    Rational& lhs = *this;
    int common = lcm(lhs.getden(), rhs.getden());
    lhs.setnum(lhs.getnum() * (common / lhs.getden()));
    lhs.setnum(lhs.getnum() - (rhs.getnum() * (common / rhs.getden())));
    lhs.setden(common);
    lhs.Normalize();
    return *this;
}



Rational& Rational::operator*=(const Rational& rhs)
{
    Rational& lhs = *this;
    lhs.setnum(lhs.getnum() * rhs.getnum());
    lhs.setden(lhs.getden() * rhs.getden());
    lhs.Normalize();
    return *this;
}



Rational& Rational::operator/=(const Rational& rhs)
{
    Rational& lhs = *this;
    if (!rhs.getnum())
    {
        throw std::invalid_argument("u cannot devide by 0");
    }

    lhs.setnum(lhs.getnum() * rhs.getden());
    lhs.setden(lhs.getden() * rhs.getnum());
    lhs.Normalize();

    return *this;
}



void Rational::showme() const
{
    std::cout << this->num << "/" << this->den;
}

int Rational::getden() const
{
    return this->den;
}

int Rational::getnum() const
{
    return this->num;
}

void Rational::setden(const int& _den)
{
    this->den = _den;
}

void Rational::setnum(const int& _num)
{
    this->num = _num;
}



Rational& Rational::operator=(const Rational& rhs)
{
    Rational& lhs = *this;
    lhs.setnum(rhs.getnum());        //num = rhs.num;
    lhs.setden(rhs.getden());        //den = rhs.den;
    return *this;
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

Rational Rational::operator-() const
{
    Rational _buf = *this * Rational(-1, 1);
    return _buf;
}

bool Rational::operator<(const Rational& rhs) const
{
    const Rational& lhs = *this;
    return lhs.getnum() * rhs.getden() < lhs.getden() * rhs.getnum();          //num * rhs.den < den* rhs.num;
}

bool Rational::operator<=(const Rational& rhs) const
{
    const Rational& lhs = *this;
    return lhs.getnum() * rhs.getden() <= lhs.getden() * rhs.getnum();
}

bool Rational::operator>(const Rational& rhs) const
{
    const Rational& lhs = *this;
    return lhs.getnum() * rhs.getden() > lhs.getden() * rhs.getnum();
}

bool Rational::operator>=(const Rational& rhs) const
{
    const Rational& lhs = *this;
    return lhs.getnum() * rhs.getden() >= lhs.getden() * rhs.getnum();
}

bool Rational::operator==(const Rational& rhs) const
{
    const Rational& lhs = *this;
    return lhs.getnum() * rhs.getden() == lhs.getden() * rhs.getnum();
}

bool Rational::operator!=(const Rational& rhs) const
{
    const Rational& lhs = *this;
    return lhs.getnum() * rhs.getden() != lhs.getden() * rhs.getnum();
}




void Rational::Normalize() {

    Rational& self = *this;
    if (self.getden() < 0)
    {
        self.setden(self.getden() * -1);
        self.setnum(self.getnum() * -1);
    }
    if (self.getnum() == 0)
    {
        self.setden(1);
    }
    else
    {
        int g = gcd(std::abs(self.getnum()), self.getden());
        self.setnum(self.getnum() / g);    //num /= g;
        self.setden(self.getden() / g);
    }
}