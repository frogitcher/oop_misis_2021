#pragma once

class Rational {
public:
    Rational();
    Rational(int _num);
    Rational(int _num, int _den);
    Rational(const Rational& other);
    ~Rational() = default;
    Rational& operator=(const Rational& other);

    bool operator<(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;
    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;

    Rational operator+(const Rational& rhs) const;
    Rational operator-(const Rational& rhs) const;
    Rational operator/(const Rational& rhs) const;
    Rational operator*(const Rational& rhs) const;

    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational operator-();
    Rational operator+();

    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

    int GetDenominator() const;
    int GetNumerator() const;
    void SetDenominator(int val);
    void SetNumerator(int val);

private:
    int num, den;
    void Normalize();
};
