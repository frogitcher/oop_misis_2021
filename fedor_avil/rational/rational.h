#pragma once

class Rational {
public:
	Rational() = default;
	Rational(int _num);
	Rational(int _num, int _den);	
	Rational(const Rational& other);
	Rational& operator=(const Rational& rhs);
	Rational operator+(const Rational& rhs) const;
	Rational& operator+=(const Rational& rhs);
	Rational operator-(const Rational& rhs) const;
	Rational& operator-=(const Rational& rhs);
	Rational operator*(const Rational& rhs) const;
	Rational& operator*=(const Rational& rhs);
	Rational operator/(const Rational& rhs) const;
	Rational& operator/=(const Rational& rhs);
	bool operator<(const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;
	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;
	~Rational() = default;
	int GetNum() const;
	int GetDen() const;
private:
	int num, den;
	void Normal();
};
