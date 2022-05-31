#pragma once

class Rational
{
public:
    Rational() = default;
    Rational(const int& _num);
    Rational(const int& f_num,const int& s_num);
    Rational(const Rational& _other);

    void convert();

    Rational& operator=(const Rational& _rhs);
    Rational& operator+=(const Rational& _rhs);
    Rational& operator-=(const Rational& _rhs);
    Rational& operator*=(const Rational& _rhs);
    Rational& operator/=(const Rational& _rhs);

    Rational operator+(const Rational& _rhs);
    Rational operator-(const Rational& _rhs);
    Rational operator*(const Rational& _rhs);
    Rational operator/(const Rational& _rhs);

    bool operator==(const Rational& _rhs) const;
    bool operator>(const Rational& _rhs) const;
    bool operator<(const Rational& _rhs) const;
    bool operator>=(const Rational& _rhs) const;
    bool operator<=(const Rational& _rhs) const;


private:
    int numerator;
    int denomerator;

};
