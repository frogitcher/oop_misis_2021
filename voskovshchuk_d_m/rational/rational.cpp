#include "rational.h"
#include <cstdlib>


unsigned _int64 findDenum(const double x) {
    int i;
    for (i = 1; (abs(round(x * i) - x * i) >= 0.05) && i <= 100; i++);
    return i;
}
unsigned _int64 gcd(_int64 a, _int64 b) { //greatest common divisor
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
}

rational::rational(const _int64 x) {
    denum = 1;
    num = x;
}
rational::rational(const _int64 x, const _int64 y) {
    denum = y;
    num = x;
}

rational rational::operator+ (const rational& rhs) const { //plus function
    _int64 n = lcm(rhs.denum, denum);
    return rational(rhs.num * (n / rhs.denum) + num * (n / denum), n);
}
rational rational::operator- (const rational& rhs) const { //minus function
    _int64 n = lcm(rhs.denum, denum);
    return rational(rhs.num * (n / rhs.denum) - num * (n / denum), n);
}
rational rational::operator* (const rational& rhs) const { // multiplication function
    return rational(rhs.num * num, rhs.denum * denum);
}
rational rational::operator/ (const rational& rhs) const { //division function
    if (rhs == 0)
        return NULL;
    return rational(rhs.denum * num - (rhs.denum == 1 ? (rhs.denum * num % rhs.num * denum) : 0), rhs.num * denum);
}

rational& rational::operator= (const rational& rhs)  {
    num = rhs.num;
    denum = rhs.denum;
    return *this;
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
    *this = *this + 1;
    return *this;
}
rational& rational::operator-- () {
    *this = *this - 1;
    return *this;
}
rational rational::operator++ (int) {
    rational tmp = *this;
    *this = *this + 1;
    return tmp;
}
rational rational::operator-- (int) {
    rational tmp = *this;
    *this = *this - 1;
    return tmp;
}

bool rational::operator== (const rational& rhs) const {
    return (num == rhs.num && denum == rhs.denum);
}
bool rational::operator> (const rational& rhs) const{
    rational tmp = *this - rhs;
    return (tmp > 0);
}
bool rational::operator< (const rational& rhs) const {
    rational tmp = rhs - *this;
    return (tmp < 0);
}
bool rational::operator>= (const rational& rhs) const {
    rational tmp = *this - rhs;
    return (tmp >= 0);
}
bool rational::operator<= (const rational& rhs) const {
    rational tmp = rhs - *this;
    return (tmp <= 0);
}
bool rational::operator!= (const rational& rhs) const {
    return (num != rhs.num || denum != rhs.denum ? 1 : 0);
}
