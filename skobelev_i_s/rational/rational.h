#pragma once

class Rational {
public:
    Rational() = default;
    ~Rational() = default;

    Rational(int _num);
    Rational(int _num, int _den);
    Rational(Rational& other);

    int GetNumerator();
    int GetDenominator();

    Rational& operator=(Rational& rhs);

    Rational operator+(Rational& rhs);
    Rational operator-(Rational& rhs);
    Rational operator*(Rational& rhs);
    Rational operator/(Rational& rhs);

    Rational& operator+=(Rational& rhs);
    Rational& operator-=(Rational& rhs);
    Rational& operator*=(Rational& rhs);
    Rational& operator/=(Rational& rhs);

    bool operator<(Rational& rhs) const;
    bool operator<=(Rational& rhs) const;
    bool operator>(Rational& rhs) const;
    bool operator>=(Rational& rhs) const;

    bool operator==(Rational& rhs) const;
    bool operator!=(Rational& rhs) const;

    Rational operator+();

private:
    int num, den;
    void Normalize();
};