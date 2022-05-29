#pragma once

class Rational {
public:
	Rational() = default;
	Rational(int _num, int _den = 1);
	Rational(const Rational& other) = default;
	Rational& operator=(const Rational& rhs) = default;
	~Rational() = default;

	Rational operator+(const Rational& rhs) const;
	Rational operator-(const Rational& rhs) const;
	Rational operator*(const Rational& rhs) const;
	Rational operator/(const Rational& rhs) const;

	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);

	Rational operator-() const;

	bool operator<(const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;
	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;

	Rational& operator++();
	Rational operator++(int a);
	Rational& operator--();
	Rational operator--(int a);

	int getnumerator() const;
	int getdenumerator() const;

private:
	int num, den;
	void Normalize();
};

