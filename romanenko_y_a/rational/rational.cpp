#include "rational.h"
#include <stdexcept>
#include <algorithm>
#include <numeric>

int gcd(int n1,int n2) {
    return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}
int lcm(int a, int b) {
	return abs(a * b) / gcd(a, b);
}


Rational::Rational(int _num)
    : num(_num)
    , den(1)
{}
Rational::Rational(const Rational& rhs){
    num = rhs.num;
    den = rhs.den;
}
Rational::Rational(int _num, int _den)
    : num(_num)
    , den(_den) {
    if (den==0) {
        throw std::invalid_argument("denominator must not be equal to 0");
    }
    Normalize();
}

Rational& Rational::operator=(const Rational& rhs){
    num = rhs.num;
    den = rhs.den;
    return *this;
}

Rational Rational::operator+(const Rational& rhs) const{
    Rational r(*this);
    return r += rhs;
}
Rational Rational::operator-(const Rational& rhs) const{
    Rational r(*this);
    return r -= rhs;
}
Rational Rational::operator*(const Rational& rhs) const{
    Rational r(*this);
    return r *= rhs;
}
Rational Rational::operator/(const Rational& rhs) const{
    Rational r(*this);
    return r /= rhs;
}


Rational& Rational::operator+=(const Rational&  rhs) {
    int common = lcm(den, rhs.den);
    num = num * common / den + rhs.num * common / rhs.den;
    den = common;
    Normalize();
    return *this;
}
Rational& Rational::operator-=(const Rational&  rhs) {
    int common = lcm(den, rhs.den);
    num = num * common / den - rhs.num * common / rhs.den;
    den = common;
    Normalize();
    return *this;
}
Rational& Rational::operator*=(const Rational&  rhs) {
    num *= rhs.num;
    den *= rhs.den;
    Normalize();
    return *this;
}
Rational& Rational::operator/=(const Rational&  rhs) {
    if  (rhs.num == 0){
        throw std::runtime_error("division by 0");
    }
    num *= rhs.den;
    den *= rhs.num;
    Normalize();
    return *this;
}


bool Rational::operator<(const Rational& rhs) const{
    return rhs.den * num < den * rhs.num;
}
bool Rational::operator>(const Rational& rhs) const{
    return rhs.den * num > den * rhs.num;
}
bool Rational::operator<=(const Rational& rhs) const{
    return rhs.den * num <= den * rhs.num;
}
bool Rational::operator>=(const Rational& rhs) const{
    return rhs.den * num >= den * rhs.num;
}


bool Rational::operator==(const Rational& rhs) const{
    return num * rhs.den == den * rhs.num;
}
bool Rational::operator!=(const Rational& rhs) const{
    Rational r(*this);
    return !(r == rhs);
}

int Rational::GetNumerator() const{
    return num;
}

int Rational::GetDenominator() const{
    return den;
}

void Rational::Normalize() {
    if (den < 0){
        den *= -1;
        num *= -1;
    }
    int g = gcd(abs(num), den);
    num /= g;
    den /= g;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.GetNumerator() << "/" << r.GetDenominator();
}

