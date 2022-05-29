#pragma once
#include <ostream>

class Rational {
public:
	Rational() = default;
	Rational(int numm, int denn);
	Rational(int numm);
	~Rational() = default;
	Rational(const Rational& other);

	Rational operator*(const Rational& rhs) const;
	Rational operator/(const Rational& rhs) const;
	Rational operator+(const Rational& rhs) const;
	Rational operator-(const Rational& rhs) const;

	Rational& operator=(const Rational& rhs);
	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);

	bool operator<(const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;

	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;

	int GetNumerator() const;
	int GetDenominator() const;
private:
	void Normalize();
	int num, den;
};

std::ostream& operator<<(std::ostream& os, const Rational& r);
