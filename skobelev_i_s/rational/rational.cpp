#include "rational.h"
#include <stdexcept>
#include <algorithm>

int Rational::GetDenominator() const{
    return den;
}
int Rational::GetNumerator() const{
    return num;
}

Rational::Rational(int _num) {
    num = _num;
    den = 1;
}

Rational::Rational(int _num, int _den) {
    num = _num;
    den = _den;
    Normalize();
    if (den == 0) {
        throw std::invalid_argument("denominator must not be equal to zero");
    }
}

Rational::Rational(const Rational &other) {
    num = other.GetNumerator();
    den = other.GetDenominator();
}

Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.GetNumerator();
    den = rhs.GetDenominator();
    return *this;
}

Rational Rational::operator+(const Rational& rhs) const{
    int r_den = den*rhs.GetDenominator();
	int r_num = num*rhs.GetDenominator() + rhs.GetNumerator()*den;
	Rational result (r_num, r_den);
	return result;
}
Rational Rational::operator-(const Rational& rhs) const{
    int r_den = den*rhs.GetDenominator();
	int r_num = num*rhs.GetDenominator() - rhs.GetNumerator()*den;
	Rational result (r_num, r_den);
	return result;
}
Rational Rational::operator*(const Rational& rhs) const{
    int r_den = den*rhs.GetDenominator();
	int r_num = num*rhs.GetNumerator();
	Rational result (r_num, r_den);
	return result;
}
Rational Rational::operator/(const Rational& rhs) const{
    int r_den = den*rhs.GetNumerator();
	int r_num = num*rhs.GetDenominator();
	Rational result (r_num, r_den);
	return result;
}

Rational& Rational::operator+=(const Rational& rhs) {
    int l = den * rhs.GetDenominator() / std::__gcd(den, rhs.GetDenominator());
    num = (l / rhs.GetDenominator()) * rhs.GetNumerator() + (l / den) * num;
    den = l;
    Normalize();
    return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
    int l = den * rhs.GetDenominator() / std::__gcd(den, rhs.GetDenominator());
    num = (l / den) * num - (l / rhs.GetDenominator()) * rhs.GetNumerator();
    den = l;
    Normalize();
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
    num = num * rhs.GetNumerator();
    den = den * rhs.GetDenominator();
    Normalize();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
    num = num * rhs.GetDenominator();
    den = den * rhs.GetNumerator();
    Normalize();
    return *this;
}

bool Rational::operator<(const Rational& rhs) const{
    return num * rhs.GetDenominator() < rhs.GetNumerator() * den;
}
bool Rational::operator<=(const Rational& rhs) const{
    return num * rhs.GetDenominator() <= rhs.GetNumerator() * den;
}
bool Rational::operator>(const Rational& rhs) const{
    return num * rhs.GetDenominator() > rhs.GetNumerator() * den;
}
bool Rational::operator>=(const Rational& rhs) const{
    return num * rhs.GetDenominator() >= rhs.GetNumerator() * den;
}

bool Rational::operator==(const Rational& rhs) const{
	return num*rhs.GetDenominator() == den*rhs.GetNumerator();
}

bool Rational::operator!=(const Rational& rhs) const{
    return num * rhs.GetDenominator() != rhs.GetNumerator() * den;
}

Rational Rational::operator-() const{
    Rational result(num * (-1), den);
    return result;
}
Rational Rational::operator+() const{
    Rational result(+num, den);
    return result;
}

Rational& Rational::operator++(){
    num += den;
    return *this;
}
Rational Rational::operator++(int) {
    Rational result(*this);
    ++(*this);
    return result;
}

void Rational::Normalize() {
    int g = std::__gcd(abs(num), den);
    num /= g;
    den /= g;
}
