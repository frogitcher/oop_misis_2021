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
    Normalize();
}

Rational::Rational(const Rational& other): num(other.num), den(other.den)
{
}

Rational& Rational::operator=(const Rational& other)
{
    num = other.num;
    den = other.den;
    return *this;
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
    return (num*rhs.den < den*rhs.num);
}

bool Rational::operator<=(const Rational& rhs) const{
    return (num*rhs.den <= den*rhs.num);
}

bool Rational::operator>(const Rational& rhs) const{
    return !(*this <= rhs);
}

bool Rational::operator>=(const Rational& rhs) const{
    return !(*this < rhs);
}

bool Rational::operator==(const Rational& rhs) const{
    return (num*rhs.den == den*rhs.num);
}

bool Rational::operator!=(const Rational& rhs) const{
    return !(*this == rhs);
}

// ariphmetic operations

Rational Rational::operator+(const Rational& rhs) const{
    int common = lcm(den, rhs.den);
    int numerator = num*(common/den) + rhs.num*(common/rhs.den);
    return Rational(numerator, common);
}

Rational Rational::operator-(const Rational& rhs) const {
    return Rational(*this + Rational(-rhs.num, rhs.den));
}

Rational Rational::operator*(const Rational& rhs) const {
    int numerator = num * rhs.num;
    int denumerator = den * rhs.den;
    return (Rational(numerator, denumerator));
}

Rational Rational::operator/(const Rational& rhs) const {
    return Rational(*this * Rational(rhs.den, rhs.num));
}



Rational& Rational::operator+=(const Rational& rhs) {
    *this = Rational(*this + rhs);
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs){
    *this = Rational(*this - rhs);
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs){
    *this = Rational(*this * rhs);
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs){
    *this = Rational(*this / rhs);
    return *this;
}



Rational Rational::operator-() {
    return Rational(-num, den);
}

Rational Rational::operator+() {
    return Rational(*this);
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
    if (den == 0)
        throw std::invalid_argument("denominator must not be equal to zero");
    int g = gcd(num, den);
    int sign = den / std::abs(den);
    den = den * sign / g;
    num = num * sign / g;
}

int Rational::GetDenominator() const{
    return den;
}

int Rational::GetNumerator() const{
    return num;
}

void Rational::SetDenominator(int val) {
    den = val;
    Normalize();
}

void Rational::SetNumerator(int val) {
    num = val;
    Normalize();
}
