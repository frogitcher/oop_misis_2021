#pragma once
#include <mutex>
class Rational
{
public:
	Rational() = default;
	~Rational() = default;
	Rational(int _num);//done
	Rational(int _num, int _den);//done

	Rational(const Rational& other);//done

	Rational operator=(const Rational& rhs);//done

	Rational operator+(const Rational& rhs) const;//done
	Rational operator-(const Rational& rhs) const;//done
	Rational operator*(const Rational& rhs) const;//done
	Rational operator/(const Rational& rhs) const;//done

	Rational operator+=(const Rational& rhs);//done
	Rational operator-=(const Rational& rhs);//done
	Rational operator*=(const Rational& rhs);//done
	Rational operator/=(const Rational& rhs);//done

	Rational operator-() const;//done

	bool operator<(const Rational& rhs) const;//done
	bool operator>(const Rational& rhs) const;//done
	bool operator<=(const Rational& rhs) const;//done
	bool operator>=(const Rational& rhs) const;//done

	bool operator==(const Rational& rhs) const;//done
	bool operator!=(const Rational& rhs) const;//done

	Rational operator++(int);//postfix
	Rational& operator++();//prefix
	Rational& operator--();
	Rational operator--(int);


	int GetNum() const;
	void SetNum(int _num);
	int GetDen() const;
	void SetDen(int _den);
private:
	int num, den;
	void simplify();
};
