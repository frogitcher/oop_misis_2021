#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"
#include <iostream>

TEST_CASE("testing arithmetic operations") {
    Rational a(1, 2), b(-1, 2);
    a += b;
    CHECK(a == Rational(0));
    a = Rational(2, 5), b = Rational(1, 4);
    a -= b;
    CHECK(a == Rational(3, 20));
    a = Rational(2, 3), b = Rational(21, 5);
    a *= b;
    CHECK(a == Rational(14, 5));
    a = Rational(2, 3), b = Rational(3, 2);
    a /= b;
    CHECK(a == Rational(4, 9));
    a = Rational(1, 2), b = Rational(-1, 2);
    Rational c(2, 5), d(1, 4), e(2, 3), f(21, 5), g(3, 2);
    CHECK(a + b == Rational(0));
    CHECK(c - d == Rational(3, 20));
    CHECK(e * f == Rational(14, 5));
    CHECK(e / g == Rational(4, 9));
    a++;
    std::cout << a.getDenominator() << a.getNominator();
    b--;
    ++c;
    --d;
    CHECK(a == Rational(3, 2));
    CHECK(b == Rational(-3, 2));
    CHECK(c == Rational(7, 5));
    CHECK(d == Rational(-3, 4));
    CHECK(-f == Rational(-21, 5));
    CHECK(+g == Rational(3, 2));
}

TEST_CASE("testing boolean operations") {
    Rational a(2, 5), b(1, 4), c(1, 100), d(15), e(22, 31), f(29, 41);
    CHECK(c < a);
    CHECK(c <= Rational(1, 100));
    CHECK(d > e);
    CHECK(!(f >= e));
    CHECK(b == Rational(1, 4));
    CHECK(d != c);
}

TEST_CASE("testing the invariant") {
    CHECK_THROWS_WITH(Rational(1, 0), "denominator must not be equal to 0");
    CHECK_THROWS_WITH(Rational(1, 2) / Rational(0, 12), "it is impossible to divide by 0");
}
