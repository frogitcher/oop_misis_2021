#pragma once
class Rational{
	public:
	    Rational();
	    Rational(int _n);
	    Rational(int _n, int _d);
	    ~Rational() = default;
	
	    d_zero();
	
	    bool operator==(const Rational& rhs) const;
	    bool operator!=(const Rational& rhs) const;
	    bool operator<(const Rational& rhs) const;
	    bool operator>(const Rational& rhs) const;
	    bool operator>=(const Rational& rhs) const;
	    bool operator<=(const Rational& rhs) const;
	
	    Rational operator+(const Rational& rhs) const;
	    Rational operator-(const Rational& rhs) const;
	    Rational operator*(const Rational& rhs) const;
	    Rational operator/(const Rational& rhs) const;
	
	    Rational& operator+=(const Rational& rhs);
	    Rational& operator-=(const Rational& rhs);
	    Rational& operator*=(const Rational& rhs);
	    Rational& operator/=(const Rational& rhs);
	
	    Rational& operator++();
	    Rational operator++(int);
	    Rational& operator--();
	    Rational operator--(int);
	
private:
	void Norm();
	int n, d;
};