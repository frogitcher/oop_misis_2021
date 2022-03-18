#pragma once
#include <numeric>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>

class Rational
{
public:
	Rational(const int num, const int det);
	Rational(int I);
	Rational(const Rational& other) = default;
	~Rational() = default;

	bool operator< (const Rational& other) const;
	bool operator> (const Rational& other) const;
	bool operator== (const Rational& other) const;
	bool operator>= (const Rational & other) const;
	bool operator<= (const Rational& other) const;
	bool operator!= (const Rational& other) const;

	bool operator! () const;
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

	Rational operator+ (const Rational& other) const;
	Rational operator+ (const int I) const;
	Rational operator- (const Rational& other) const;
	Rational operator- (const int I) const;
	Rational operator* (const Rational& other) const;
	Rational operator* (const int I) const;
	Rational operator/ (const Rational& other) const;
	Rational operator/ (const int I) const;

	Rational& operator++();
	Rational operator++(int I);
	Rational& operator--();
	Rational operator--(int I);

	operator double() const;
	std::pair<int, Rational> ToProperFraction();

	int getNum() const { return num; }
	int getDet() const { return det; }
private:
	void NormalizeSign();
	void ReduceFraction();
private:
	int num;
	int det;
};
