#pragma once

int gcd(int a, int b);
int lcd(int a, int b);

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

	Rational operator+(const Rational& rhs);
	Rational operator-(const Rational& rhs);
	Rational operator*(const Rational& rhs);
	Rational operator/(const Rational& rhs);

	Rational& operator++();
	Rational& operator--();

private:
	int num, den;
	Rational& Normalize();
};




