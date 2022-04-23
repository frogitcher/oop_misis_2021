#include "rational.h"
#include <stdexcept>
#include <cstdlib>


unsigned _int64 findDenum(const double x) {
    int i;
    for (i = 1; (abs(round(x * i) - x * i) >= 0.05) && i <= 100; i++);
    return i;
}
unsigned _int64 gcd(_int64 a, _int64 b) { //greatest common divisor
    a = abs(a);
    b = abs(b);
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return gcd(a % b, b);
    return gcd(a, b % a);
}
unsigned _int64 lcm(_int64 a, _int64 b) {  //least common multiple
    return a * b / gcd(a, b);
}
void rational::normal() { //makes it common
    _int64 n = gcd(abs(num), denum);
    num /= n;
    denum /= n;
    if ((num > 0 && denum < 0) || (num < 0 && denum > 0)) {
        num = abs(num) * (-1);
        denum = abs(denum);
    }
    else {
        num = abs(num);
        denum = abs(denum);
    }
}

rational::rational(const _int64 x) {
    denum = 1;
    num = x;
    normal();
}
rational::rational(const _int64 x, const _int64 y) {
    if (y == 0)
        throw std::invalid_argument("Denuminator has to be unequal 0");
    denum = y;
    num = x;
    normal();
}
rational::rational(const rational& rhs) {
    num = rhs.num;
    denum = rhs.denum;
}

rational rational::operator+ (const rational& rhs) const { //plus function
    _int64 n = lcm(rhs.denum, denum);
    rational tmp (rhs.num * (n / rhs.denum) + num * (n / denum), n);
    tmp.normal();
    return tmp;
}
rational rational::operator- (const rational& rhs) const { //minus function
    _int64 n = lcm(rhs.denum, denum);
    rational tmp (num * (n / denum) - rhs.num * (n / rhs.denum), n);
    tmp.normal();
    return tmp;
}
rational rational::operator* (const rational& rhs) const { // multiplication function
    rational tmp (rhs.num * num, rhs.denum * denum);
    tmp.normal();
    return tmp;
}
rational rational::operator/ (const rational& rhs) const { //division function
    if (rhs.num == 0)
        throw std::invalid_argument("Divider has to be unequal 0");
    rational tmp (rhs.denum * num - (rhs.denum == 1 ? (rhs.denum * num % rhs.num * denum) : 0), rhs.num* denum);
    tmp.normal();
    return tmp;
}

rational& rational::operator+= (const rational& rhs)  {
    *this = *this + rhs;
    return *this;
}
rational& rational::operator-= (const rational& rhs)  {
    *this = *this - rhs;
    return *this;
}
rational& rational::operator*= (const rational& rhs)  {
    *this = *this * rhs;
    return *this;
}
rational& rational::operator/= (const rational& rhs)  {
    *this = *this / rhs;
    return *this;
}

rational& rational::operator++ () {
    rational tmp(1);
    *this = *this + tmp;
    return *this;
}
rational& rational::operator-- () {
    rational tmp(1);
    *this = *this - tmp;
    return *this;
}
rational rational::operator++ (int) {
    rational tmp1(1);
    rational tmp = *this;
    *this = *this + tmp1;
    return tmp;
}
rational rational::operator-- (int) {
    rational tmp1(1);
    rational tmp = *this;
    *this = *this - tmp1;
    return tmp;
}

bool rational::operator== (const rational& rhs) const {
    return (num == rhs.num && denum == rhs.denum);
}
bool rational::operator> (const rational& rhs) const{
    rational tmp = *this - rhs;
    return (tmp.num > 0);
}
bool rational::operator< (const rational& rhs) const {
    rational tmp = rhs - *this;
    return (tmp.num > 0);
}
bool rational::operator>= (const rational& rhs) const {
    rational tmp = *this - rhs;
    return (tmp.num >= 0);
}
bool rational::operator<= (const rational& rhs) const {
    rational tmp = rhs - *this;
    return (tmp.num >= 0);
}
bool rational::operator!= (const rational& rhs) const {
    return (num != rhs.num || denum != rhs.denum ? 1 : 0);
}
