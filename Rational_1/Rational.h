#pragma once
#include <ostream>

class Rational {
public:
	Rational() = default;
	~Rational() = default;

	Rational(int _num);
	Rational(int _num, int _den);

	Rational(const Rational& other);

	//Declaration of arithmetic operations
	Rational& operator=(const Rational& rhs);
	Rational operator+(const Rational& rhs) const;
	Rational& operator+=(const Rational& rhs);
	Rational operator-(const Rational& rhs) const;
	Rational& operator-=(const Rational& rhs);
	Rational operator*(const Rational& rhs) const;
	Rational& operator*=(const Rational& rhs);
	Rational operator/(const Rational& rhs) const;
	Rational& operator/=(const Rational& rhs);

	//Declaration of boolean functions
	bool operator<(const Rational& rhs) const;  
	bool operator<=(const Rational& rhs) const; 
	bool operator>(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const; 
	bool operator==(const Rational& rhs) const; 
	bool operator!=(const Rational& rhs) const; 

	//Declaration of unarian operators
	Rational operator-() const;
	Rational operator+() const;
	Rational& operator++();
	Rational operator++(int a);
	Rational& operator--();
	Rational operator--(int a);

	//Declaration of normaliztion
	int GetNum() const;
	int GetDen() const;
private:
	int num, den;
	void Normal();

};
//Declaration of output operator 
std::ostream& operator<<(std::ostream& os, const Rational& r);