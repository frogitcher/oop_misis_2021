#pragma once
#include <iostream>

int gcd(int a, int b);

class Rational {

public:
	Rational() = default;
	~Rational() = default;
	Rational(int _num);
	Rational(const int _num,const int _den);
	Rational (const Rational& other);
	
	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;
	bool operator<(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;
	bool operator<= (const Rational & rhs) const;
	
	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational & rhs);

	Rational operator+(const Rational& rhs) const;
	Rational operator-(const Rational& rhs) const;
	Rational operator*(const Rational& rhs) const;
	Rational operator/(const Rational& rhs) const;

	Rational& operator++();
	Rational& operator--();
	Rational operator++(int a);
	Rational operator--(int a);

private:
	int num, den;
	Rational& Normalize();
};




