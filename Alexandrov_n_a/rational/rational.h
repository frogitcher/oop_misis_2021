#pragma once
#include <iostream>
class rational {
	int num;
	int denom;
	void normalize();
public:
	rational() = default;
	~rational() = default;
	rational(int n, int d);
	int numerator() const { return num; }
	int denominator() const { return denom; }
	rational& reduce();
	bool operator< (const rational& r) const;
	bool operator<= (const rational& r) const;
	bool operator> (const rational& r) const;
	bool operator>= (const rational& r) const;
	bool operator== (const rational& r) const;
	bool operator!= (const rational& r) const;

	rational operator+ (const rational& r) const;
	rational operator- (const rational& r) const;
	rational operator/ (const rational& r) const;
	rational operator* (const rational& r) const;

	rational& operator+= (const rational& r);
	rational& operator-= (const rational& r);
	rational& operator*= (const rational& r);
	rational& operator/= (const rational& r);

	rational& operator++ ();
	rational operator-- ();
	rational& operator++ (int r);
	rational operator-- (int r);

	rational& operator= (const rational& rhs);
};