#include <cmath>
#include <numeric>
#include <stdexcept>
#include "rational.h"

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
    , denom(1) {
        Normalize();
}
Rational::Rational(int _num, int _denom)
    : num(_num)
    , denom(_denom) {
    if (denom == 0) {
            throw std::invalid_argument("Denominator can not be 0!");
        }
    Normalize();
}
Rational::Rational(const Rational& other)
    : num(other.num)
    , denom(other.denom) {
}
Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.num;
    denom = rhs.denom;
    return *this;
}
Rational& Rational::operator+=(const Rational& rhs){
    num *= rhs.denom;
    num += rhs.num * denom;
    denom *= rhs.denom;
    Normalize();
    return *this;
}
Rational Rational::operator+(const Rational& rhs) const{
    return Rational(*this) += rhs;
}
Rational& Rational::operator-=(const Rational& rhs){
    num *= rhs.denom;
    num -= rhs.num * denom;
    denom *= rhs.denom;
    Normalize();
    return *this;
}
Rational Rational::operator-(const Rational& rhs) const{
    return Rational(*this) -= rhs;
}
Rational& Rational::operator*=(const Rational& rhs){
    num *= rhs.num;
    denom *= rhs.denom;
    Normalize();
    return *this;
}
Rational Rational::operator*(const Rational& rhs) const{
    return Rational(*this) *= rhs;
}
Rational& Rational::operator/=(const Rational& rhs){
    if(rhs.num == 0){
        throw std::domain_error("Division can not be 0!");
    }
    num *= rhs.denom;
    denom *= rhs.num;
    Normalize();
    return *this;
}
Rational Rational::operator/(const Rational& rhs) const{
    return Rational(*this) /= rhs;
}
Rational Rational::operator-() const{
    Rational a(*this);
    a.num *= -1;
    return a;
}
Rational Rational::operator+() const{
    return Rational(*this);
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
    return (num == rhs.num) && (denom == rhs.denom);
}
bool Rational::operator!=(const Rational& rhs) const {
    return !((num == rhs.num) && (denom == rhs.denom));
}
bool Rational::operator<(const Rational& rhs) const {
    return (num * rhs.denom) < (denom * rhs.num);
}
bool Rational::operator>(const Rational& rhs) const {
    return (num * rhs.denom) > (denom * rhs.num);
}
bool Rational::operator<=(const Rational& rhs) const {
    return !((num * rhs.denom) > (denom * rhs.num));
}
bool Rational::operator>=(const Rational& rhs) const {
    return !((num * rhs.denom) < (denom * rhs.num));
}
int Rational::GetNum() const {
    return num;
}
int Rational::GetDenom() const {
    return denom;
}
void Rational::Normalize(){
    int gc = gcd(num, denom);
    num /= gc;
    denom /= gc;
    if (denom < 0) {
    denom *= -1;
    num *= -1;
  }
}
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.GetNum() << "/" << r.GetDenom();
}

