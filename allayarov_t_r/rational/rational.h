#include <iostream>

#pragma once
#ifndef RATIONAL_H
#define RATIONAL_H

class Rational
{
public:
  Rational();
  Rational(const int numerator);
  Rational(const int numerator, const int denominator);
  Rational(const Rational &rational);
  ~Rational() = default;

  Rational &operator=(const Rational &rhs);

  Rational &operator++();
  Rational operator++(int);

  Rational &operator--();
  Rational operator--(int);

  Rational operator+();
  Rational operator+(const Rational &rhs) const;

  Rational operator-();
  Rational operator-(const Rational &rhs) const;

  Rational operator*(const Rational &rhs) const;
  Rational operator/(const Rational &rhs) const;

  Rational &operator+=(const Rational &rhs);
  Rational &operator-=(const Rational &rhs);
  Rational &operator*=(const Rational &rhs);
  Rational &operator/=(const Rational &rhs);

  bool operator==(const Rational &rhs) const;
  bool operator!=(const Rational &rhs) const;

  bool operator<(const Rational &rhs) const;
  bool operator<=(const Rational &rhs) const;
  bool operator>(const Rational &rhs) const;
  bool operator>=(const Rational &rhs) const;

  std::ostream &writeTo(std::ostream &ostrm) const;
  std::istream &readFrom(std::istream &istrm);

private:
  int numerator_{0};
  int denominator_{0};

  static const char separator{'/'};

  void normalize();
};

#endif /* RATIONAL_H */