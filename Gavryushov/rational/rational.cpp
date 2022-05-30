#include "rational.h"
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <iostream>

Rational::Rational(int _num)
	: num(_num)
	, den(1)
{}

Rational::Rational(int _num, int _den)
	: num(_num)
	, den(_den) {
		if (den==0) {
			throw std::invalid_argument("denominator must not be equal to 0");
		}
		Normalize();
	}

Rational::Rational(const Rational& other)
	: num(other.num)
	, den(other.den)
{}
Rational& Rational::operator=(const Rational& rhs){
	num = rhs.num;
	den = rhs.den;
	return *this;
}

Rational Rational::operator+(const Rational& rhs) const {
	return Rational(*this) += rhs;
}

Rational Rational::operator-(const Rational& rhs) const{
	return Rational(*this) -= rhs;
}

Rational Rational::operator*(const Rational& rhs) const{
	return Rational(*this) *= rhs;
}

Rational Rational::operator/(const Rational& rhs) const{
	return Rational(*this) /= rhs;
}

Rational Rational::operator+(){
	return Rational(*this);
}

Rational Rational::operator-(){
	return Rational(*this)*Rational(-1);
}



Rational& Rational::operator+=(const Rational& rhs) {
	int common = std::lcm(den,rhs.den);
	num = num * (common / den) + rhs.num * (common / rhs.den);
	den = common;
	Normalize();
	return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
	int common = std::lcm(den,rhs.den);
	num = num * (common / den) - rhs.num * (common / rhs.den);
	den = common;
	Normalize();
	return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
	num *= rhs.num;
	den *= rhs.den;
	Normalize();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs.num==0){
		throw std::invalid_argument("Dividing by zero is impossible");
	}
	num *= rhs.den;
	den *= rhs.num;
	Normalize();
	return *this;
}

bool Rational::operator<(const Rational& rhs) const {
	return num * rhs.den < rhs.num * den;
}

bool Rational::operator>(const Rational& rhs) const {
	return num * rhs.den > rhs.num * den;
}

bool Rational::operator<=(const Rational& rhs) const {
	return num * rhs.den <= rhs.num * den;
}

bool Rational::operator>=(const Rational& rhs) const {
	return num * rhs.den >= rhs.num * den;
}

bool Rational::operator!=(const Rational& rhs) const {
	return num * rhs.den != rhs.num * den;
}

bool Rational::operator==(const Rational& rhs) const {
	return num * rhs.den == rhs.num * den;
}

Rational& Rational::operator++(){
	return *this +=Rational(1);
}

Rational Rational::operator++(int a){
	*this += Rational(1);
	return *this-Rational(1);
}

Rational& Rational::operator--(){
	return *this -=Rational(1);
}

Rational Rational::operator--(int){
	*this -= Rational(1);
	return *this+Rational(1);
}

void Rational::Normalize() {
	int g=std:: gcd (abs(num),den);
	num/=g;
	den/=g;
	if (den<0){
		num= -num;
		den = -den;
	}
}

int Rational::GetNumerator() const{
	return num;
}

int Rational::GetDenominator() const{
	return den;
}

std::ostream& operator<<(std::ostream& os, const Rational& x){
	return os << x.GetNumerator() << "/" << x.GetDenominator();
}