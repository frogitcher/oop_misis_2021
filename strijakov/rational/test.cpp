#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing arithmetic operators") {
    Rational a(-3, 2), b(-2, 9), c(-6, 4), d(25, 3);
    CHECK(((a + b) == Rational(-31, 18)) == true);
    CHECK((a - b == Rational(-23, 18)) == true);
    CHECK(((a * c) == Rational(9,25)) == false);
    CHECK(((a / c) == Rational(1, 1)) == true);
    CHECK((a - d == Rational(-59, 6)) == true);

    Rational q(-5, 6), w(-5, 6), e(-5, 6), x(-5, 6), y(-1,6);
    q-=y;
    CHECK((q == Rational(-2,3)) == true);
    w*=y;
    CHECK((w == Rational(5,36)) == true);
    e/=y;
    CHECK((e == Rational(5,1)) == true);
    x+=y;
    CHECK((x == Rational(-1,1)) == true);
}

TEST_CASE("Testing boolean operators") {
    Rational a(-3, 2), b(-2, 9), c(-6, 4), d(25, 3);
    CHECK((a == c) == true);
    CHECK((a < b) == true);
    CHECK((a > c) == false);
    CHECK((b <= c) == false);
    CHECK((d >= a) == true);
    CHECK((a != d) == true);
}

TEST_CASE("Testing other operators") {
    Rational a(30,50), b(-1,10), c(3,5),d(75/3);
    a++;
    d--;
    CHECK((++c == Rational(8, 5))== true);
    CHECK((a == Rational(8, 5))==true);
    CHECK((d == Rational(24, 1))==true);
    CHECK((--b == Rational(-11, 10))==true);
    CHECK(((-Rational(-3,1)) == Rational(3, 1))==true);
}
TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(8, 0), "Denominator can not be 0!");
    CHECK_THROWS_WITH((Rational(8, 6) /= Rational(0, 77)), "Division can not be 0!");
}
