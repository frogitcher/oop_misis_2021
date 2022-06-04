#include "class_rational.h"
#include <stdexcept>
#include <cmath>

int gcd (int a, int b) {
    a=std::abs(a);
    b=std::abs(b);
	if (b == 0)
		return a;
	else
		return gcd (b, a % b);
}

int lcm (int a, int b) {
	return a / gcd (a, b) * b;
}

Rational::Rational(int _num,int _den)
    : num(_num)
    , den(_den)
    {
        if (den==0)
        {
            throw std::invalid_argument("Denominator must not be equal to 0!");
        }
        else
        {
            if (den<0)
            {
                num *= -1;
                den *= -1;
            }
            Normalize();
        }
    }

Rational::Rational(int _num)
    : num(_num)
    , den(1)
    {
        Normalize();
    }

Rational::Rational(const Rational& other)
    : num(other.num)
    , den(other.den)
{}

Rational& Rational::operator=(const Rational& rhs)
{
    num=rhs.num;
    den=rhs.den;
    return *this;
}


Rational& Rational::operator+=(const Rational& rhs)
{
    int temp=lcm(den, rhs.den);
    num*=temp/den;
    num+=(temp/rhs.den)*rhs.num;
    den=temp;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs)
{
    int temp=lcm(den, rhs.den);
    num*=temp/den;
    num-=(temp/rhs.den)*rhs.num;
    den=temp;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs)
{
    num*=rhs.num;
    den*=rhs.den;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{
    if (rhs.num==0)
    {
        throw std::domain_error("Division by 0!");
    }
    num*=rhs.den;
    den*=rhs.num;
    Normalize();
    return *this;
}

Rational Rational::operator+(const Rational& rhs) const
{
    return Rational(*this)+= rhs;
}

Rational Rational::operator*(const Rational& rhs) const
{
    return Rational(*this)*= rhs;
}

Rational Rational::operator-(const Rational& rhs) const
{
    return Rational(*this)-= rhs;
}

Rational Rational::operator/(const Rational& rhs) const
{
    return Rational(*this)/= rhs;
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

bool Rational::operator==(const Rational& rhs)const
{
    return (num==rhs.num)&&(den==rhs.den);
}

bool Rational::operator!=(const Rational& rhs) const
{
    return !(*this==rhs);
}

bool Rational::operator>(const Rational& rhs) const
{
    return(num*rhs.den)> (den*rhs.num);
}

bool Rational::operator<(const Rational& rhs) const
{
    return(num*rhs.den)< (den*rhs.num);
}

bool Rational::operator>=(const Rational& rhs) const
{
    return(num*rhs.den)>= (den*rhs.num);
}

bool Rational::operator<=(const Rational& rhs) const
{
    return(num*rhs.den)<= (den*rhs.num);
}

int Rational::GetNumerator() const
{
    return(num);
}

int Rational::GetDenominator() const
{
    return(den);
}

void Rational::Normalize()
{
    if (den<1)
    {
        den*=-1;
        num*=-1;
    }
    int temp=gcd(num,den);
    num/=temp;
    den/=temp;
}
int main()
{
    return 0;
}
