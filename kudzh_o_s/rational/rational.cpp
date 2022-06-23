#include <iostream>
#include "rational.h"
#include <math.h>


Rational:: Rational(const int& num)
{
    numerator = num;
    denomerator = 1;
}

Rational:: Rational (const int& num, const int& denom)
{
    numerator = num;

    denomerator = denom;
    convert();
}

Rational:: Rational(const Rational& other)
{
    numerator = other.numerator;
    denomerator = other.denomerator;
}




Rational& Rational::operator=(const Rational& rhs)
{
    numerator = rhs.numerator;
    denomerator = rhs.denomerator;
    return *this;
}

Rational& Rational::operator+=(const Rational& rhs)
{
    numerator = numerator * rhs.denomerator + rhs.numerator * denomerator;
    denomerator = denomerator * rhs.denomerator;
    convert();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs)
{
    numerator = numerator * rhs.denomerator - rhs.numerator * denomerator;
    denomerator = denomerator * rhs.denomerator;
    convert();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs)
{
    numerator = numerator * rhs.numerator;
    denomerator = denomerator * rhs.denomerator;
    convert();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{
    numerator = numerator * rhs.denomerator;
    denomerator = denomerator * rhs.numerator;
    convert();
    return *this;
}



Rational Rational:: operator+(const Rational& rhs)
{
    return Rational(*this) += rhs;
}

Rational Rational:: operator-(const Rational& rhs)
{
    return Rational(*this) -= rhs;
}

Rational Rational:: operator*(const Rational& rhs)
{
    return Rational(*this) *= rhs;
}

Rational Rational:: operator/(const Rational& rhs)
{
    return Rational(*this) /= rhs;
}



bool Rational:: operator==(const Rational& rhs) const
{
    return (numerator * rhs.denomerator) == (denomerator * rhs.numerator);
}

bool Rational:: operator>(const Rational& rhs) const
{
    return numerator * rhs.denomerator > denomerator * rhs.numerator;
}

bool Rational:: operator<(const Rational& rhs) const
{
    return numerator * rhs.denomerator < denomerator * rhs.numerator;
}

bool Rational:: operator>=(const Rational& rhs) const
{
    return numerator * rhs.denomerator >= denomerator * rhs.numerator;
}

bool Rational:: operator<=(const Rational& rhs) const
{
    return numerator * rhs.denomerator <= denomerator * rhs.numerator;
}



void Rational::convert()
{
    if (numerator == 0){
        return;
    }
    for (int i = 2; i <= sqrt(std::max(numerator, denomerator)); i++){
        if (denomerator % i == 0 && numerator % i == 0){
            numerator = int(numerator / i);
            denomerator = int(denomerator / i);
        }
    }
}
