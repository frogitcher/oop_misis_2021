#pragma once
#include <ostream>

class Rational {
public:
    Rational() = default;
    Rational(int _num, int _den);
    Rational(const Rational& other);
    Rational(int _num);
    ~Rational() = default;

    Rational operator+(const Rational& rhs) const;
    Rational operator-(const Rational& rhs) const;
    Rational operator*(const Rational& rhs) const;
    Rational operator/(const Rational& rhs) const;

    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);
    Rational& operator=(const Rational& rhs);
    Rational operator-() const;

    Rational& operator++();
    Rational operator++(int a);
    Rational& operator--();
    Rational operator--(int a);

    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;

    int GetNum() const;
    int GetDenom() const;

private:
    int num, den;
    void Normalize();
};

std::ostream& operator<<(std::ostream& os, const Rational& r);
