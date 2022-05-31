#include <iostream>
#include "rational.h"
#include <stdexcept>
#include <numeric>
#include <cmath> 

void Rational::simplify() {
    if ((den < 0) || ((den < 0) && (num < 0))) {
        num *= -1;
        den *= -1;
    }
    int div = std::gcd(std::abs(num), den); //divisor
    num /= div;
    den /= div;
}

Rational::Rational(int _num) 
    :num(_num)
    ,den(1)
{}

Rational::Rational(int _num, int _den)
    :num(_num)
    ,den(_den) {
        if (den == 0) {
            throw std::invalid_argument("Denominator can't be equal to zero");
        }
        simplify();
}

Rational::Rational(const Rational& other) 
    :num(other.num)
    ,den(other.den)
{}

Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.num;
    den = rhs.den;
    return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
    num = num * rhs.den + den * rhs.num;
    den *= rhs.den;
    simplify();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    num = num * rhs.den - den * rhs.num;
    den *= rhs.den;
    simplify();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    num *= rhs.num;
    den *= rhs.den;
    simplify();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num == 0) {
        throw std::invalid_argument("Can't divide by zero");
    } 
    num *= rhs.den;
    den *= rhs.num;
    simplify();
    return *this;
}

Rational Rational::operator+(const Rational& rhs) const{
    Rational res(*this); // res - result
    res += rhs;
    return res;
}

Rational Rational::operator-(const Rational& rhs) const{
    Rational res(*this);
    res -= rhs;
    return res;
}

Rational Rational::operator*(const Rational& rhs) const{
    Rational res(*this);
    res *= rhs;
    return res;
}

Rational Rational::operator/(const Rational& rhs) const{
    Rational res(*this);
    res /= rhs;
    return res;
}

Rational& Rational::operator++() {
    num += den;
    return *this;
}

Rational Rational::operator++(int) {
    Rational copy(*this);
    num += den;
    return copy;
}

Rational& Rational::operator--() {
    num -= den;
    return *this;
}

Rational Rational::operator--(int) {
    Rational copy(*this);
    num -= den;
    return copy;
}

bool Rational::operator<(const Rational& rhs) const{
    return (num * rhs.den < rhs.num * den);
}

bool Rational::operator>(const Rational& rhs) const{
    return (num * rhs.den > rhs.num * den);
}

bool Rational::operator<=(const Rational& rhs) const{
    return !((*this) > rhs);
}

bool Rational::operator>=(const Rational& rhs) const{
    return !((*this) < rhs);
}

bool Rational::operator==(const Rational& rhs) const{
    return (num * rhs.den == rhs.num * den);
}

bool Rational::operator!=(const Rational& rhs) const{
    return !((*this) == rhs);
}

int Rational::get_num() const {
    return num;
}

int Rational::get_den() const{
    return den;
}

std::ostream& operator<<(std::ostream& ost, const Rational& ex) {
    return ost<<ex.get_num()<<"/"<<ex.get_den();
}