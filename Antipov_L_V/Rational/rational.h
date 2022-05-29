#pragma once
#include <ostream>

#ifndef RATIONAL_RATIONAL_H
#define RATIONAL_RATIONAL_H

class Rational {
public:
    Rational() = default;
    ~Rational() = default;

    Rational(int _num);
    Rational(int _num, int _den);
    Rational(const Rational& copy);

    Rational& operator=(const Rational& rhs);
    Rational operator+(const Rational& rhs) const;
    Rational& operator+=(const Rational& rhs);
    Rational operator-(const Rational& rhs) const;
    Rational& operator-=(const Rational& rhs);
    Rational operator*(const Rational& rhs) const;
    Rational& operator*=(const Rational& rhs);
    Rational operator/(const Rational& rhs) const;
    Rational& operator/=(const Rational& rhs);

    bool operator<(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;
    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;

    Rational operator-() const;
    Rational operator+() const;
    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

    // Getters
    int GetNum() const;
    int GetDen() const;

private:
    int num, den;
    void Normal();

};

// output
std::ostream& operator<<(std::ostream& os, const Rational& r);

#endif //RATIONAL_RATIONAL_H
