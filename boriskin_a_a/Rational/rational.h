#pragma once
#include <ostream>


class Rational {
public:
    Rational() = default;
    Rational(int _num);
    Rational(int _num, int _denum);
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
    int GetDenum() const;

private:
    int num, denum;
    void Normalize();
};

std::ostream& operator<<(std::ostream& os, const Rational& r);
