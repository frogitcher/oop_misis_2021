#include "Rational.h"
#include <stdexcept>
#include <algorithm>
#include <math.h>

Rational::Rational()
    : num(0), den(1) {
}

Rational::Rational(int _num)
    : num(_num), den(1) {
}

Rational::Rational(int _num, int _den)
    : num(_num), den(_den) {
    if (den == 0){
        throw std::invalid_argument("denominator must not be equal to 0");
    }
    Normalize();
}

long long gcd(long long a, long long b){
    if (b==0){
        return a;
    }
    long long ans = gcd (b,a%b);
    return ans;
}

void Rational::Normalize(){
    if (num < 0 && den < 0){
        num = std::abs(num);
        den = std::abs(den);
    }

    if (num > 0 && den < 0){
        num = num * (-1);
        den = std::abs(den);
    }

    int g = gcd(std::abs(num), den);
    num /= g;
    den /= g;
}


bool Rational::operator==(const Rational& rhs) const {
    return num == rhs.num && den == rhs.den;
}

bool Rational::operator!=(const Rational& rhs) const {
    return !(num == rhs.num && den == rhs.den);
}

bool Rational::operator<(const Rational& rhs) const {
    return num*rhs.den < den*rhs.num;
}

bool Rational::operator>(const Rational& rhs) const {
    return num*rhs.den > den*rhs.num;
}

bool Rational::operator<=(const Rational& rhs) const {
    return num*rhs.den <= den*rhs.num;
}

bool Rational::operator>=(const Rational& rhs) const {
    return num*rhs.den >= den*rhs.num;
}

Rational Rational::operator+(const Rational& rhs) const{
    int num_result = num*rhs.den + rhs.num*den;
    int den_result = den*rhs.den;

    return Rational(num_result, den_result);
}

Rational Rational::operator-(const Rational& rhs) const{
    int num_result = num*rhs.den - rhs.num*den;
    int den_result = den*rhs.den;

    return Rational(num_result, den_result);
}

Rational Rational::operator/(const Rational& rhs) const{
    int num_result = num * rhs.den;
    int den_result = den * rhs.num;

    return Rational(num_result, den_result);
}

Rational Rational::operator*(const Rational& rhs) const{
    int num_result = num * rhs.num;
    int den_result = den * rhs.den;

    return Rational(num_result, den_result);
}

Rational& Rational::operator+=(const Rational& rhs){
    *this = *this + rhs;
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs){
    *this = *this - rhs;
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs){
    *this = *this * rhs;
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs){
    *this = *this / rhs;
    return *this;
}

Rational& Rational::operator++(){
    num = num + den;
    return *this;
}

Rational Rational::operator++(int){
    Rational initValue(*this);
    ++(*this);
    return initValue;
}

Rational& Rational::operator--(){
    num = num - den;
    return *this;
}

Rational Rational::operator--(int){
    Rational initValue(*this);
    --(*this);
    return initValue;
}
