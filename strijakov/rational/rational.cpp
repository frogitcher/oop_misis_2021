#include "rational.h"
#include <cmath>
#include <stdexcept>
#include <numeric>

int gcd(int x, int y) {
    x = std::abs(x);
    y = std::abs(y);
    if (x == 0) {
        return y;
    }
    return gcd(y % x, x);
}


Rational::Rational(int _num)
    : num(_num)
    , den(1) {
        Normalize();
      }
Rational::Rational(int _num, int _den)
    : num(_num)
    , den(_den) {
    if (den == 0) {
            throw std::invalid_argument("Denominator can`t be zero!");
    }
    Normalize();
}
Rational::Rational(const Rational& other)
    : num(other.num)
    , den(other.den) {}

Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.num;
    den = rhs.den;
    return *this;
}
Rational& Rational::operator+=(const Rational& rhs) {
    num *= rhs.den;
    num += rhs.num * den;
    den *= rhs.den;
    Normalize();
    return *this;
}
Rational Rational::operator+(const Rational& rhs) const{
    return Rational(*this) += rhs;
}
Rational& Rational::operator-=(const Rational& rhs) {
    num *= rhs.den;
    num -= rhs.num * den;
    den *= rhs.den;
    Normalize();
    return *this;
}
Rational Rational::operator-(const Rational& rhs) const {
    return Rational(*this) -= rhs;
}
Rational& Rational::operator*=(const Rational& rhs) {
    num *= rhs.num;
    den *= rhs.den;
    Normalize();
    return *this;
}
Rational Rational::operator*(const Rational& rhs) const {
    return Rational(*this) *= rhs;
}
Rational& Rational::operator/=(const Rational& rhs) {
    if(rhs.num == 0){
        throw std::domain_error("Divisor can`t be zero!");
    }
    num *= rhs.den;
    den *= rhs.num;
    Normalize();
    return *this;
}
Rational Rational::operator/(const Rational& rhs) const {
    return Rational(*this) /= rhs;
}
Rational Rational::operator-() const {
    Rational a(*this);
    a.num *= -1;
    return a;
}

Rational& Rational::operator++() {
    return *this += Rational(1,1);
}
Rational Rational::operator++(int a) {
    Rational r(*this);
    *this += Rational(1,1);
    return r;
}
Rational& Rational::operator--() {
    return *this -= Rational(1,1);
}
Rational Rational::operator--(int a) {
    Rational r(*this);
    *this-= Rational(1,1);
    return r;
}
bool Rational::operator==(const Rational& rhs) const {
    return (num == rhs.num) && (den == rhs.den);
}
bool Rational::operator!=(const Rational& rhs) const {
    return !(*this == rhs);
}
bool Rational::operator<(const Rational& rhs) const {
    return (num * rhs.den) < (den * rhs.num);
}
bool Rational::operator>(const Rational& rhs) const {
    return (num * rhs.den) > (den * rhs.num);
}
bool Rational::operator<=(const Rational& rhs) const {
    return !((num * rhs.den) > (den * rhs.num));
}
bool Rational::operator>=(const Rational& rhs) const {
    return !((num * rhs.den) < (den * rhs.num));
}
int Rational::GetNum() const {
    return num;
}
int Rational::GetDenom() const {
    return den;
}

void Rational::Normalize() {
    int gc = gcd(num, den);
    num /= gc;
    den /= gc;
    if (den < 0) {
        den *= -1;
        num *= -1;
    }

}
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.GetNum() << "/" << r.GetDenom();
}
