#include "rational.h"

#include <numeric>
#include <stdexcept>

void Rational::Normalize(){
    int g = std::gcd(numerator, denominator); 
    numerator /= g;
    denominator /= g;
}

Rational::Rational(int _numenator){
    numerator = _numenator;
    denominator = 1;
}

Rational::Rational(Rational& rhs){
    numerator = rhs.numerator;
    denominator = rhs.denominator;
}

Rational::Rational(int _numenator, int _denominator){
    if (denominator == 0){
        throw std::invalid_argument("denominator must not be 0 ");
    }
    numerator = _numenator;
    denominator = _denominator;
    Normalize();
}

Rational& Rational::operator=(const Rational& rhs){
    numerator == rhs.numerator;
    denominator == rhs.denominator;
    return *this;
}

Rational Rational::operator+(const Rational& rhs){
    return Rational(numerator * rhs.denominator + rhs.numerator * denominator, denominator * rhs.denominator);
}

Rational Rational::operator-(const Rational& rhs){
    return Rational(numerator * rhs.denominator - rhs.numerator * denominator, denominator * rhs.denominator);
}

Rational Rational::operator*(const Rational& rhs){
    return Rational(numerator * rhs.numerator, denominator * rhs.denominator);
}

Rational Rational::operator/(const Rational& rhs){
    return Rational(numerator * rhs.denominator, denominator * rhs.numerator);
}

Rational& Rational::operator+=(const Rational& rhs){
    numerator += rhs.numerator * denominator;
    denominator *= rhs.denominator ;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs){
    numerator -= rhs.numerator() * denominator;
    denominator *= rhs.denominator;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs){
    numerator *= rhs.numerator();
    denominator *= rhs.denominator ;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs){
    numerator *= rhs.denominator;
    denominator *=  rhs.numerator;
    Normalize();
}

bool Rational::operator==(const Rational& rhs){
    return (numerator * rhs.denominator == denominator * rhs.numerator);
}


bool Rational::operator<(const Rational& rhs){
    return (numerator * rhs.denominator < denominator * rhs.numerator);
}

bool Rational::operator>(const Rational rhs){
    return (numerator * rhs.denominator > denominator * rhs.numerator);
}

bool Rational::operator<=(const Rational& rhs){
    return (numerator * rhs.denominator <= denominator * rhs.numerator);
}

bool Rational::operator>=(const Rational& rhs){
    return (numerator * rhs.denominator >= denominator * rhs.numerator);
}

int Rational::GetNumerator(){
    return numerator;
}

int Rational::GetDenominator(){
    return denominator;
}