#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "rational.h"

#include "doctest.h"

TEST_CASE("Testing Rational constructors")
{
  CHECK(Rational() == Rational(0, 1));
  CHECK(Rational(3) == Rational(3, 1));
  CHECK(Rational(-3) == Rational(-3, 1));
  CHECK(Rational(3, 1) == Rational(3, 1));
  CHECK(Rational(-3, 1) == Rational(-3, 1));
  CHECK(Rational(3, -1) == Rational(-3, 1));
  CHECK(Rational(-3, -1) == Rational(3, 1));
  CHECK(Rational(Rational(1, 1)) == Rational(1, 1));
  Rational a = Rational(2);
  CHECK(a == Rational(2, 1));
  CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("Testing the class invariant")
{
  CHECK(Rational(3) == Rational(-3, -1));
  CHECK(Rational(2, 4) == Rational(1, 2));
  CHECK(Rational(-2, 4) == Rational(-1, 2));
  CHECK(Rational(3, -9) == Rational(-1, 3));
  CHECK(Rational(27, -9) == Rational(-3, 1));
  CHECK(Rational(-27, 9) == Rational(-3, 1));
  CHECK(Rational(-27, -9) == Rational(3, 1));
  CHECK(Rational(2, 5) == Rational(2, 5));
  CHECK(Rational(1024, 2048) == Rational(1, 2));
}

TEST_CASE("Testing Rational arithmetic #1")
{
  Rational a = Rational(1, 3);
  Rational b = Rational(10, 20);
  CHECK((a + b) == Rational(5, 6));
  CHECK((a - b) == Rational(-1, 6));
  CHECK((a * b) == Rational(1, 6));
  CHECK((a / b) == Rational(2, 3));
  CHECK(-a == Rational(-1, 3));
  CHECK(+a == Rational(1, 3));
  CHECK(++a == Rational(4, 3));
  CHECK(a++ == Rational(4, 3));
  CHECK(a == Rational(7, 3));
  CHECK(a-- == Rational(7, 3));
  CHECK(a == Rational(4, 3));
  CHECK(--a == Rational(1, 3));
}

TEST_CASE("Testing Rational arithmetic #2")
{
  Rational a = Rational(2, 5);
  Rational b = Rational(3, 5);
  a += b;
  CHECK(a == Rational(1));
  a -= b;
  CHECK(a == Rational(2, 5));
  a *= b;
  CHECK(a == Rational(6, 25));
  b = Rational(1, 5);
  a /= b;
  CHECK(a == Rational(6, 5));
}

TEST_CASE("Testing Rational arithmetic #3")
{
  CHECK_THROWS(Rational(0) / Rational(0));
  CHECK_THROWS(Rational(1) / Rational(0));
  CHECK_THROWS(Rational(2, 3) / Rational(0, 2));
  CHECK_THROWS(Rational(1, 2) /= Rational(0));
  CHECK_THROWS(Rational(1, 2) /= Rational(5, 0));
  CHECK((Rational(1, 2) * Rational(0, 2)) == Rational(0));
  CHECK((Rational(0, 2) *= Rational(1, 2)) == Rational(0));
}

TEST_CASE("Testing Rational comparison operators")
{
  CHECK(Rational(1, 2) != Rational(2, 5));
  CHECK(Rational(1, 2) > Rational(2, 5));
  CHECK(Rational(1, 2) >= Rational(2, 5));
  CHECK(Rational(1, 2) >= Rational(1, 2));
  CHECK(Rational(1, 3) < Rational(1, 2));
  CHECK(Rational(1, 3) <= Rational(1, 2));
  CHECK(Rational(1, 3) <= Rational(1, 3));
  CHECK(Rational(10, 20) > Rational(9, 20));
}

TEST_CASE("Testing Rational input/output")
{
  Rational a = Rational(1, 2);
  std::ostringstream oss;
  oss << a;
  CHECK(oss.str() == "1/2");

  Rational b, c, d;
  std::istringstream iss("2/3\n3/4\n10/2\n");
  iss >> b >> c >> d;
  CHECK(b == Rational(2, 3));
  CHECK(c == Rational(3, 4));
  CHECK(d == Rational(5, 1));
}
