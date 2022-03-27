#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing arithmetic operators") {
    Rational a(-3, 2), b(-2, 9), c(-6, 4), d(25, 3);
    CHECK(((a + b) == Rational(-31, 18)));
    CHECK((a - b == Rational(-23, 18)));
    CHECK(!((a * c) == Rational(9,25)));
    CHECK(((a / c) == Rational(1, 1)));
    CHECK((a - d == Rational(-59, 6)));

    Rational q(-5, 6), w(-5, 6), e(-5, 6), x(-5, 6), y(-1,6);
    q-=y;
    CHECK((q == Rational(-2,3)));
    w*=y;
    CHECK((w == Rational(5,36)));
    e/=y;
    CHECK((e == Rational(5,1)));
    x+=y;
    CHECK((x == Rational(-1,1)));
}

TEST_CASE("Testing boolean operators") {
    Rational a(-3, 2), b(-2, 9), c(-6, 4), d(25, 3);
    CHECK((a == c));
    CHECK((a < b));
    CHECK(!(a > c));
    CHECK(!(b <= c));
    CHECK((d >= a));
    CHECK((a != d));
}

TEST_CASE("Testing other operators") {
    Rational a(30,50), b(-1,10), c(3,5),d(75/3);
    a++;
    d--;
    CHECK(a++ == Rational(3, 5));
    CHECK(a == Rational(8, 5));
    
    CHECK((++c == Rational(8, 5)));
    CHECK((d == Rational(24, 1)));
    CHECK((--b == Rational(-11, 10)));
    CHECK(((-Rational(-3,1)) == Rational(3, 1)));
}

TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(222, 0), "Denominator can not be 0!");
    CHECK_THROWS_WITH((Rational(9, 1) /= Rational(0, 634)), "Divisor can not be 0!");
}
