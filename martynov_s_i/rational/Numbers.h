#pragma once
class Rational {
public:
	Rational();
	Rational(int numerator);
	Rational(int numerator, int denominator);
	~Rational();

	//"+"
	Rational operator+(const Rational& rhs) const;

	//"-"
	Rational operator-(const Rational& rhs) const;
	
	//"*"
	Rational operator*(const Rational& rhs) const;

	//"/"
	Rational operator/(const Rational& rhs) const;

	//"="
	Rational operator=(const Rational& rhs);

	//"+="
	Rational operator+=(const Rational& rhs);

	//"-="
	Rational operator-=(const Rational& rhs);

	//"*="
	Rational operator*=(const Rational& rhs);

	//"/="
	Rational operator/=(const Rational& rhs);

	//"++x"
	Rational operator++();

	//"x++"
	Rational operator++(const int);

	//"--x"
	Rational operator--();

	//"x--"
	Rational operator--(const int);

	//"-x"
	Rational operator-();

	//"+x"
	Rational operator+() const;

	//"=="
	bool operator==(const Rational& rhs) const;

	//"!="
	bool operator!=(const Rational& rhs) const;

	//">"
	bool operator>(const Rational& rhs) const;

	//"<"
	bool operator<(const Rational& rhs) const;

	//">="
	bool operator>=(const Rational& rhs) const;

	//"<="
	bool operator<=(const Rational& rhs) const;
private:
	int num, den;
	void check_zero();
	void make_simple();
};