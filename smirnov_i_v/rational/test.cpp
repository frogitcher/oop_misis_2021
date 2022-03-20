#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("testing initialization functions") {
    CHECK(Rational(5) == Rational(5, 1));
    CHECK(Rational(7, 2).getnumerator() == 7);
    CHECK(Rational(7, 2).getdenumerator() == 2);
    CHECK(Rational(20, 15).getnumerator() == 4);
    CHECK(Rational(20, 15).getdenumerator() == 3);
    CHECK(Rational(3, -7) == Rational(-3, 7));
    CHECK(Rational(12, 18) == Rational(2, 3));
    CHECK(Rational(-2, -3) == Rational(2, 3));
    CHECK(Rational(Rational(-2, -3)) == Rational(2, 3));
    CHECK(Rational(0, 5) == Rational(0, 1));
    CHECK_THROWS_WITH(Rational(8, 0), "denominator must not be equal to 0");
}

TEST_CASE("testing base arithmetic operations") {
    CHECK(Rational(2, 3) + Rational(5, 3) == Rational(7, 3));
    CHECK(Rational(2, 3) + Rational(-11, 4) == Rational(-25, 12));
    CHECK(Rational(5, 6) + Rational(-11, 4) == Rational(-23, 12));
    CHECK(Rational(5, 6) - Rational(-11, 4) == Rational(43, 12));
    CHECK(Rational(5, 6) - Rational(0, 4) == Rational(5, 6));
    CHECK(Rational(5, 6) - Rational(5, 6) == Rational(0, 1));
    CHECK(Rational(5, 6) * Rational(2, 3) == Rational(5, 9));
    CHECK(Rational(5, 6) * Rational(0, 3) == Rational(0, 1));
    CHECK(Rational(5, 6) * Rational(-7, 3) == Rational(-35, 18));
    CHECK(Rational(5, 6) / Rational(2, 3) == Rational(5, 4));
    CHECK(Rational(5, 6) / Rational(-7, 2) == Rational(-5, 21));
    CHECK_THROWS_WITH(Rational(5, 6) / Rational(0, 2), "Devisor can't be 0!");
    CHECK(-Rational(5, 6) == Rational(-5, 6));
    CHECK(-Rational(-5, 6) == Rational(5, 6));
    CHECK(-Rational(0, 6) == Rational(0, 6));
    CHECK(-Rational(0, 6) == Rational(0, 6));
    CHECK(Rational(5, 6)++ == Rational(5, 6));
    CHECK(++Rational(5, 6) == Rational(11, 6));
    CHECK(Rational(5, 6)-- == Rational(5, 6));
    CHECK(--Rational(5, 6) == Rational(-1, 6));
}

TEST_CASE("testing relationals operators") {
    CHECK(Rational(5, 6) > Rational(2, 3));
    CHECK(Rational(5, 6) > Rational(-11, 3));
    CHECK(Rational(2, 3) < Rational(5, 6));
    CHECK(Rational(-2, 3) < Rational(1, 6));
    CHECK(Rational(5, 6) >= Rational(5, 6));
    CHECK(Rational(5, 6) >= Rational(2, 3));
    CHECK(Rational(5, 6) <= Rational(5, 6));
    CHECK(Rational(2, 3) <= Rational(5, 6));
    CHECK(Rational(2, 3) == Rational(4, 6));
    CHECK(Rational(2, 3) != Rational(3, 6));
    CHECK(Rational(0, 3) == Rational(0, 6));
}