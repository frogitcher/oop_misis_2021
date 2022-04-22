#pragma once

class Rational{
	public:
		Rational()=default;
		Rational(int _num);
		Rational(int _num, int _den);
		Rational(const Rational& other);
		~Rational()=default;

		Rational operator+(const Rational& rhs) const; 
		Rational operator-(const Rational& rhs) const; 
		Rational operator*(const Rational& rhs) const; 
		Rational operator/(const Rational& rhs) const; 

		Rational& operator+=(const Rational& rhs);
		Rational& operator-=(const Rational& rhs);	
		Rational& operator*=(const Rational& rhs);
		Rational& operator/=(const Rational& rhs);

		Rational operator -();
		Rational operator +();

		Rational& operator=(const Rational& rhs);
		bool operator<(const Rational& rhs ) const;
		bool operator>(const Rational& rhs ) const;
		bool operator<=(const Rational& rhs ) const;
		bool operator>=(const Rational& rhs ) const;
		bool operator==(const Rational& rhs) const;
		bool operator!=(const Rational& rhs) const;

		Rational& operator++();
		Rational operator++(int);
		Rational& operator--();
		Rational operator--(int);

		int	GetDenominator() const;
		int GetNumerator() const;

	private:
		int num;
		int den;
		void Normalize();
};
std::ostream& operator<<(std::ostream& os, const Rational& r);