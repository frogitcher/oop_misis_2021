#include "rational.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>
using namespace std;
int gcd(int a, int b)
{
    a = std::abs(a);
    b = std::abs(b);
    if (a == 0)
    {
        return b;
    }
    return gcd(b % a, a);
}

int lcm(int a, int b)
{
    return abs(a * b) / gcd(a, b);
}
Rational::Rational(int _num)
{
    num = _num;
    den = 1;
}
Rational::Rational(int _num, int _den)
{
    num = _num;
    den = _den;
    if (den == 0)
    {
        throw std::invalid_argument("Den must be != 0");
    }
    Rational::Norm();
}
Rational::Rational(const Rational &other)
{
    num = other.GetNum();
    den = other.GetDen();
    Rational::Norm();
}
Rational Rational::operator+(const Rational &rhs) const
{
    return Rational(*this) += rhs;
}
Rational &Rational::operator=(const Rational &rhs)
{
    num = rhs.GetNum();
    den = rhs.GetDen();
    return *this;
}
Rational Rational::operator-(const Rational &rhs) const
{
    return Rational(*this) -= rhs;
}
Rational &Rational::operator+=(const Rational &rhs)
{
    int common = lcm(GetDen(), rhs.GetDen());
    num = GetNum() * (common / GetDen()) + rhs.GetNum() * (common / rhs.GetDen());
    den = common;
    Rational::Norm();
    return *this;
}
Rational &Rational::operator-=(const Rational &rhs)
{
    int common = lcm(GetDen(), rhs.GetDen());
    num = GetNum() * (common / GetDen()) - rhs.GetNum() * (common / rhs.GetDen());
    den = common;
    Rational::Norm();
    return *this;
}
Rational &Rational::operator*=(const Rational &rhs)
{
    num *= rhs.GetNum();
    den *= rhs.GetDen();
    Norm();
    return *this;
}
Rational &Rational::operator/=(const Rational &rhs)
{
    if (rhs == Rational(0))
    {
        throw std::domain_error("Division by 0!");
    }
    num *= rhs.GetDen();
    den *= rhs.GetNum();
    Norm();
    return *this;
}
Rational Rational::operator/(const Rational &rhs) const
{
    return Rational(*this) /= rhs;
}
Rational Rational::operator*(const Rational &rhs) const
{
    return Rational(*this) *= rhs;
}
int Rational::GetDen() const
{
    return den;
}

int Rational::GetNum() const
{
    return num;
}

bool Rational::operator<(const Rational &rhs) const
{
    return GetNum() * rhs.GetDen() < rhs.GetNum() * GetDen();
}
bool Rational::operator<=(const Rational &rhs) const
{
    return GetNum() * rhs.GetDen() <= rhs.GetNum() * GetDen();
}
bool Rational::operator>(const Rational &rhs) const
{
    return GetNum() * rhs.GetDen() > rhs.GetNum() * GetDen();
}
bool Rational::operator>=(const Rational &rhs) const
{
    return GetNum() * rhs.GetDen() >= rhs.GetNum() * GetDen();
}
bool Rational::operator==(const Rational &rhs) const
{
    return GetNum() * rhs.GetDen() == rhs.GetNum() * GetDen();
}
bool Rational::operator!=(const Rational &rhs) const
{
    return GetNum() * rhs.GetDen() != rhs.GetNum() * GetDen();
}

void Rational::Norm()
{
    if (GetDen() < 0 && GetNum() >= 0)
    {
        den = -den;
        num = -num;
    }
    int g = gcd(abs(GetNum()), GetDen());
    num /= g;
    den /= g;
}