#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Rational.h"
#include <string>
#include <mutex>
#include <iostream>

TEST_CASE("Test comparison operations")
{
    Rational a(6, 3), b(1, 1), c(9, 7), d(12, 6);
    CHECK(a == d);
    CHECK(!(a == b));
    CHECK(!(a != d));
    CHECK(a != b);
    CHECK(a > b);
    CHECK(a >= d);
    CHECK(a >= c);
    CHECK(!(c >= d));
    CHECK(a <= d);
    CHECK(b < a);
}

TEST_CASE("Test math operations")
{
    Rational a(3, 2), b(4, 5), c(2), d(7, 9), e(1, 2), f(1, 3);
    CHECK((a + b) == Rational(23, 10));
    CHECK((a - b) == Rational(7, 10));
    CHECK((e -= f) == Rational(1, 6));
    e = Rational(1, 2);
    CHECK((a += b) == Rational(23, 10));
    a = Rational(3, 2);
    CHECK((a * f) == Rational(1, 2));
    CHECK((a *= d) == Rational(7, 6));
    a = Rational(3, 2);
    CHECK((a / e) == Rational(3, 1));
    CHECK((a /= e) == Rational(3, 1));
}


TEST_CASE("Test unary operations")
{
    Rational a(5, 1);
    CHECK(++a == Rational(6));
    CHECK(a++ == Rational(6));
    CHECK(a == Rational(7));
    CHECK(--a == Rational(6));
    CHECK(a-- == Rational(6));
    CHECK(a == Rational(5));
}



TEST_CASE("Test minus and one_value_announcement and assignment")
{
    Rational a(5, 1), b(6), c(a), d;
    d = a;
    CHECK(-a == Rational(-5, 1));
    CHECK(b == Rational(6, 1));
    CHECK(-b == Rational(-6, 1));
    CHECK(a == c);
    CHECK(a == d);
    CHECK(d == c);
}


TEST_CASE("Testing denominator")
{
    Rational b(3, 2);
    CHECK_THROWS_WITH(Rational(5, 0), "denominator can't contain zero value");
    CHECK(Rational(5, -1) == Rational(-5, 1));
    CHECK_THROWS_WITH((b /= Rational(0, 5)), "denominator can't contain zero value");
}