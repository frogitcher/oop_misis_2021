#pragma once

class Rational {
	Rational() = default;
	Rational(int _num);
	Rational(int _num, int _den);
	Rational(const Rational& other);
	~Rational() = default;

	Rational& operator=(const Rational& rhs);

	Rational operator+(const Rational& rhs) const;//константный метод // а еще -, *, /
	Rational operator-(const Rational& rhs) const;
	Rational operator*(const Rational& rhs) const;
	Rational operator/(const Rational& rhs) const;

	Rational& operator+=(const Rational& rhs); //-=, *=, /=
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);

	Rational operator-() const; //унарные операторы
	Rational operator+() const;
	
	//изменить 5/-2 на -5/2

	//инвариант:
	// 1. den!=0
	// 2. несокращ€ема€ дробь

	bool operator<(const Rational& rhs) const; //true if *this<rhs // <=, >, >=
	bool operator>(const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;

	bool operator==(const Rational& rhs) const; // !=
	bool operator!=(const Rational& rhs) const;

	Rational operator++() const; //++a
	Rational& operator++(); //a++ // --, --;
	Rational operator--() const;
	Rational& operator--();

	int getNum() const;
	int getDen() const;
	void setNum(int _num);
	void setDen(int _den);
private:
	int num, den;
	void normalize();
};