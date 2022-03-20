#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing boolean operators") {
    Rational a(30, 50), b(-1, 10), c(3, 5),d(75, 3);
    CHECK((a == c));
    CHECK(!(a < b));
    CHECK(!(a > c));
    CHECK((b <= c));
    CHECK(!(a >= d));
    CHECK((a != d));
    CHECK((Rational(0, 1) == Rational(0, 5)));
}
TEST_CASE("Testing arithmetic operators") {
    Rational a(30, 50), b(-1, 10), c(3, 5), d(75, 3);
    CHECK(a + b == Rational(1, 2));
    CHECK(a - b == Rational(7, 10));
    CHECK(a * c == Rational(9,25));
    CHECK(a / b == Rational(-6, 1));
    CHECK(a - d == Rational(-122, 5));
    Rational x(-5, 6), y(-1,6);
    x+=y;
    CHECK(x == Rational(-1,1));
    Rational q(-5, 6);
    q-=y;
    CHECK(q == Rational(-2,3));
    Rational w(-5, 6);
    w*=y;
    CHECK(w == Rational(5,36));
    Rational e(-5, 6);
    e/=y;
    CHECK(e == Rational(5,1));
}
TEST_CASE("Testing other operators") {
    Rational a(30,50), b(-1,10), c(3,5), d(75, 3);
    a++;
    d--;
    CHECK(++c == Rational(8, 5));
    CHECK(a == Rational(8, 5));
    CHECK(d == Rational(24, 1));
    CHECK(--b == Rational(-11, 10));
    CHECK((-Rational(-3,1)) == Rational(3, 1));
    CHECK((+Rational(30,1)) == Rational(30, 1));
}
TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(8, 0), "Denominator can not be 0!");
    CHECK_THROWS_WITH((Rational(8, 6) /= Rational(0, 77)), "Division can not be 0!");
}
