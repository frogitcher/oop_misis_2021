#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.cpp"

TEST_CASE("testing operationas") {
    CHECK(Rational(25, 30) == Rational(5, 6));
    CHECK(Rational(1, 3) + Rational(1, 3) == Rational(2, 3));
    CHECK(Rational(4, 3) - Rational(5, 3) == Rational(-1, 3));
    CHECK(Rational(2, 5) * Rational(1, 2) == Rational(2, 10));
    CHECK(Rational(4, 3) / Rational(-3, 4) == Rational(-16, 9));
    CHECK((Rational(5, 7) += Rational(3, 6)) == Rational(17, 14));
    CHECK((Rational(5, 1) *= Rational(0, 5)) == Rational(0));
    CHECK((Rational(2, 3) -= Rational(2, 3)) == Rational(0));
    CHECK((Rational(8, 2) /= Rational(1, 2)) == Rational(8, 1));
    CHECK(Rational(1, -1) == Rational(-1, 1));
    CHECK(Rational(-1, 1) != Rational(1, 1));
    CHECK(Rational(20, 1) > Rational(1, 20));
    CHECK(Rational(-6, 9) < (Rational(5, -9)));
    CHECK(Rational(4, 7) >= (Rational(7, 31)));
    CHECK(Rational(3, 14) <= (Rational(7, 15)));
    CHECK(Rational(3, 14)++ == (Rational(17, 14)));
    CHECK(Rational(8, 5)-- == (Rational(3, 5)));
}

TEST_CASE("testing exceptions") {
    CHECK_THROWS_WITH(Rational(1, 0), "denominator mustnot be equal to 0");
    CHECK_THROWS_WITH((Rational(5, 2) /= Rational(0, 3)), "division by 0");
}
