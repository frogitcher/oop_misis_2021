#pragma once
#include <iostream>


class Rational{

private:
    int numerator;
    int denominator;
    void Normalize();

public:
    Rational();//for null
    Rational(const double value);//for the Z
    Rational(const double num, const double den);//for the fraction
    Rational(const Rational& other);
    ~Rational();

    void View();

    double ToDouble() const;

    Rational operator + (const Rational& rhs) const;
    Rational operator - (const Rational& rhs) const;
    Rational operator * (const Rational& rhs) const;
    Rational operator / (const Rational& rhs) const;

    Rational operator ++ () const;
    Rational operator -- () const;
    Rational operator += (const Rational& rhs);
    Rational operator -= (const Rational& rhs);
    Rational operator *= (const Rational& rhs);
    Rational operator /= (const Rational& rhs);

    bool operator < (const Rational& rhs) const;
    bool operator > (const Rational& rhs) const;
    bool operator <= (const Rational& rhs) const;
    bool operator >= (const Rational& rhs) const;
    bool operator == (const Rational& rhs) const;
    bool operator != (const Rational& rhs) const;

    friend std::ostream& operator << (std::ostream& out, const Rational& rhs);
    friend std::istream& operator >> (std::istream& in, Rational& rhs);

};

int gcd(int a, int b);
