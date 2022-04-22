#pragma once
#include <ostream>


class Rational {
public:
    Rational() = default;
    Rational(int _num);
    Rational(int _num, int _denom);
    Rational(const Rational& other);
    ~Rational() = default;

    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;

    Rational operator+(const Rational& rhs) const;
    Rational operator-(const Rational& rhs) const;
    Rational operator*(const Rational& rhs) const;
    Rational operator/(const Rational& rhs) const;

    Rational& operator=(const Rational& rhs);
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational operator-() const;
    Rational operator+() const;

    Rational& operator++();
    Rational operator++(int a);
    Rational& operator--();
    Rational operator--(int a);

    int GetNum() const;
    int GetDenom() const;

private:
    int num, denom;
    void Normalize();
};

std::ostream& operator<<(std::ostream& os, const Rational& r);
