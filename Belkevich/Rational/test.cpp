#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Constuctor check") {
    CHECK(Rational(3) == Rational(3,1));
    CHECK(Rational(6,1) == Rational(12,2));
    CHECK(Rational(-1,3) == Rational(1,-3));
    CHECK(Rational(-1,-3) == Rational(1,3));
    CHECK_THROWS_WITH(Rational(3,0), "Denominator can't be equal to zero");
}

TEST_CASE("Operators") {
    CHECK((Rational(2,3) + Rational(1,3)) == Rational(1,1));
    CHECK((Rational(7,3) - Rational(1,3)) == Rational(2));
    CHECK((Rational(5,7) / Rational(25,14)) == Rational(2,5));
    CHECK_THROWS_WITH(Rational(5,9) / Rational(0), "Can't divide by zero");
    Rational a(1,3);
    CHECK((a--) == Rational(1,3));
    CHECK(a == Rational(-2,3));
    Rational b(2,3);
    CHECK((b++) == Rational(2,3));
    CHECK(b == Rational(5,3));
    CHECK((++Rational(8,10)) == Rational(9,5));
    CHECK((--Rational(7,5)) == Rational(4,10));
    CHECK((Rational(1,3) += Rational(2)) == Rational(7,3));
    CHECK((Rational(1,3) -= Rational(2)) == Rational(-5,3));
    CHECK((Rational(1,3) /= Rational(2,1)) == Rational(1,6));
    CHECK((Rational(1,3) *= Rational(2,1)) == Rational(2,3));
}

TEST_CASE("bool functions") {
    CHECK(Rational(-1,-1) == Rational(1,1));
    CHECK(Rational(1,5) < Rational(7,3));
    CHECK(Rational(2,-3) > Rational(-4,3));
    CHECK(Rational(6,9) != Rational (3,2));
    CHECK(Rational(6,4) >= Rational(3,2));
    CHECK(Rational(8,7) <= Rational (6,5));
}

