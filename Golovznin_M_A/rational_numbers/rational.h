#pragma once

class Rational {
public:
    Rational() = default;

    Rational(int _num);

    Rational(int _num, int _denum);

    Rational(const Rational &other);

    ~Rational() = default;

    Rational &operator=(const Rational &rhs);

    Rational operator+(const Rational &rhs);

    Rational operator-(const Rational &rhs);

    Rational operator*(const Rational &rhs);

    Rational operator/(const Rational &rhs);

    Rational &operator+=(const Rational &rhs);

    Rational &operator-=(const Rational &rhs);

    Rational &operator*=(const Rational &rhs);

    Rational &operator/=(const Rational &rhs);

    Rational operator-();
    Rational operator+();

    Rational operator++(int a);
    Rational& operator++();

    Rational operator--(int a);
    Rational& operator--();

    //invariant
    // 1. denum != 0
    // 2. дробь несокращаемая

    bool operator<(const Rational &rhs) const;

    bool operator<=(const Rational &rhs) const;

    bool operator>(const Rational &rhs) const;

    bool operator>=(const Rational &rhs) const;

    bool operator==(const Rational &rhs) const;

    bool operator!=(const Rational &rhs) const;

    int GetNum() const;

    int GetDenum() const;

private:
    int num, denum;
    void Normalize();
};