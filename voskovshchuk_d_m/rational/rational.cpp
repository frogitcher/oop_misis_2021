#include <iostream>
#include "rational.h"

/*
int main()
{
}
*/


unsigned _int64 findDenum(const double x) {
    int i;
    for (i = 1; (abs(round(x * i) - x * i) > 0.01) && i <= 100; i++);
    return i;
}
unsigned _int64 lcm(_int64 a, _int64 b) {  //least common multiple
    _int64 s = a * b;
    _int64 mi = (a < b ? a : b);
    for (_int64 i = 2; i * i <= mi; i++)
        if (a % i && b % i)
            s /= i--;
    return s;
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
void rational::normal() { //makes it common
    stateCheck();
    _int64 n = (sign == Sign::negative ? gcd(-num, denum) : gcd(num, denum));
    num /= n;
    denum /= n;
    stateCheck();
}
void rational::stateCheck() {
    if (num == 0) {
        Sign sign = Sign::null;
        State state = State::integer;
    }
    else {
        sign = (num > 0 ? Sign::positive : Sign::negative);
        state = (num % denum == 0 ? State::integer : State::real);
    }
}


template<typename Type>
rational::rational(const Type rhs) {
    int inte = rhs / 1;
    double real = rhs - inte;
    denum = (real == 0 ? 1 : findDenum(real));
    num = (int)(round(real / (1.0 / denum)) + inte * denum);
    stateCheck();
}
template rational::rational(const int rhs);
template rational::rational(const double rhs);

rational rational::operator+ (const rational& rhs) const { //plus function
    rational tmp;
    _int64 n = lcm(rhs.denum, denum);
    tmp.denum = n;
    tmp.num = rhs.num * (n / rhs.denum) + num * (n / denum);
    tmp.normal();
    return tmp;
}
rational rational::operator- (const rational& rhs) const { //minus function
    rational tmp;
    _int64 n = lcm(rhs.denum, denum);
    tmp.denum = n;
    tmp.num = num * (n / denum) - rhs.num * (n / rhs.denum);
    tmp.normal();
    return tmp;
}
rational rational::operator* (const rational& rhs) const { // multiplication function
    rational tmp;
    tmp.denum = rhs.denum * denum;
    tmp.num = rhs.num * num;
    tmp.normal();
    return tmp;
}
rational rational::operator/ (const rational& rhs) const { //division function
    if (rhs.sign == Sign::null)
        return NULL;
    rational tmp;
    tmp.num = rhs.denum * num;
    tmp.denum = rhs.num * denum;
    if (rhs.state == State::integer)
        tmp.num %= tmp.denum;
    tmp.normal();
    return tmp;
}
rational rational::operator% (const rational& rhs) const { //reminder of dividon on integer
    if (rhs.state == State::integer) {
        rational tmp;
        tmp.num = num % (rhs.num * denum);
        tmp.denum = denum;
        tmp.normal();
        return tmp;
    }
    else
        return NULL;
}

rational& rational::operator= (const rational& rhs)  {
    num = rhs.num;
    denum = rhs.denum;
    sign = rhs.sign;
    state = rhs.state;
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
rational& rational::operator%= (const rational& rhs) {
    *this = *this % rhs;
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
    return (num == rhs.num && denum == rhs.denum ? 1 : 0);
}


/*
bool operator> (const rational x) {
    if (value > x.value)
        return 1;
    else return 0;
}
bool operator>= (const rational x) {
    if (value >= x.value)
        return 1;
    else return 0;
}
bool operator<= (const rational x) {
    if (value <= x.value)
        return 1;
    else return 0;
}
bool operator< (const rational x) {
    if (value < x.value)
        return 1;
    else return 0;
}
bool operator== (const rational x) {
    if (value == x.value)
        return 1;
    else return 0;
}
*/