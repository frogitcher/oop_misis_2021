#pragma once
#include <iostream>
class Rational {
public:
	Rational();
	~Rational() = default;
	Rational(const int _num);
	Rational(const int _num, const int _den);
	Rational(const Rational& other);

	Rational operator+(const Rational& rhs) const;
	Rational operator*(const Rational& rhs) const;
	Rational operator-(const Rational& rhs) const;
	Rational operator/(const Rational& rhs) const;

	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);

	Rational operator++(int);
	Rational operator--(int);
	Rational& operator++();
	Rational& operator--();


	bool operator<(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;
	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;

public:
	int num, den;
	void Check();
	void Normal();

};

std::istream& operator>>(std::istream& input, Rational& rhs);

std::ostream& operator<<(std::ostream& output, const Rational& rhs);