#pragma once

class Rational {
public:
    Rational() = default;
    ~Rational() = default;

    Rational(int _num);
    Rational(int _num, int _den);
    Rational(const Rational& other);

    int GetNumerator() const;
    int GetDenominator() const;

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

    Rational operator+() const;
    Rational operator-() const;
    Rational& operator++();
	Rational operator++(int);

private:
    int num, den;
    void Normalize();
};
