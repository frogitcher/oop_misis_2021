#include "rational.h"

#include <numeric>
#include <stdexcept>

void Rational::Normalize(){
    if (denominator < 0){
        denominator *= -1;
        numerator *= -1;
    }
    int g = std::gcd(numerator, denominator); 
    numerator /= g;
    denominator /= g;
}

Rational::Rational(int _numerator)
    : numerator(_numerator)
    , denominator(1){
}

Rational::Rational(const Rational& rhs)
    :numerator(rhs.numerator)
    , denominator(rhs.denominator){
}

Rational::Rational(int _numerator, int _denominator){
    if (_denominator == 0){
        throw std::invalid_argument("denominator must not be 0");
    }
    numerator = _numerator;
    denominator = _denominator;
    Normalize();
}

Rational& Rational::operator=(const Rational& rhs){
    numerator = rhs.numerator;
    denominator = rhs.denominator;
    return *this;
}

Rational Rational::operator+(const Rational& rhs) const{
    return Rational(numerator * rhs.denominator + rhs.numerator * denominator, denominator * rhs.denominator);
}

Rational Rational::operator-(const Rational& rhs) const{
    return Rational(numerator * rhs.denominator - rhs.numerator * denominator, denominator * rhs.denominator);
}

Rational Rational::operator*(const Rational& rhs) const{

    return Rational(numerator * rhs.numerator, denominator * rhs.denominator);
}

Rational Rational::operator/(const Rational& rhs) const{
    if (rhs.numerator == 0){
        throw std::invalid_argument("division by 0");
    }
    return Rational(numerator * rhs.denominator, denominator * rhs.numerator);
}

Rational& Rational::operator+=(const Rational& rhs){
    numerator += rhs.numerator * denominator;
    denominator *= rhs.denominator ;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs){
    numerator -= rhs.numerator * denominator;
    denominator *= rhs.denominator;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs){
    numerator *= rhs.numerator;
    denominator *= rhs.denominator ;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs){
    if (rhs.numerator == 0){
        throw std::invalid_argument("division by 0");
    }
    numerator *= rhs.denominator;
    denominator *=  rhs.numerator;
    Normalize();
    return *this;
}

bool Rational::operator==(const Rational& rhs) const{
    return (numerator * rhs.denominator == denominator * rhs.numerator);
}

bool Rational::operator!=(const Rational& rhs) const{
    return !(numerator * rhs.denominator == denominator * rhs.numerator);
}

bool Rational::operator<(const Rational& rhs) const{
    return (numerator * rhs.denominator < denominator * rhs.numerator);
}

bool Rational::operator>(const Rational& rhs) const{
    return (numerator * rhs.denominator > denominator * rhs.numerator);
}

bool Rational::operator<=(const Rational& rhs) const{
    return !(*this > rhs);
}

bool Rational::operator>=(const Rational& rhs) const{
    return !(*this < rhs);
}

int Rational::GetNumerator() const{
    return numerator;
}

int Rational::GetDenominator() const{
    return denominator;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.GetNumerator() << "/" << r.GetDenominator();
}