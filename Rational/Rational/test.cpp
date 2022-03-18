#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing arithmetic operations") {
    std::cout << Rational(117, 237) << " - test for one operator" << std::endl;
    CHECK(Rational(35, 245) == Rational(1, 7));
    CHECK(Rational(4, 3) + Rational(1, 3) == Rational(5, 3));
    CHECK(Rational(9, 3) - Rational(1, 2) == Rational(10, 4));
    CHECK(Rational(2, 3) - Rational(5, 3) == Rational(-3, 3));
    CHECK(Rational(6, 19) * Rational(1, 9) == Rational(2, 57));
    CHECK(Rational(89, 101) / Rational(1, 2) == Rational(178,101));
    CHECK(Rational(4, 3) / Rational(-4, 3) == Rational(-1, 1));
    CHECK((Rational(5, 25) += Rational(6, 4)) == Rational(17, 10));
    CHECK((Rational(5, 1) *= Rational(0, 9)) == Rational(0));
    CHECK((Rational(4, 3) -= Rational(4, 3)) == Rational(0));
    CHECK((Rational(6, 2) /= Rational(1, 2)) == Rational(6, 1));
}

TEST_CASE("Testing boolean functions") {
    CHECK(Rational(213, -876) == Rational(-213, 876));
    CHECK(Rational(-65, 34) != Rational(65, 34));
    CHECK(Rational(20, 7) > Rational(7, 20));
    CHECK(Rational(-6, 87) < (Rational(5, -101)));
    CHECK(Rational(3, 7) >= (Rational(5, 28)));
    CHECK(Rational(3, 7) >= (Rational(3, 711)));
    CHECK(Rational(6, 15) <= (Rational(7, 16)));
    CHECK(Rational(6, 15) <= (Rational(3, 4)));
}

TEST_CASE("Testing unarian operators") {
    CHECK(-Rational(300, 60) == Rational(-5));
    CHECK(+Rational(300, 60) == Rational(5));
    CHECK((++Rational(8, 98)) == Rational(53, 49));
    CHECK((--Rational(8, 98)) == Rational(-45, 49));
    Rational a(6, 7);
    CHECK(((a++) == Rational(6, 7)));
    CHECK(a == Rational(13, 7));
    Rational b(47, 69);
    CHECK(((b--) == Rational(47, 69)));
    CHECK(b == Rational(-22, 69));
}

TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Rational(256, 0), "Den can't be 0");
    CHECK_THROWS_WITH((Rational(24, 49) /= Rational(0, 117)), "Division by 0!!!");
}