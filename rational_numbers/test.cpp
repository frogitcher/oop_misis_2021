#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing arithmetic operations") {
    std::cout << Rational(1, 2) << " - output test" << std::endl;
    CHECK(Rational(100, 1000) == Rational(1, 10));
    CHECK(Rational(1, 2) + Rational(1, 2) == Rational(1, 1));
    CHECK(Rational(3, 3) - Rational(1, 2) == Rational(2, 4));
    CHECK(Rational(2, 5) * Rational(1, 2) == Rational(2, 10));
    CHECK(Rational(5, 1) / Rational(1, 2) == Rational(10, 1));
    CHECK((Rational(5, 1) += Rational(3, 1)) == Rational(8, 1));
    CHECK((Rational(5, 1) *= Rational(0, 5)) == Rational(0));
    CHECK((Rational(7, 2) -= Rational(0, 5723)) == Rational(7, 2));
}

TEST_CASE("Testing boolean functions") {
    CHECK(Rational(1, -1) == Rational(-1, 1));
    CHECK(Rational(-1, 1) != Rational(1, 1));
    CHECK(Rational(20, 1) > Rational(1, 20));
    CHECK(Rational(-6, 9) < (Rational(5, -9)));
}

TEST_CASE("Testing other stuff") {
    CHECK(-Rational(150, 50) == Rational(-3));
    CHECK(+Rational(150, 50) == Rational(3));
    CHECK((Rational(2, 5)++) == Rational(7, 5));
    CHECK((++Rational(2, 5)) == Rational(7, 5));
}

TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(1, 0), "Denominator must not be equal to 0!");
    CHECK_THROWS_WITH((Rational(4, 9) /= Rational(0, 23)), "Division by 0!");
}
