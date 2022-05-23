#include "rational.h"
#include <iostream>
#include <stdexcept>

Rational::Rational()
    : num(0)
    , denum(1)
{}

Rational::Rational(const int _num, const int _denum)
    : num(_num)
    , denum(_denum) {
    Check();
    Normalize();
}

Rational::Rational(const int _num)
    : num(_num)
    , denum(1) {
}

Rational::Rational(const Rational& other)
    : num(other.num)
    , denum(other.denum)
{}

void Rational::Check() {
    if (denum < 0) {
        num = -num;
        denum = -denum;
    }
    else if (denum == 0) {
        throw std::invalid_argument("You cannot divide by zero");
    }
}

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

void Rational::Normalize() {
    int g = gcd(std::abs(num), denum);
    num /= g;
    denum /= g;
}

Rational Rational::operator+(const Rational& rhs) const {
    return Rational(num * rhs.denum + rhs.num * denum, denum * rhs.denum);
}
Rational Rational::operator-(const Rational& rhs) const {
    return Rational(num * rhs.denum - rhs.num * denum, denum * rhs.denum);
}
Rational Rational::operator*(const Rational& rhs) const {
    return Rational(num * rhs.num, denum * rhs.denum);
}
Rational Rational::operator/(const Rational& rhs) const {
    if (rhs.num != 0) {
        return Rational(num * rhs.denum, rhs.num * denum);
    }
    else {
        throw std::invalid_argument("You cannot divide by zero");
    }
}

Rational& Rational::operator=(const Rational& rhs){
    num = rhs.num;
    denum = rhs.denum;
    return *this;
}
Rational& Rational::operator+=(const Rational& rhs) {
    *this = *this + rhs;
    return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
    *this = *this - rhs;
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
    *this = *this * rhs;
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
    *this = *this / rhs;
    return *this;
}

Rational& Rational::operator++(){
    num += denum;
    return *this;
}
Rational Rational::operator++(int) {
    Rational temp(*this);
    ++(*this);
    return temp;
}
Rational& Rational::operator--() {
    num -= denum;
    return *this;
}
Rational Rational::operator--(int) {
    Rational temp(*this);
    --(*this);
    return temp;
}

Rational Rational::operator-() const {
    return Rational(-num, denum);
}

bool Rational::operator==(const Rational& rhs) const { return num * rhs.denum == rhs.num * denum; }
bool Rational::operator!=(const Rational& rhs) const { return !operator==(rhs); }
bool Rational::operator>(const Rational& rhs) const { return num * rhs.denum > denum * rhs.num; }
bool Rational::operator>=(const Rational& rhs) const { return num * rhs.denum >= denum * rhs.num; }
bool Rational::operator<(const Rational& rhs) const { return !(*this >= rhs); }
bool Rational::operator<=(const Rational& rhs) const { return !(*this > rhs); }

std::ostream& Rational::writeTo(std::ostream& ostrm) const {
    ostrm << num << "/" << denum;
    return ostrm;
}
    
std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
    return rhs.writeTo(ostrm);
}

std::istream& Rational::readFrom(std::istream& istrm) {
    char slash(0);
    int _num(1);
    int _denum(1);
    istrm >> _num >> slash >> _denum;
    if (istrm && slash == '/') {
        num = _num;
        denum = _denum;
        Check();
        Normalize();
    }
    else {
        istrm.setstate(std::ios_base::failbit);
    }
    return istrm;
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) {
    return rhs.readFrom(istrm);
}