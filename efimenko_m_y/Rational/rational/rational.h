#pragma once
#include <iosfwd>

class Rational {
public:
	Rational() = default;
	Rational(int _num);
	Rational(int _num, int _den);
	Rational(const Rational& other);
	~Rational() = default;

	Rational operator + (const Rational& rhs) const;
	Rational operator - (const Rational& rhs) const;
	Rational operator * (const Rational& rhs) const;
	Rational operator / (const Rational& rhs) const;

	Rational& operator=(const Rational& rhs);
	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator *=(const Rational& rhs);
	Rational& operator /=(const Rational& rhs);

	//унарные
	Rational operator +() const;
	Rational operator - () const;
	Rational operator++();//префиксный
	Rational& operator++(int);//постфиксный
	Rational operator--();
	Rational& operator--(int);


	bool operator< (const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;
	bool operator==(const Rational& rhs) const;
	bool operator != (const Rational& rhs) const;

	friend std::istream& operator>>(std::istream& in, Rational& value);
	friend std::ostream& operator<<(std::ostream& out, const Rational& value);

	int getnumerator();
	int getdenominator();

private:
	int num, den;
	void Normalize();
};
