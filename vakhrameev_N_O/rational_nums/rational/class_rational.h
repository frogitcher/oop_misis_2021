#pragma once
class Rational
{
public:
    Rational() = default;
    Rational(int num);
    Rational(int num, int den);
    Rational(const Rational& other);
    ~Rational() = default;

    Rational& operator=(const Rational& rhs);

    Rational operator+(const Rational& rhs) const;
    Rational operator-(const Rational& rhs) const;
    Rational operator*(const Rational& rhs) const;
    Rational operator/(const Rational& rhs) const;

    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);

    Rational operator++();
    Rational operator++(int a);
    Rational operator-() const;
    Rational operator+() const;

    bool operator>(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;

    int GetNumerator() const;
    int GetDenominator() const;

private:
    void Normalize();
    int num;
    int den;
};