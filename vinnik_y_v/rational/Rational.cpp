#include "Rational.h"

Rational::Rational(const int Num, const int Det) : num(Num), det(Det)
{
	if (Det == 0) {
		num = 0;
		det = 1;
	}
	ReduceFraction();
}

bool Rational::operator<(const Rational& other)
{
	return num * other.det < other.num * det;
}

bool Rational::operator>(const Rational& other)
{
	return num * other.det > other.num* det;
}

bool Rational::operator==(const Rational& other)
{
	return num * other.det == other.num* det;
}

Rational Rational::operator-() const
{
	return Rational(-num, det);
}

Rational& Rational::operator=(const Rational& other)
{
	if (this == &other) {
		return *this;
	}

	num = other.num;
	det = other.det;
	return *this;
}

Rational& Rational::operator+=(const Rational& other)
{
	num += other.num;
	det *= other.det;
	ReduceFraction();
	return *this;
}

Rational& Rational::operator+=(const int I)
{
	num += I * det;
	ReduceFraction();
	return *this;
}

Rational& Rational::operator-=(const Rational& other)
{
	num -= other.num;
	det *= other.det;
	ReduceFraction();
	return *this;
}

Rational& Rational::operator-=(const int I)
{
	num -= I * det;
	ReduceFraction();
	return *this;
}

Rational& Rational::operator*=(const Rational& other)
{
	num *= other.num;
	det *= other.det;
	ReduceFraction();
	return *this;
}

Rational& Rational::operator*=(const int I)
{
	num *= I;
	ReduceFraction();
	return *this;
}

Rational& Rational::operator/=(const Rational& other)
{
	num *= other.det;
	det *= other.num;
	ReduceFraction();
	return *this;
}

Rational& Rational::operator/=(const int I)
{
	det *= I;
	ReduceFraction();
	return *this;
}

Rational Rational::operator+(const Rational& other)
{
	return Rational(num * other.det + other.num * det, det * other.det);
}

Rational Rational::operator+(const int I)
{
	return Rational(num + I * det, det);
}

Rational Rational::operator-(const Rational& other)
{
	return Rational(num * other.det - other.num * det, det * other.det);
}

Rational Rational::operator-(const int I)
{
	return Rational(num - I * det, det);
}

Rational Rational::operator*(const Rational& other)
{
	return Rational(num * other.num, det * other.det);
}

Rational Rational::operator*(const int I)
{
	return Rational(num * I, det);
}

Rational Rational::operator/(const Rational& other)
{
	return Rational(num * other.det, det * other.num);
}

Rational Rational::operator/(const int I)
{
	return Rational(num, det * I);
}

Rational::operator double()
{
	return double(num) / double(det);
}

std::pair<int, Rational> Rational::ToProperFraction()
{
	return {num / det, Rational(num % det, det)};
}

void Rational::ReduceFraction()
{
	if (num == 0) {
		det = 1;
		return;
	}
	int _gcd = std::gcd(num, det);
	num /= _gcd;
	det /= _gcd;
}


