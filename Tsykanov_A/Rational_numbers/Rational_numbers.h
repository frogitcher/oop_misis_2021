#pragma once
#include <iostream>
class Rational {
public:
	// Конструкторы
	Rational() = default;
	Rational(int _num);
	Rational(int _num, int _den);
	Rational(const Rational& other);
	~Rational() = default;
	// Арифметические операции
	Rational& operator+=(const Rational& rhs);
	Rational operator+(const Rational& rhs) const;
	Rational& operator-=(const Rational& rhs);
	Rational operator-(const Rational& rhs) const;
	Rational& operator*=(const Rational& rhs);
	Rational operator*(const Rational& rhs) const;
	Rational& operator/=(const Rational& rhs);
	Rational operator/(const Rational& rhs) const;
	// Операции сравнения
	bool operator<(const Rational&  rhs) const;
	bool operator<=(const Rational&  rhs) const;
	bool operator>=(const Rational&  rhs) const;
	bool operator>(const Rational&  rhs) const;
	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs)const;
	Rational& operator=(const Rational& rhs) ;
	// Бинарные операции
	Rational operator-() const;
	Rational operator+() const;
	Rational& operator++();
	Rational operator++(int number);
	Rational& operator--();
	Rational operator--(int number);
	int GetNumerator() const;
	int GetDenumerator() const;
private:
	int num, den;
	void Normalize();
};
std::ostream& operator<<(std::ostream& os, const Rational& r);