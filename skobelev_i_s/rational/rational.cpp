#include "rational.h"
#include <stdexcept>
#include <algorithm>

int Rational::GetDenominator() {
    return den;
}
int Rational::GetNumerator() {
    return num;
}

Rational::Rational(int _num) {
    num = _num;
    den = 1;
}

Rational::Rational(int _num, int _den) {
    num = _num;
    den = _den;
    if (den == 0) {
        throw std::invalid_argument("denominator must not be equal to zero");
    }
}

Rational::Rational(Rational &other) {
    num = other.GetNumerator();
    den = other.GetDenominator();
}

Rational& Rational::operator=(Rational& rhs) {
    num = rhs.GetNumerator();
    den = rhs.GetDenominator();
    return *this;
}

Rational Rational::operator+(Rational& rhs) {
    int l = den * rhs.GetDenominator() / std::__gcd(den, rhs.GetDenominator());
    num = (l / rhs.GetDenominator()) * rhs.GetNumerator() + (l / den) * num;
    den = l;
    this->Normalize();
    return *this;
}
Rational Rational::operator-(Rational& rhs) {
    int l = den * rhs.GetDenominator() / std::__gcd(den, rhs.GetDenominator());
    num = (l / den) * num - (l / rhs.GetDenominator()) * rhs.GetNumerator();
    den = l;
    this->Normalize();
    return *this;
}
Rational Rational::operator*(Rational& rhs) {
    num *= rhs.GetNumerator();
    den *= rhs.GetDenominator();
    this->Normalize();
    return *this;
}
Rational Rational::operator/(Rational& rhs) {
    num *= rhs.GetDenominator();
    den *= rhs.GetNumerator();
    if (den == 0) {
        throw std::invalid_argument("denominator must not be equal to zero");
    }
    this->Normalize();
    return *this;
}

Rational& Rational::operator+=(Rational& rhs) {
    int l = den * rhs.GetDenominator() / std::__gcd(den, rhs.GetDenominator());
    num = (l / rhs.GetDenominator()) * rhs.GetNumerator() + (l / den) * num;
    den = l;
    this->Normalize();
    return *this;
}
Rational& Rational::operator-=(Rational& rhs) {
    int l = den * rhs.GetDenominator() / std::__gcd(den, rhs.GetDenominator());
    num = (l / den) * num - (l / rhs.GetDenominator()) * rhs.GetNumerator();
    den = l;
    this->Normalize();
    return *this;
}
Rational& Rational::operator*=(Rational& rhs) {
    num = num * rhs.GetNumerator();
    den = den * rhs.GetDenominator();
    this->Normalize();
    return *this;
}
Rational& Rational::operator/=(Rational& rhs) {
    num = num * rhs.GetDenominator();
    den = den * rhs.GetNumerator();
    this->Normalize();
    return *this;
}

bool Rational::operator<(Rational& rhs) const{
    return num * rhs.GetDenominator() < rhs.GetNumerator() * den;
}
bool Rational::operator<=(Rational& rhs) const{
    return num * rhs.GetDenominator() <= rhs.GetNumerator() * den;
}
bool Rational::operator>(Rational& rhs) const{
    return num * rhs.GetDenominator() > rhs.GetNumerator() * den;
}
bool Rational::operator>=(Rational& rhs) const{
    return num * rhs.GetDenominator() >= rhs.GetNumerator() * den;
}

bool Rational::operator==(Rational& rhs) const{
    return num * rhs.GetDenominator() == rhs.GetNumerator() * den;
}
bool Rational::operator!=(Rational& rhs) const{
    return num * rhs.GetDenominator() != rhs.GetNumerator() * den;
}

Rational Rational::operator+() {
    num = +num;
    den = +den;
    return *this;
}

void Rational::Normalize() {
    int g = std::__gcd(abs(num), den);
    num /= g;
    den /= g;
}