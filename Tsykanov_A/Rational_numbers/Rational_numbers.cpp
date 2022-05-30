#include "Rational_numbers.h"
#include <stdexcept>
int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}
int lcm(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    return a * b / gcd(a, b);
}
// Конструкторы 
Rational::Rational(int _num)
 : num(_num),
   den(1)
{
    Normalize();
}
Rational::Rational(int _num, int _den)
	: num(_num)
	, den(_den)
{
    if (den == 0){
        throw std::domain_error("Denominator must not be equal to 0!");
    }
    Normalize();
}
Rational::Rational(const Rational& other) {
	num = other.num;
	den = other.den;
}
// Арифметические операции
Rational& Rational::operator+=(const Rational& rhs){
    int comm_den = lcm(den, rhs.den);
    num *= comm_den / den;
    num += rhs.num * (comm_den / rhs.den);
    den = comm_den;
    Normalize();
    return *this;
}
Rational Rational::operator+(const Rational& rhs) const {
    return Rational(*this) += rhs;
}
Rational& Rational::operator-=(const Rational& rhs){
    int comm_den = lcm(den, rhs.den);
    num *= comm_den / den;
    num -= rhs.num * (comm_den / rhs.den);
    den = comm_den;
    Normalize();
    return *this;
}
Rational Rational::operator-(const Rational& rhs) const {
    return Rational(*this) -= rhs;
}
Rational& Rational::operator*=(const Rational& rhs){
    num *= rhs.num;
    den *= rhs.den;
    Normalize();
    return *this;
}
Rational Rational::operator*(const Rational& rhs) const{
    return Rational(*this) *= rhs;
}
Rational& Rational::operator/=(const Rational& rhs){
    if(rhs == Rational(0)){
        throw std::domain_error("Division by 0!");
    }
    num *= rhs.den;
    den *= rhs.num;
    Normalize();
    return *this;
}
Rational Rational::operator/(const Rational& rhs) const{
    return Rational(*this) /= rhs;
}
// Операции сравнения
bool Rational::operator<(const Rational&  rhs) const{
    return (num * rhs.den) < (den * rhs.num);
};
bool Rational::operator<=(const Rational&  rhs) const{
    return (num * rhs.den) <= (den * rhs.num);
};
bool Rational::operator>=(const Rational&  rhs) const{
    return !(*this < rhs);
};
bool Rational::operator>(const Rational&  rhs) const{
    return !(*this <= rhs);
};
bool Rational::operator==(const Rational& rhs) const{
    return (num == rhs.num) && (den == rhs.den);
};
bool Rational::operator!=(const Rational& rhs) const{
    return !(*this == rhs);
};
Rational& Rational::operator=(const Rational& rhs){
    num = rhs.num;
    den = rhs.den;
    return *this;
}
// Бинарные операции
Rational Rational::operator-() const{
    Rational lhs(*this);
    lhs.num *= -1;
    return lhs;
};
Rational Rational::operator+() const{
    return *this;
};
Rational& Rational::operator++(){
    return *this += Rational(1, 1);
};
Rational Rational::operator++(int number){
    Rational lhs(*this);
    *this += Rational(1, 1);
    return lhs;
};
Rational& Rational::operator--(){
    return *this -= Rational(1, 1);
};
Rational Rational::operator--(int number){
    Rational lhs(*this);
    *this -= Rational(1, 1);
    return lhs;
};
int Rational::GetDenumerator() const{
    return den;
}
int Rational::GetNumerator() const{
    return num;
}
std::ostream& operator<<(std::ostream& os, const Rational& r) {
return os << r.GetNumerator() << "/" << r.GetDenumerator();
}
void Rational::Normalize(){
    if (den < 0){
        den *= -1;
        num *= -1;
    }
    int g = gcd(den, num);
    num /= g;
    den /= g;
}

