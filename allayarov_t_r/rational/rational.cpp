#include "rational.h"

#include <stdexcept>
#include <sstream>

Rational::Rational()
    : numerator_(0),
      denominator_(1)
{
}

Rational::Rational(const int numerator)
    : numerator_(numerator),
      denominator_(1)
{
}

Rational::Rational(const int numerator, const int denominator)
    : numerator_(numerator),
      denominator_(denominator)
{
  if (denominator_ == 0)
    throw std::invalid_argument("Zero division error");

  _normalize();
}

Rational::Rational(const Rational &rational)
    : numerator_(rational.numerator_),
      denominator_(rational.denominator_)
{
}

Rational &Rational::operator=(const Rational &rhs)
{
  numerator_ = rhs.numerator_;
  denominator_ = rhs.denominator_;
  return *this;
}

Rational &Rational::operator++()
{
  numerator_ += denominator_;
  return *this;
}

Rational Rational::operator++(int)
{
  Rational result(*this);
  ++(*this);
  return result;
}

Rational &Rational::operator--()
{
  numerator_ -= denominator_;
  return *this;
}

Rational Rational::operator--(int)
{
  Rational result(*this);
  --(*this);
  return result;
}

Rational Rational::operator+()
{
  return *this;
}

Rational Rational::operator+(const Rational &rhs) const
{
  Rational result(*this);
  result += rhs;
  return result;
}

Rational Rational::operator-()
{
  Rational result = Rational(-numerator_, denominator_);
  return result;
}

Rational Rational::operator-(const Rational &rhs) const
{
  Rational result(*this);
  result -= rhs;
  return result;
}

Rational Rational::operator*(const Rational &rhs) const
{
  Rational result(*this);
  result *= rhs;
  return result;
}

Rational Rational::operator/(const Rational &rhs) const
{
  Rational result(*this);
  result /= rhs;
  return result;
}

Rational &Rational::operator+=(const Rational &rhs)
{
  int a = numerator_;
  int b = denominator_;
  int c = rhs.numerator_;
  int d = rhs.denominator_;
  *this = Rational(a * d + b * c, b * d);
  return *this;
}

Rational &Rational::operator-=(const Rational &rhs)
{
  int a = numerator_;
  int b = denominator_;
  int c = rhs.numerator_;
  int d = rhs.denominator_;
  *this = Rational(a * d - b * c, b * d);
  return *this;
}

Rational &Rational::operator*=(const Rational &rhs)
{
  int a = numerator_;
  int b = denominator_;
  int c = rhs.numerator_;
  int d = rhs.denominator_;
  *this = Rational(a * c, b * d);
  return *this;
}

Rational &Rational::operator/=(const Rational &rhs)
{
  int a = numerator_;
  int b = denominator_;
  int c = rhs.numerator_;
  int d = rhs.denominator_;

  if (c == 0)
    throw std::invalid_argument("Zero division error");

  *this = Rational(a * d, b * c);
  return *this;
}

bool Rational::operator==(const Rational &rhs) const
{
  return (numerator_ * rhs.denominator_) == (denominator_ * rhs.numerator_);
}

bool Rational::operator!=(const Rational &rhs) const
{
  return !operator==(rhs);
}

bool Rational::operator<(const Rational &rhs) const
{
  return numerator_ * rhs.denominator_ < denominator_ * rhs.numerator_;
}

bool Rational::operator<=(const Rational &rhs) const
{
  return numerator_ * rhs.denominator_ <= denominator_ * rhs.numerator_;
}

bool Rational::operator>(const Rational &rhs) const
{
  return !operator<=(rhs);
}

bool Rational::operator>=(const Rational &rhs) const
{
  return !operator<(rhs);
}

std::ostream &operator<<(std::ostream &ostrm, const Rational &rhs)
{
  return rhs.writeTo(ostrm);
}

std::istream &operator>>(std::istream &istrm, Rational &rhs)
{
  return rhs.readFrom(istrm);
}

std::ostream &Rational::writeTo(std::ostream &ostrm) const
{
  ostrm << numerator_ << "/" << denominator_;
  return ostrm;
}

std::istream &Rational::readFrom(std::istream &istrm)
{
  int numerator(0);
  char separator(0);
  int denominator(0);
  istrm >> numerator >> separator >> denominator;
  if (istrm.good())
  {
    if (Rational::separator == separator)
    {
      if (denominator_ == 0)
        istrm.setstate(std::ios_base::failbit);

      numerator_ = numerator;
      denominator_ = denominator;
      _normalize();
    }
    else
      istrm.setstate(std::ios_base::failbit);
  }
  return istrm;
}

int gcd(int a, int b)
{
  return b ? gcd(b, a % b) : a;
}

void Rational::_normalize()
{
  int g = gcd(numerator_, denominator_);
  numerator_ /= g;
  denominator_ /= g;
}
