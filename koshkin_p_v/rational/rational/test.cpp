#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing arithmetic operators") {
    Rational a(-3, 7), b(8, 13);
    CHECK(((a + b) == Rational(17, 91)) == true);
    CHECK(((a - b) == Rational(-95, 91)) == true);
    CHECK(((a * b) == Rational(-23,91)) == false);
    CHECK(((a / b) == Rational(-39, 56)) == true);

    Rational x(7, 21), y(7, 21), z(7, 21), w(7, 21), v(14, 21);
    x-=v;
    CHECK((x == Rational(-1, 3)) == true);
    y*=v;
    CHECK((y == Rational(2, 9)) == true);
    z/=v;
    CHECK((z == Rational(1, 2)) == true);
    w+=v;
    CHECK((w == Rational(1, 1)) == true);

}

TEST_CASE("Testing boolean operators") {
    Rational a(-3, 7), b(8, 13), c(-5, 17), d(4, 12);
    CHECK((a == c) == false);
    CHECK((a < b) == true);
    CHECK((a > c) == false);
    CHECK((b <= c) == false);
    CHECK((a >= d) == false);
    CHECK((a != d) == true);
}

TEST_CASE("Testing other operators") {
    Rational a(-3, 7), b(8, 13), c(-5, 17), d(4, 12);
    a++;
    d--;
    c++;
    CHECK((c == Rational(12, 17))== true);
    CHECK((a == Rational(4, 7))==true);
    CHECK((d == Rational(-2, 3))==true);
    CHECK((--b == Rational(-5, 13))==true);
}
TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(2, 0), "Denominator can not be 0!");
    CHECK_THROWS_WITH((Rational(3, 6) /= Rational(0, 81)), "Division can not be 0!");
}