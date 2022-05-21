#include "Rational.h"
#include <stdexcept>
#include <algorithm>
#include <math.h>

Rational::Rational(): num(0), den(1)
{
}

Rational::Rational(int _num): num(_num), den(1)
{
}

Rational::Rational(int _num, int _den): num(_num), den(_den)
{
    if (_den == 0)
        throw std::invalid_argument("denominator must not be equal to zero");
    Normalize();
}

Rational::Rational(const Rational& other): num(other.GetNumerator()), den(other.GetDenominator())
{
    Normalize();
}

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (a == 0 || b == 0) {
        return std::max(a, b);
    }
    while (a > 0 && b > 0) {
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return std::max(a,b);
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

// boolean operations

bool Rational::operator<(const Rational& rhs) const{
    return (num*rhs.GetDenominator() < den*rhs.GetNumerator());
}

bool Rational::operator<=(const Rational& rhs) const{
    return (num*rhs.GetDenominator() <= den*rhs.GetNumerator());
}

bool Rational::operator>(const Rational& rhs) const{
    return (num*rhs.GetDenominator() > den*rhs.GetNumerator());
}

bool Rational::operator>=(const Rational& rhs) const{
    return (num*rhs.GetDenominator() >= den*rhs.GetNumerator());
}

bool Rational::operator==(const Rational& rhs) const{
    return (num*rhs.GetDenominator() == den*rhs.GetNumerator());
}

bool Rational::operator!=(const Rational& rhs) const{
    return (num*rhs.GetDenominator() != den*rhs.GetNumerator());
}

// ariphmetic operations

Rational Rational::operator+(const Rational& rhs) const{
    int common = lcm(GetDenominator(), rhs.GetDenominator());
    int numerator = GetNumerator()*(common/GetDenominator()) + rhs.GetNumerator()*(common/rhs.GetDenominator());
    return Rational(numerator, common);
}

Rational Rational::operator-(const Rational& rhs) const {
    return Rational(*this + Rational(-rhs.GetNumerator(), rhs.GetDenominator()));
}

Rational Rational::operator*(const Rational& rhs) const {
    int common = lcm(GetDenominator(), rhs.GetDenominator());
    int numerator = GetNumerator() * rhs.GetNumerator();
    int denumerator = GetDenominator() * rhs.GetDenominator();
    return Rational(numerator, denumerator);
}

Rational Rational::operator/(const Rational& rhs) const {
    return Rational(*this * Rational(rhs.GetDenominator(), rhs.GetNumerator()));
}



Rational Rational::operator+=(const Rational& rhs) {
    *this = Rational(*this + rhs);
    return *this;
}

Rational Rational::operator-=(const Rational& rhs){
    *this = Rational(*this - rhs);
    return *this;
}

Rational Rational::operator*=(const Rational& rhs){
    *this = Rational(*this * rhs);
    return *this;
}

Rational Rational::operator/=(const Rational& rhs){
    *this = Rational(*this / rhs);
    return *this;
}



Rational Rational::operator-() {
    return Rational(-GetNumerator(), GetDenominator());
}

Rational Rational::operator+() {
    return (*this);
}

Rational& Rational::operator++() {
    *this += Rational(1,1);
    return *this;
}

Rational Rational::operator++(int){
    Rational temp = *this;
    ++(*this);
    return temp;
}

Rational& Rational::operator--() {
    *this -= Rational(1,1);
    return *this;
}

Rational Rational::operator--(int){
    Rational temp = *this;
    --(*this);
    return temp;
}

// functional
void Rational::Normalize() {
    int g = gcd(GetNumerator(), GetDenominator());
    int sign = GetDenominator() / std::abs(GetDenominator());
    SetNumerator(GetNumerator()*sign/g);
    SetDenominator(GetDenominator()*sign/g);
}

int Rational::GetDenominator() const{
    return den;
}

int Rational::GetNumerator() const{
    return num;
}

void Rational::SetDenominator(int val) {
    den = val;
}

void Rational::SetNumerator(int val) {
    num = val;
}
