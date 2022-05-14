#pragma once
#include <iosfwd>

class Rational {
public:
	Rational();
	Rational(const int _num);
	Rational(const int _num, const int _denum);
	Rational(const Rational& other);
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

	Rational& operator++(); //++r
	Rational operator++(int); //r++
	Rational& operator--();
	Rational operator--(int);

	Rational operator-() const;

	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;
	bool operator<(const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;

	std::ostream& writeTo(std::ostream& ostrm) const;
	std::istream& readFrom(std::istream& istrm);

private:
	void Check();
	void Normalize();
	int num;
	int denum;
};

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);