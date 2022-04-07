#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("boolean operators")
{
    Rational a(1, 2), b(2, 4), c(5, 3),d(3, 4);
    CHECK((a == b));
    CHECK(!(a > c));
    CHECK((d > a));
    CHECK((b <= c));
    CHECK(!(a >= d));
    CHECK((a != d));
}
TEST_CASE("arithmetic operators") {
    Rational a(1, 2), b(2, 4), c(5, 3),d(3, 4);
    CHECK(a + b == Rational(1, 1));
    CHECK(a - b == Rational(0, 1));
    CHECK(a * c == Rational(5,6));
    CHECK(a / b == Rational(1, 1));
    CHECK(a - d == Rational(-1, 4));
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
TEST_CASE("Testing other operators")
{
    Rational a(1, 2), b(2, 4), c(5, 3),d(3, 4);
    a++;
    d--;
    CHECK(++c == Rational(8, 3));
    CHECK(a == Rational(3, 2));
    CHECK(d == Rational(-1, 4));
    CHECK(--b == Rational(-1, 2));
}
TEST_CASE("exceptions") {
    CHECK_THROWS_WITH(Rational(1, 0), "invalid denum - 0!");
    CHECK_THROWS_WITH((Rational(1, 2) /= Rational(0, 3)), "invalid denum");
}
