#pragma once

class Rational {

public:


	int GetNumerator() const;
	int GetDenominator() const;

	Rational() = default;
	Rational(int _num);
	Rational(int _num, int _den);
	Rational(const Rational& r);

	~Rational() = default;

	Rational operator+(const Rational& rhs) const;
	Rational operator-(const Rational& rhs) const;
	Rational operator*(const Rational& rhs) const;
	Rational operator/(const Rational& rhs) const;

	Rational& operator=(const Rational& rhs);

	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);

	Rational operator-() const;

	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;
	bool operator<(const Rational& rhs) const;

private:
	int num, den;
	void Normalize();
};
