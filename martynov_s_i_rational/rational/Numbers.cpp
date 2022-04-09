#include "Numbers.h"
#include <stdlib.h>

void Rational::check_zero() {
	if (den == 0) {
		throw "denominator - 0";
	}
}
int make_nod(int a, int b) {
	if (a % b == 0)
		return b;
	if (b % a == 0)
		return a;
	if (a > b)
		return make_nod(a % b, b);
	return make_nod(a, b % a);
}
void Rational::make_simple() {
	int nod = make_nod(abs(num), abs(den));
	num /= nod;
	den /= nod;
	if (num < 0 && den < 0) {
		num *= -1;
		den *= -1;
	}
	if (den < 0) {
		num *= -1;
		den *= -1;
	}
}

//конструкторы
Rational::Rational() {
	num = 0;
	den = 1;
}
Rational::Rational(int numerator) {
	num = numerator;
	den = 1;
}
Rational::Rational(int numumerator, int denominator) {
	num = numumerator;
	den = denominator;
	check_zero();
	make_simple();
}
Rational::~Rational() = default;

//"+"
Rational Rational::operator+(const Rational& num2) const {
	return Rational(num * num2.den  + num2.num * den, den * num2.den);
}

//"-"
Rational Rational::operator-(const Rational& num2) const {
	return Rational(num * num2.den - num2.num * den, den * num2.den);
}

//"*"
Rational Rational::operator*(const Rational& num2) const {
	return Rational(num * num2.num, den * num2.den);
}

//"/"
Rational Rational::operator/(const Rational& num2) const {
	return Rational(num * num2.den, den * num2.num);
}

//"="
Rational Rational::operator=(const Rational& num2) {
	num = num2.num;
	den = num2.den;
	return *this;
}

//"+="
Rational Rational::operator+=(const Rational& num2) {
	*this = *this + num2;
	return *this;
}

//"-="
Rational Rational::operator-=(const Rational& num2) {
	*this = *this - num2;
	return *this;
}

//"*="
Rational Rational::operator*=(const Rational& num2) {
	*this = *this * num2;
	return *this;
}

//"/="
Rational Rational::operator/=(const Rational& num2) {
	*this = *this / num2;
	return *this;
}

//"++x"
Rational Rational::operator++() {
	*this += 1;
	return *this;
}

//"x++"
Rational Rational::operator++(const int num2) {
	Rational temp = *this;
	++(*this);
	return temp;
}

//"--x"
Rational Rational::operator--() {
	*this -= 1;
	return *this;
}

//"x--"
Rational Rational::operator--(const int num2) {
	Rational temp = *this;
	--(* this);
	return temp;
}

Rational Rational::operator-() {
	num *= -1;
	return *this;
}

Rational Rational::operator+() const{
	return *this;
}

//"=="
bool Rational::operator==(const Rational& num2) const {
	return (num == num2.num && den == num2.den);
}

//"!="
bool Rational::operator!=(const Rational& num2) const {
	return !(*this == num2);
}

//">"
bool Rational::operator>(const Rational& num2) const {
	return (num * num2.den > num2.num * den);
}

//"<"
bool Rational::operator<(const Rational& num2) const {
	return !(*this > num2 || *this == num2);
}

//">="
bool Rational::operator>=(const Rational& num2) const {
	return !(*this < num2);
}

//"<="
bool Rational::operator<=(const Rational& num2) const {
	return !(*this > num2);
}