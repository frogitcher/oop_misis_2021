#pragma once 
#include <ostream>

class Rational{
public:
    Rational() = default;
    Rational(int _numenator); //+
    Rational(int _numenator, int _denominator); //+
    Rational(const Rational& rhs); //+
    ~Rational() = default; //+

    Rational& operator=(const Rational& rhs); //+
    Rational operator+(const Rational& rhs) const; //+
    Rational operator-(const Rational& rhs) const; //+
    Rational operator*(const Rational& rhs) const; //+
    Rational operator/(const Rational& rhs) const; //+

    
    Rational& operator+=(const Rational& rhs); //+
    Rational& operator-=(const Rational& rhs); //+
    Rational& operator*=(const Rational& rhs); //+
    Rational& operator/=(const Rational& rhs); //+

    Rational operator-();
    Rational operator+(); // ?????

    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    bool operator<(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;

    int GetNumerator() const;
    int GetDenominator() const;

    
private:
    int numerator, denominator; 
    void Normalize();
};

std::ostream& operator<<(std::ostream& os, const Rational& r);