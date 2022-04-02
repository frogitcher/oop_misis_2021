#pragma once

class Rational {
public:
    Rational();
    Rational(int _num);
    Rational(int _num, int _den);
    ~Rational() = default;

    den_zero();

    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;

    Rational operator+(const Rational& rhs) const;
    Rational operator-(const Rational& rhs) const;
    Rational operator*(const Rational& rhs) const;
    Rational operator/(const Rational& rhs) const;

    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

private:
    void Normalize();
    int num, den;
};
