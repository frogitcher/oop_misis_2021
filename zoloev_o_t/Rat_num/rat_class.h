#pragma once
#include <iostream>


class Rational{

private:
    int numerator;
    int denominator;
    void Normalize();

public:
    Rational();//for null
    Rational(const int value);//for the Z
    Rational(const int num, const int den);//for the fraction
    Rational(const Rational& other);
    ~Rational();

    void View();

    double ToDouble() const;

    Rational& operator=(const Rational& rhs);


    Rational operator + (const Rational& rhs) const;
    Rational operator - (const Rational& rhs) const;
    Rational operator * (const Rational& rhs) const;
    Rational operator / (const Rational& rhs) const;

    Rational& operator ++ ();
    Rational& operator -- ();
    Rational operator ++ (int a);
    Rational operator -- (int a);

    Rational& operator += (const Rational& rhs);
    Rational& operator -= (const Rational& rhs);
    Rational& operator *= (const Rational& rhs);
    Rational& operator /= (const Rational& rhs);

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
