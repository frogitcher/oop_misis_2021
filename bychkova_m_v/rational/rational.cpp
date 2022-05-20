#include "rational.h"
#include <stdexcept>


Rational::Rational(int _num) {
    num = _num;
    den = 1;
}


int gcd(int a, int b) {

	if (b == 0) {
		return a;
	}
	else {
		gcd(b, a%b);
	}
}

void Rational::Normalize() {
	if (den<0) {
		den*=(-1);
		num*=(-1);
	}
	int g = gcd(std::abs(num), den);
	if (g > 1) {
		den/=g;
		num/=g;
	}
}


Rational::Rational(int _num, int _den) {
	num = _num;
	den = _den;
		if (_den == 0) {
			throw std::invalid_argument("Denominator must not be equal 0");
		}
        Normalize();
}

int Rational::GetNumerator() const{
	return num;
}

int Rational::GetDenominator() const{
	return den;
}

Rational::Rational(const Rational& r) {
    num = r.GetNumerator();
    den = r.GetDenominator();
}


Rational Rational::operator+(const Rational& rhs) const{
	int r_den = den*rhs.GetDenominator();
	int r_num = num*rhs.GetDenominator() + rhs.GetNumerator()*den;
	Rational result (r_num, r_den);
	return result;
}

Rational Rational::operator-(const Rational& rhs) const{
	int r_den = den*rhs.GetDenominator();
	int r_num = num*rhs.GetDenominator() - rhs.GetNumerator()*den;
	Rational result (r_num, r_den);
	return result;
}

Rational Rational::operator*(const Rational& rhs) const{
	int r_den = den*rhs.GetDenominator();
	int r_num = num*rhs.GetNumerator();
	Rational result (r_num, r_den);
	return result;
}

Rational Rational::operator/(const Rational& rhs) const{
	int r_den = den*rhs.GetNumerator();
	int r_num = num*rhs.GetDenominator();
	Rational result (r_num, r_den);
	return result;
}

Rational& Rational::operator=(const Rational& rhs) {
	num = rhs.GetNumerator();
	den = rhs.GetDenominator();
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

Rational Rational::operator-()const{
	Rational result(num*(-1), den);
	return result;
}

Rational& Rational::operator++(){
    num+=den;
    return *this;
}

Rational Rational::operator++(int a) {
    Rational result(*this);
    ++(*this);
    return result;
}

bool Rational::operator==(const Rational& rhs) const{
	return num*rhs.GetDenominator() == den*rhs.GetNumerator();
}

bool Rational::operator!=(const Rational& rhs) const{
	return !(*this == rhs);
}

bool Rational::operator>=(const Rational& rhs) const{
	return num*rhs.GetDenominator() >= den*rhs.GetNumerator();
}

bool Rational::operator<(const Rational& rhs) const{
	return !(*this >= rhs);
}

bool Rational::operator<=(const Rational& rhs) const{
	return num*rhs.GetDenominator() <= den*rhs.GetNumerator();
}

bool Rational::operator>(const Rational& rhs) const{
	return !(*this <= rhs);
}

