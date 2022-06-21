#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Basic functions") {
    CHECK((Rational(3, 13) + Rational(3, 13)) == Rational(18, 39));
    CHECK((Rational(9, 13) - Rational(6, 13)) == Rational(9, 39));
    CHECK((Rational(2, 3) * Rational(3, 5)) == Rational(6, 15));
    CHECK((Rational(3, 13) / Rational(3, 13)) == Rational(1));

    CHECK((Rational(3, 13) += Rational(3, 13)) == Rational(6, 13));
    CHECK((Rational(3, 13) -= Rational(3, 13)) == Rational(0));
    CHECK((Rational(3, 13) *= Rational(3, 13)) == Rational(9, 169));
    CHECK((Rational(3, 13) /= Rational(3, 13)) == Rational(1));

    CHECK(Rational(2, 13) < Rational(9, 39));
    CHECK(Rational(3, 13) <= Rational(9, 39));
    CHECK(Rational(4, 13) > Rational(9, 39));
    CHECK(Rational(3, 13) >= Rational(9, 39));

    CHECK(Rational(3, 13) == Rational(9, 39));
    CHECK(Rational(2, 13) != Rational(9, 39));
}
TEST_CASE("Testing actions with zero") {
    CHECK_THROWS_WITH((Rational(1,0)), "denominator must not be equal to zero");
    CHECK_THROWS_WITH((Rational(1,2) / Rational(0)), "You can't divide by zero");
    CHECK_THROWS_WITH((Rational(1,2) /= Rational(0)), "You can't divide by zero");
}