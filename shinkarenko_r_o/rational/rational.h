#pragma once

class Rational
{
public:
    Rational() = default;
    Rational(int _num);
    Rational(int _num, int _den);
    Rational(const Rational& other);
    ~Rational() = default;

    Rational& operator=(const Rational& rhs);

    Rational operator+(const Rational& rhs) const;
    Rational operator-(const Rational& rhs) const;
    Rational operator/(const Rational& rhs) const;
    Rational operator*(const Rational& rhs) const;

    Rational& operator+=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational operator-() const;
    Rational operator+() const;

    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;

    Rational operator++(int t);
    Rational& operator++();
    Rational operator--(int t);
    Rational& operator--();

    int GetNumerator();
    int GetDenominator();

private:
    void Normalize();
    int num, den;

};