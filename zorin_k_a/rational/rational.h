#pragma once
#include <ostream>


class Rational
{
    public:
    Rational()=default;
    Rational (int _num);
    Rational(int _num, int _den);
    Rational (const Rational&other);
    ~Rational()=default;


    Rational operator=(const Rational&rhs);


    Rational operator+(const Rational&rhs);
    Rational operator-(const Rational&rhs);
    Rational operator*(const Rational&rhs) const;
    Rational operator/(const Rational&rhs) const;
    //-,*,/
    Rational& operator+=(const Rational&rhs);
    Rational& operator-=(const Rational&rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational& operator--();
    Rational operator--(int a);
    Rational operator++(int a);
    Rational& operator++();
    bool operator<(const Rational&rhs) const;
    bool operator==(const Rational&rhs) const;
    bool operator>(const Rational&rhs) const;
    bool operator<=(const Rational&rhs) const;
    bool operator>=(const Rational&rhs) const;
    bool operator!=(const Rational& rhs) const;



    int GetNumerator() const;
    int GetDenumerator() const;
    private:
    void Normalize();
    int num,den;
};
std::ostream& operator<<(std::ostream& os, const Rational& r);
