#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Test initialization") {
    CHECK(Rational(1234321) == Rational(1234321, 1));
    CHECK(Rational(65432345675, 2).get_numerator() == 65432345675);
    CHECK(Rational(2, 3).get_denominator() == 3);
    CHECK(Rational(20, 5).get_numerator() == 4);
    CHECK(Rational(20, 15).get_denominator() == 3);
    CHECK(Rational(848484, 10) == Rational(848484, 10));
    CHECK(Rational(0, 76545678654) == Rational(0, 76545678654));
    CHECK(Rational(Rational(-11, -12)) == Rational(11, 12));
    CHECK_THROWS_WITH(Rational(8, 0), "Denominator must not be equal to 0");
}

TEST_CASE("Test logical operators") {
    CHECK(Rational(12344643, 6) > Rational(2, 3));
    CHECK(Rational(2345, 12) > Rational(-1, 1));
    CHECK(Rational(234234, 3) < Rational(23456789876, 2));
    CHECK(Rational(3, 11) >= Rational(2, 11));
    CHECK(Rational(5, 11) <= Rational(5, 11));
    CHECK(Rational(2, 11) != Rational(3, 11));
    CHECK(Rational(0, 11) == Rational(0, 11));
}

TEST_CASE("Test arithmetic operators") {
CHECK(Rational(114, 228) + Rational(113, 228) == Rational(227, 228));
CHECK(Rational(5, 222) + Rational(-35, 4) == Rational(-23, 12));
CHECK(Rational(5, 222) - Rational(-35, 6) == Rational(-215, 37));
CHECK(Rational(5, 333) - Rational(5, 6) == Rational(-545, 666));
CHECK(Rational(12, 123) * Rational(21, 321) == Rational(28, 4387));
CHECK(Rational(44, 444) * Rational(0, 3) == Rational(0, 1));
CHECK(Rational(5, 555) / Rational(5, 555) == Rational(1, 1));
CHECK(Rational(5, 100) / Rational(-13, 2) == Rational(-1, 130));
CHECK_THROWS_WITH(Rational(123, 432) / Rational(0, 2345), "Denominator must not be equal to 0");
CHECK(-Rational(6, 11) == Rational(-6, 11));
CHECK(-Rational(-7, 11) == Rational(7, 11));
CHECK(-Rational(0, 11) == Rational(0, 11));
CHECK(Rational(5, 11)++ == Rational(5, 11));
CHECK(++Rational(3, 6) == Rational(3, 2));
CHECK(Rational(5, 11)-- == Rational(5, 11));
CHECK(--Rational(5, 11) == Rational(-6, 11));
}
