#include "Rational.h"

Rational::Rational(const int Num, const int Det) : num(Num), det(Det)
{
	ReduceFraction();
}

Rational::Rational(int I)
{
	num = I;
	det = 1;
}

bool Rational::operator<(const Rational& other) const
{
	return num * other.det < other.num * det;
}

bool Rational::operator>(const Rational& other) const
{
	return num * other.det > other.num* det;
}

bool Rational::operator==(const Rational& other) const
{
	return num * other.det == other.num* det;
}

bool Rational::operator>=(const Rational& other) const
{
	return !(*this < other);
}

bool Rational::operator<=(const Rational& other) const
{
	return !(*this > other);
}

bool Rational::operator!=(const Rational& other) const
{
	return !(*this == other);
}

bool Rational::operator!() const
{
	return !num;
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
	num = other.num * det + num * other.det;
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
	num = num * other.det - other.num * det;
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

Rational Rational::operator+(const Rational& other) const
{
	return Rational(*this) += other;
}

Rational Rational::operator+(const int I) const
{
	return Rational(*this) += I;
}

Rational Rational::operator-(const Rational& other) const
{
	return Rational(*this) -= other;
}

Rational Rational::operator-(const int I) const
{
	return Rational(*this) -= I;
}

Rational Rational::operator*(const Rational& other) const
{
	return Rational(*this) *= other;
}

Rational Rational::operator*(const int I) const
{
	return Rational(*this) *= I;
}

Rational Rational::operator/(const Rational& other) const
{
	return Rational(*this) /= other;
}

Rational Rational::operator/(const int I) const
{
	return Rational(*this) /= I;
}

Rational& Rational::operator++() {
	*this += 1;
	return *this;
}

Rational Rational::operator++(int I) {
	Rational r(*this);
	*this += 1;
	return r;
}

Rational& Rational::operator--() {
	*this -= 1;
	return *this;
}

Rational Rational::operator--(int I) {
	Rational r(*this);
	*this -= 1;
	return r;
}

/*
std::ostream& Rational::operator<<(std::ostream& os)
{
	os << std::to_string(num) << "/" << std::to_string(det);
	return os;
}
*/

Rational::operator double() const
{
	return double(num) / double(det);
}

std::pair<int, Rational> Rational::ToProperFraction()
{
	return {num / det, Rational(num % det, det)};
}

void Rational::NormalizeSign()
{
	if (det < 0) {
		num = -num;
		det = -det;
	}
}

void Rational::ReduceFraction()
{
	if (det == 0) {
		throw std::invalid_argument("Denominator cannot be equal to 0");
	}
	if (num == 0) {
		det = 1;
		return;
	}
	NormalizeSign();
	int _gcd = std::gcd(num, det);
	num /= _gcd;
	det /= _gcd;
}


