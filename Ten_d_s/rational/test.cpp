#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Test1") {
    CHECK(Rational(4, 7) + Rational(3, 7) == Rational(1, 1));
    CHECK(Rational(3, 3) - Rational(1, 2) == Rational(2, 4));
    CHECK(Rational(1, 3) - Rational(5, 3) == Rational(-4, 3));
    CHECK(Rational(2, 3) * Rational(1, 2) == Rational(1, 3));
    CHECK(Rational(5, 1) / Rational(1, 2) == Rational(10, 1));
    CHECK(Rational(4, 3) / Rational(-3, 4) == Rational(-16, 9));
    CHECK((Rational(5, 1) += Rational(3, 1)) == Rational(8, 1));
    CHECK((Rational(1, 2) -= Rational(0, 43)) == Rational(1, 2));
    CHECK((Rational(5, 1) *= Rational(0, 5)) == Rational(0));
    CHECK((Rational(8, 2) /= Rational(1, 2)) == Rational(8, 1));
}

TEST_CASE("Test2") {
    CHECK(Rational(1, -1) == Rational(-1, 1));
    CHECK(Rational(-1, 1) != Rational(1, 1));
    CHECK(Rational(10, 1) > Rational(1, 10));
    CHECK(Rational(-17, 9) < (Rational(5, -9)));
    CHECK(Rational(7, 8) >= (Rational(2, 3)));
    CHECK(Rational(2, 3) >= (Rational(2, 3)));
    CHECK(Rational(3, 12) <= (Rational(4, 5)));
    CHECK(Rational(1, 7) <= (Rational(2, 14)));
}

TEST_CASE("Test3") {
    CHECK_THROWS_WITH(Rational(4, 0), "demonitation must not be equal to 0");
    CHECK_THROWS_WITH((Rational(4, 9) /= Rational(0, 9)), "Division by 0!");
}
