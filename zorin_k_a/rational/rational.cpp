#include "rational.h"
#include <stdexcept>
#include <algorithm>
#include <numeric>


Rational::Rational(int _num)
    : num(_num)
    , den(1)
{
        Normalize();
}
Rational::Rational(int _num,int _den)
    : num(_num)
    , den(_den){
    if (den==0)
    {
        throw std::invalid_argument("denominator must not be equal to 0");
    }
    Normalize();
}
Rational::Rational(const Rational &other)

    :num(other.GetNumerator())
    ,den(other.GetDenumerator()){

    Normalize();
}
int gcd (int a, int b) { return b ? a : gcd(b, a % b) ; }



Rational& Rational::operator+=(const Rational&rhs)
{
    int _den=(int)this->den*rhs.den;
    int _num=(int)this->num*rhs.den+(int)rhs.num*this->den;
    int d=gcd(_den,_num);
    _num/=d;
    _den/=d;
    den=(int)_den;
    num=(int)_num;
    return *this;
}
Rational& Rational::operator-=(const Rational&rhs)
{
    int _den=(int)this->den*rhs.den;
    int _num=(int)this->num*rhs.den-(int)rhs.num*this->den;
    int d=gcd(_den,_num);
    _num/=d;
    _den/=d;
    den=(int)_den;
    num=(int)_num;
    return *this;

}
Rational& Rational::operator*=(const Rational& rhs) {
    num *= rhs.num;
    den *= rhs.den;
    Normalize();
    return *this;
}
Rational Rational::operator+(const Rational& rhs)
{
    Rational r(*this);
    return r+=rhs;
}
Rational Rational::operator*(const Rational& rhs) const {
    return Rational(*this) *= rhs;
}
Rational Rational::operator-(const Rational& rhs)
{
    Rational r(*this);
    return r-=rhs;
}
Rational& Rational::operator++() {
    return *this += 1;
}
Rational Rational::operator++(int a) {
    Rational r(*this);
    *this += 1;
    return r;
}
Rational Rational::operator--(int a) {
    Rational r(*this);
    *this -= 1;
    return r;
}
Rational& Rational::operator--() {
    return *this -= 1;
}

bool Rational::operator<(const Rational& rhs)const {
    return num * rhs.den< rhs.num;
}
bool Rational::operator>(const Rational& rhs)const {
    return num * rhs.den> rhs.num;
}
bool Rational::operator==(const Rational& rhs) const
{
    return (num==rhs.num)&&(den==rhs.den);
}
bool Rational::operator!=(const Rational& rhs) const
{
    return (num!=rhs.num)||(den!=rhs.den);
}
bool Rational::operator<=(const Rational& rhs) const {
    return !(*this > rhs);}
bool Rational::operator>=(const Rational& rhs) const {
    return !(*this < rhs);
}
int Rational::GetNumerator() const {
    return num;
}
int Rational::GetDenumerator() const {
    return den;
}
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.GetNumerator() << "/" << r.GetDenumerator();
}

void Rational::Normalize()
    {
        if (den < 0)
        {
        num *= -1;
        den *= -1;
        }
        int g=gcd(abs(num),den);
        num/=g;
        den/=g;
    }






