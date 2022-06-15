#include "RationalNumber.h"
#include <numeric>


void RationalNumber::normalize() {
    if(denom < 0){
        num*=-1;
        denom*=-1;
    }
    int gcd = std::gcd(num, denom);
    num/=gcd;
    denom/=gcd;
}
RationalNumber::RationalNumber(int _num) {
    num = _num;
    denom = 1;
}
RationalNumber::RationalNumber(int _num, int _denom) {
    if (_denom == 0){
        throw std::invalid_argument("Denominator is equal to 0");
    }
    num = _num;
    denom = _denom;
    normalize();
}

RationalNumber::RationalNumber(const RationalNumber &rationalNumber) {
    num = rationalNumber.num;
    denom = rationalNumber.denom;
    normalize();
}

RationalNumber &RationalNumber::operator=(const RationalNumber &rationalNumber) {
    num = rationalNumber.getNum();
    denom = rationalNumber.getDenom();
    return *this;
}

RationalNumber RationalNumber::operator+(const RationalNumber &rationalNumber) const {
    return RationalNumber(*this)+=rationalNumber;
}

RationalNumber RationalNumber::operator-(const RationalNumber &rationalNumber) const {
    return RationalNumber(*this)-=rationalNumber;
}

RationalNumber RationalNumber::operator/(const RationalNumber &rationalNumber) const {
    return RationalNumber(*this)/=rationalNumber;
}

RationalNumber RationalNumber::operator*(const RationalNumber &rationalNumber) const {
    return RationalNumber(*this)*=rationalNumber;
}

RationalNumber &RationalNumber::operator+=(const RationalNumber &rationalNumber) {
    int lcm = std::lcm(denom, rationalNumber.getDenom());
    num = getNum() * (lcm / getDenom()) + rationalNumber.getNum() * (lcm / rationalNumber.getDenom());
    denom = lcm;
    normalize();
    return *this;
}

RationalNumber &RationalNumber::operator-=(const RationalNumber &rationalNumber) {
    int lcm = std::lcm(denom, rationalNumber.getDenom());
    num = getNum() * (lcm / getDenom()) - rationalNumber.getNum() * (lcm / rationalNumber.getDenom());
    denom = lcm;
    normalize();
    return *this;
}

RationalNumber &RationalNumber::operator*=(const RationalNumber &rationalNumber) {
    num *= rationalNumber.getNum();
    denom *= rationalNumber.getDenom();
    normalize();
    return *this;
}

RationalNumber &RationalNumber::operator/=(const RationalNumber &rationalNumber) {
    if (rationalNumber.num == 0){
        throw std::invalid_argument("division by 0");
    }
    num *= rationalNumber.getDenom();
    denom *= rationalNumber.getNum();
    normalize();
    return *this;
}

bool RationalNumber::operator<(const RationalNumber &rationalNumber) const {
    return !(*this >= rationalNumber);
}

bool RationalNumber::operator<=(const RationalNumber &rationalNumber) const {
    return !(*this > rationalNumber);
}

bool RationalNumber::operator>(const RationalNumber &rationalNumber) const {
    return getNum() * rationalNumber.getDenom() > rationalNumber.getNum() * getDenom();
}

bool RationalNumber::operator>=(const RationalNumber &rationalNumber) const {
    return (*this > rationalNumber or *this == rationalNumber);
}

bool RationalNumber::operator==(const RationalNumber &rationalNumber) const {
    return num * rationalNumber.getDenom() == denom * rationalNumber.getNum();
}

bool RationalNumber::operator!=(const RationalNumber &rationalNumber) const {
    return !(*this == rationalNumber);
}

RationalNumber RationalNumber::operator-() {
    RationalNumber newRationalNum = *this;
    newRationalNum.num *=-1;
    return newRationalNum;
}

int RationalNumber::getNum() const {
    return num;
}

int RationalNumber::getDenom() const {
    return denom;
}
std::ostream& operator<<(std::ostream& os, const RationalNumber& rationalNumber) {
    return os << rationalNumber.getNum() << "/" << rationalNumber.getDenom();
}






