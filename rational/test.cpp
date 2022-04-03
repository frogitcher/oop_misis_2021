#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing output"){
    std::stringstream teststream;
    teststream << Rational(1, 2);
    CHECK(teststream.str() == "1/2");
}

TEST_CASE("Testing arithmetic operations") {
    CHECK(Rational(100, 1000) == Rational(1, 10));
    CHECK(Rational(1, 2) + Rational(1, 2) == Rational(1, 1));
    CHECK(Rational(3, 3) - Rational(1, 2) == Rational(2, 4));
    CHECK(Rational(1, 3) - Rational(5, 3) == Rational(-4, 3));
    CHECK(Rational(2, 5) * Rational(1, 2) == Rational(2, 10));
    CHECK(Rational(5, 1) / Rational(1, 2) == Rational(10, 1));
    CHECK(Rational(4, 3) / Rational(-3, 4) == Rational(-16, 9));
    CHECK((Rational(5, 1) += Rational(3, 1)) == Rational(8, 1));
    CHECK((Rational(5, 1) *= Rational(0, 5)) == Rational(0));
    CHECK((Rational(7, 2) -= Rational(0, 5723)) == Rational(7, 2));
    CHECK((Rational(8, 2) /= Rational(1, 2)) == Rational(8, 1));
}

TEST_CASE("Testing boolean functions") {
    CHECK(Rational(1, -1) == Rational(-1, 1));
    CHECK(Rational(-1, 1) != Rational(1, 1));
    CHECK(Rational(20, 1) > Rational(1, 20));
    CHECK(Rational(-6, 9) < (Rational(5, -9)));
    CHECK(Rational(4, 7) >= (Rational(7, 31)));
    CHECK(Rational(4, 7) >= (Rational(4, 7)));
    CHECK(Rational(3, 14) <= (Rational(7, 15)));
    CHECK(Rational(3, 14) <= (Rational(3, 14)));
}

TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(1, 0), "denominator must not be 0");
    CHECK_THROWS_WITH((Rational(4, 9) /= Rational(0, 23)), "division by 0");
}
