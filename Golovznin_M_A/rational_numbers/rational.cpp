#include "rational.h"
#include <stdexcept>
#include <numeric>

//конструкторы

Rational::Rational(int _num) : num(_num), denum(1) {}

Rational::Rational(int _num, int _denum) : num(_num), denum(_denum) {
    if (denum == 0) {
        throw std::invalid_argument("denominator must not be equal to 0");
    }
    Normalize();
}

Rational::Rational(const Rational &other) : num(other.GetNum()), denum(other.GetDenum()) {}

//присвоение

Rational &Rational::operator=(const Rational &rhs) {
    num = rhs.GetNum();
    denum = rhs.GetDenum();
    return *this;
}

//арифметические действия

Rational Rational::operator+(const Rational &rhs) {
    return Rational(*this) += rhs;
}

Rational Rational::operator-(const Rational &rhs) {
    return Rational(*this) -= rhs;
}

Rational Rational::operator*(const Rational &rhs) {
    return Rational(*this) *= rhs;
}

Rational Rational::operator/(const Rational &rhs) {
    return Rational(*this) /= rhs;
}

//арифметические действия + =

Rational &Rational::operator+=(const Rational &rhs) {
    int common = std::lcm(GetDenum(), rhs.GetDenum());

    int num_1 = GetNum() * (common / GetDenum());
    int num_2 = rhs.GetNum() * (common / rhs.GetDenum());

    Rational result = Rational(num_1 + num_2, common);
    result.Normalize();
    *this = result;

    return *this;
}

Rational &Rational::operator-=(const Rational &rhs) {
    int common = std::lcm(GetDenum(), rhs.GetDenum());

    int num_1 = GetNum() * (common / GetDenum());
    int num_2 = rhs.GetNum() * (common / rhs.GetDenum());

    Rational result = Rational(num_1 - num_2, common);
    result.Normalize();
    *this = result;

    return *this;
}

Rational &Rational::operator*=(const Rational &rhs) {
    Rational result = Rational(GetNum() * rhs.GetNum(), GetDenum() * rhs.GetDenum());
    result.Normalize();
    *this = result;

    return *this;
}

Rational &Rational::operator/=(const Rational &rhs) {
    Rational result = Rational(GetNum() * rhs.GetDenum(), GetDenum() * rhs.GetNum());
    result.Normalize();
    *this = result;

    return *this;
}

//знак

Rational Rational::operator-() {
    num *= -1;
    return *this;
}

Rational Rational::operator+() {
    return *this;
}

//инкремент, декремент

Rational Rational::operator++(int a) {
    Rational result(*this);
    *this += Rational(1);

    return result;
}

Rational &Rational::operator++() {
    return *this += Rational(1);
}

Rational Rational::operator--(int a) {
    Rational result(*this);
    *this -= Rational(1);

    return result;
}

Rational &Rational::operator--() {
    return *this -= Rational(1);
}


//сравнение

bool Rational::operator<(const Rational &rhs) const {
    return num * rhs.denum < rhs.num * denum;
}

bool Rational::operator<=(const Rational &rhs) const {
    return num * rhs.denum <= rhs.num * denum;
}

bool Rational::operator>(const Rational &rhs) const {
    return num * rhs.denum > rhs.num * denum;
}

bool Rational::operator>=(const Rational &rhs) const {
    return num * rhs.denum >= rhs.num * denum;
}

bool Rational::operator==(const Rational &rhs) const {
    return (GetNum() == rhs.GetNum()) && (GetDenum() == rhs.GetDenum());
}

bool Rational::operator!=(const Rational &rhs) const {
    return !(*this == rhs);
}


int Rational::GetNum() const {
    return num;
}

int Rational::GetDenum() const {
    return denum;
}

void Rational::Normalize() {
    int g = std::gcd(abs(num), denum);
    num /= g;
    denum /= g;

    if(denum < 0) {
        denum *= -1;
        num *= -1;
    }
}
