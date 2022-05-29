#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

using namespace std;

TEST_CASE("Output testing.") {
    stringstream ss1;
    ss1 << Rational(15, 30);
    CHECK(ss1.str() == "1/2");
    stringstream ss2;
    ss2 << Rational(2, 1);
    CHECK(ss2.str() == "2");
}


TEST_CASE("Testing unary arithmetic operators.") {
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

TEST_CASE("Testing binary arithmetic operators.") {
    CHECK(Rational(1, 7) + Rational(7, 7) == Rational(8, 7));
    CHECK(Rational(7) - Rational(1, 2) == Rational(13, 2));
    CHECK(Rational(5, 6) - Rational(2, 6) == Rational(1, 2));
    CHECK(Rational(17, 21) / Rational(21, 17) == Rational(289, 441));
    CHECK(Rational(-1, 2) / Rational(1, 2) == Rational(-1));
    CHECK((Rational(3, 2) += Rational(5, 2)) == Rational(8, 2));
    CHECK((Rational(5, 10) *= Rational(0)) == Rational(0));
    CHECK((Rational(6, 2) /= Rational(1, 2)) == Rational(6, 1));
    CHECK((Rational(4, 3) -= Rational(4, 3)) == Rational(0));
}

TEST_CASE("Testing binary boolean operators.") {
    CHECK(Rational(213, -876) == Rational(-213, 876));
    CHECK(Rational(-65, 34) != Rational(65, 34));
    CHECK(Rational(20, 7) > Rational(7, 20));
    CHECK(Rational(-6, 87) < (Rational(5, -101)));
    CHECK(Rational(3, 7) >= (Rational(5, 28)));
    CHECK(Rational(3, 7) >= (Rational(3, 711)));
    CHECK(Rational(6, 15) <= (Rational(7, 16)));
    CHECK(Rational(6, 15) <= (Rational(3, 4)));
}

TEST_CASE("Testing exceptions.") {
    CHECK_THROWS_WITH(Rational(1, 0), "Denominator can't be a zero.");
    CHECK_THROWS_WITH((Rational(1, 2) /= Rational(0)), "Can't divide by zero.");
}