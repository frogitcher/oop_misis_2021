#pragma once

#include <ostream>

class Rational {
public:
    Rational() = default;
    Rational(int _numerator);
    Rational(int _numerator, int _denominator);
    Rational(const Rational &rhs);

    ~Rational() = default;

    Rational &operator=(const Rational &rhs);
    Rational operator+(const Rational &rhs) const;
    Rational operator-(const Rational &rhs) const;
    Rational operator*(const Rational &rhs) const;
    Rational operator/(const Rational &rhs) const;

    Rational &operator+=(const Rational &rhs);
    Rational &operator-=(const Rational &rhs);
    Rational &operator*=(const Rational &rhs);
    Rational &operator/=(const Rational &rhs);

    Rational operator-() const;
    Rational operator+() const;

    bool operator==(const Rational &rhs) const;
    bool operator!=(const Rational &rhs) const;
    bool operator<(const Rational &rhs) const;
    bool operator>(const Rational &rhs) const;
    bool operator<=(const Rational &rhs) const;
    bool operator>=(const Rational &rhs) const;

    int getNum() const;
    int getDen() const;

private:
    long long numerator, denominator;
    void Normalize();
};

std::ostream &operator<<(std::ostream &os, const Rational &r);