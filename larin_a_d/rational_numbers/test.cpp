#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing arithmetic") {
    std::cout << Rational(1, 2) << " - output test" << std::endl;
    CHECK(Rational(100, 1000) == Rational(1, 10));
    CHECK(Rational(2, 4) + Rational(9, 3) == Rational(7, 2));
    CHECK(Rational(8, 9) - Rational(12, 6) == Rational(-10, 9));
    CHECK(Rational(5, 3) - Rational(11, 3) == Rational(-6, 3));
    CHECK(Rational(1, 7) * Rational(1, 2) == Rational(1, 14));
    CHECK(Rational(9, 1) / Rational(1, 2) == Rational(18, 1));
    CHECK(Rational(7, 2) / Rational(-5, 3) == Rational(-21, 10));
    CHECK((Rational(12, 1) += Rational(8, 1)) == Rational(20, 1));
    CHECK((Rational(420, 228) *= Rational(0, 11)) == Rational(0));
    CHECK((Rational(5, 2) -= Rational(0, 1337)) == Rational(5, 2));
    CHECK((Rational(30, 17) /= Rational(1, 17)) == Rational(30, 1));
}

TEST_CASE("Testing boolean") {
    CHECK(Rational(15, -15) == Rational(-15, 15));
    CHECK(Rational(-24, 4) != Rational(4, 24));
    CHECK(Rational(25, 2) > Rational(5, 21));
    CHECK(Rational(4, -3) < (Rational(25, 4)));
    CHECK(Rational(50, 2) >= (Rational(0, 19)));
    CHECK(Rational(50, 2) >= (Rational(50, 2)));
    CHECK(Rational(2, 28) <= (Rational(4, 25)));
    CHECK(Rational(2, 28) <= (Rational(2, 28)));
}

TEST_CASE("Testing other") {
    CHECK(-Rational(2000, 25) == Rational(-80));
    CHECK(+Rational(2000, 25) == Rational(80));
    CHECK((++Rational(13, 25)) == Rational(38, 25));
    CHECK((--Rational(13, 25)) == Rational(-12, 25));
    Rational f(13, 25);
    CHECK(((f++) == Rational(13, 25)));
    CHECK(f == Rational(38, 25));
    Rational s(13, 25);
    CHECK(((s--) == Rational(13, 25)));
    CHECK(s == Rational(-12, 25));
}

TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(1488, 0), "The denominator cannot be equal to zero!");
    CHECK_THROWS_WITH((Rational(7, 2) /= Rational(0, 3)), "Division by zero!");
}
