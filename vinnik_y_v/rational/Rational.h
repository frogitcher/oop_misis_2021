#pragma once
#include <numeric>
#include <iostream>

class Rational
{
public:
	Rational(const int num, const int det);
	Rational(const Rational& other) = default;
	~Rational() = default;

	bool operator< (const Rational& other);
	bool operator> (const Rational& other);
	bool operator== (const Rational& other);

	Rational operator- () const;

	Rational& operator= (const Rational& other);

	Rational& operator+= (const Rational& other);
	Rational& operator+= (const int I);
	Rational& operator-= (const Rational& other);
	Rational& operator-= (const int I);
	Rational& operator*= (const Rational& other);
	Rational& operator*= (const int I);
	Rational& operator/= (const Rational& other);
	Rational& operator/= (const int I);

	Rational operator+ (const Rational& other);
	Rational operator+ (const int I);
	Rational operator- (const Rational& other);
	Rational operator- (const int I);
	Rational operator* (const Rational& other);
	Rational operator* (const int I);
	Rational operator/ (const Rational& other);
	Rational operator/ (const int I);

	operator double();
	std::pair<int, Rational> ToProperFraction();

	int getNum() const { return num; }
	int getDet() const { return det; }
private:
	void ReduceFraction();
private:
	int num;
	int det;
};
