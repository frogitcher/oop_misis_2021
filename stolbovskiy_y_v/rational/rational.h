#pragma once

class rational {
public:
	rational() = default;
	rational(int _num);
	rational(int _num, int _den);
	rational(const rational& r);
	~rational() = default;

	rational& operator=(const rational& rhs);

	rational operator+(const rational& rhs) const;
	rational operator-(const rational& rhs) const;
	rational operator*(const rational& rhs) const;
	rational operator/(const rational& rhs) const;

	rational& operator+=(const rational& rhs);
	rational& operator-=(const rational& rhs);
	rational& operator*=(const rational& rhs);
	rational& operator/=(const rational& rhs);

	rational operator-() const;
	rational operator+() const;

	bool operator<(const rational& rhs) const;
	bool operator<=(const rational& rhs) const;
	bool operator>(const rational& rhs) const;
	bool operator>=(const rational& rhs) const;

	bool operator==(const rational& rhs) const;
	bool operator!=(const rational& rhs) const;

	int getnum() const;
	int getden() const;
	void setnum(const int& _num);
	void setden(const int& _den);

private:
	int num, den;
	void normalize();
};