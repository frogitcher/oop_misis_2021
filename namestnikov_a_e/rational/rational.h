#pragma once
//#include <ostream>

class Rational {
public:
	Rational() = default;
	Rational(int _num);
	Rational(int _num, int _den);
	Rational(const Rational& other);
	~Rational() = default;
	
	Rational& operator=(const Rational& rhs);

	Rational operator+(const Rational& rhs) const;
	Rational operator-(const Rational& rhs) const;
	Rational operator*(const Rational& rhs) const;
	Rational operator/(const Rational& rhs) const;
	
	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);

	bool operator<(const Rational& rhs) const;
	bool operator<=(const Rational& rhs) const;
	bool operator>(const Rational& rhs) const;
	bool operator>=(const Rational& rhs) const;

	bool operator==(const Rational& rhs) const;
	bool operator!=(const Rational& rhs) const;

	//инвариант:
	// den != 0
	// несокращаемая дробь

	int GetNumerator() const;
	int GetDenominator() const;
	
private:
	int num, den;
	void Normalize();
};

//std::ostream& operator<<(std::ostream& os, const Rational& r);