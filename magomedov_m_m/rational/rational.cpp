#include "rational.h"
#include <stdexcept>
#include <iostream>

int gcd(int a, int b) {
	if (b == 0){
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}
Rational::Rational(const Rational& other) {
	*this = other;
}

Rational::Rational()
	:num(0)
	, den(1)
{}
Rational::Rational(const int _num)
	:num(_num)
	, den(1)
{}
Rational::Rational(const int _num, int _den)
	: num(_num)
	, den(_den){
	Check();
	Normal();
}

void Rational::Check() {
	if (den == 0) {
		throw std::invalid_argument("You cannot divide by zero");
	}
	else if (den < 0) {
		num = -num;
		den = -den;
	}
}
void Rational::Normal() {
	int c = gcd(abs(den), num);
	if (c > 1) {
		num /= c;
		den /= c;
	}
}

bool Rational:: operator<(const Rational& rhs) const {
	return (num * rhs.den < den* rhs.num);
}
bool Rational:: operator>(const Rational& rhs) const {
	return (num * rhs.den > den * rhs.num);
}
bool Rational:: operator<=(const Rational& rhs) const {
	return !(*this>rhs);
}
bool Rational:: operator>=(const Rational& rhs) const {
	return !(*this<rhs);
}
bool Rational:: operator==(const Rational& rhs) const {
	return (num * rhs.den == den* rhs.num);
}
bool Rational:: operator!=(const Rational& rhs) const {
	return !(*this==rhs);
}


std::istream& operator>>(std::istream& input, Rational& rhs)
{	char c;
	return input >> rhs.num >> c >> rhs.den;
}
std::ostream& operator<<(std::ostream& output, Rational& rhs)
{
	return output << rhs.num <<"/"<<rhs.den;
}


Rational Rational::operator+(const Rational& rhs) const{
	return Rational(num * rhs.den + rhs.num * den, den * rhs.den);
};
Rational Rational::operator-(const Rational& rhs) const {
	return Rational(num * rhs.den - rhs.num * den, den * rhs.den);
};
Rational Rational::operator*(const Rational& rhs) const {
	return Rational(num * rhs.num, den * rhs.den);
};
Rational Rational::operator/(const Rational& rhs) const {
	if (rhs.num == 0) {
		throw std::invalid_argument("You cannot divide by zero");
	}
	else {
		return Rational(num * rhs.den, den * rhs.num);
	}
};


Rational& Rational::operator+=(const Rational& rhs) {
	*this = *this+rhs;
	return *this;
};
Rational Rational::operator++(int) {
	Rational old(*this);
	num += den;
	return old;
};
Rational Rational::operator--(int) {
	Rational old(*this);
	num -= den;
	return old;
};
Rational& Rational::operator++() {
	num += den;
	return *this;
}
Rational& Rational::operator--() {
	num -= den;
	return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
	*this = *this - rhs;
	return *this;
};
Rational& Rational::operator*=(const Rational& rhs) {
	*this = *this * rhs;
	return *this;
};
Rational& Rational::operator/=(const Rational& rhs) {

	*this = *this / rhs;
	return *this;
};

