#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing assigning operations") {
    Rational r(5);
    CHECK(r.GetNum() == 5);
    CHECK(r.GetDenum() == 1);

    r = Rational(1, 5);
    CHECK(r.GetNum() == 1);
    CHECK(r.GetDenum() == 5);

    Rational l = r;
    CHECK(l.GetNum() == 1);
    CHECK(l.GetDenum() == 5);

    CHECK(Rational(2, 10) == Rational(1, 5));
    CHECK(Rational(1, -5) == Rational(-1, 5));
}

TEST_CASE("Testing arithmetic operators") {
    CHECK(Rational(1, 5) + Rational(1, 5) == Rational(2, 5));
    CHECK(Rational(1, 2) + Rational(2, 5) == Rational(9, 10));
    CHECK(Rational(1, 5) + Rational(-1, 5) == Rational(0));
    CHECK(Rational(3, 5) + Rational(2, 5) == Rational(1));
    CHECK(Rational(3, 5) + Rational(4, 5) == Rational(7, 5));

    CHECK(Rational(1, 5) - Rational(1, 5) == Rational(0));
    CHECK(Rational(3, 5) - Rational(1, 5) == Rational(2, 5));
    CHECK(Rational(1, 2) - Rational(1, 5) == Rational(3, 10));
    CHECK(Rational(1, 2) - Rational(-1, 2) == Rational(1));

    CHECK(Rational(1, 5) * Rational(1, 5) == Rational(1, 25));
    CHECK(Rational(3, 5) * Rational(5, 3) == Rational(1));
    CHECK(Rational(12, 5) * Rational(3, 13) == Rational(36, 65));
    CHECK(Rational(-1, 5) * Rational(-1, 5) == Rational(1, 25));
    CHECK(Rational(-1, 5) * Rational(1, 5) == Rational(-1, 25));

    CHECK(Rational(1, 5) / Rational(1, 5) == Rational(1));
    CHECK(Rational(2, 5) / Rational(1, 5) == Rational(2));
    CHECK(Rational(12, 5) / Rational(3, 13) == Rational(52, 5));
    CHECK(Rational(4, 5) / Rational(-3, 5) == Rational(-4, 3));
}

TEST_CASE("Testing incremental functions") {
    Rational r(1, 5);

    CHECK(r++ == Rational(1, 5));
    CHECK(r == Rational(6, 5));

    CHECK(r-- == Rational(6, 5));
    CHECK(r == Rational(1, 5));

    CHECK(++r == Rational(6, 5));
    CHECK(--r == Rational(1, 5));


}

TEST_CASE("Testing boolean operators") {
    CHECK(Rational(1, 5) == Rational(1, 5));
    CHECK(Rational(-1, 5) == Rational(1, -5));
    CHECK(Rational(1, 5) == Rational(2, 10));
    CHECK(Rational(1, 5) != Rational(-1, 5));
    CHECK(Rational(1, 5) != Rational(2, 5));

    CHECK(Rational(1, 5) < Rational(2, 5));
    CHECK(Rational(1, 5) < Rational(1, 2));
    CHECK(Rational(-1, 5) < Rational(1, 5));
    CHECK(Rational(1, 5) < Rational(1));
    CHECK(Rational(-3, 5) < Rational(-1, 5));

    CHECK(Rational(1, 5) > Rational(1, 10));
    CHECK(Rational(2, 5) > Rational(1, 5));
    CHECK(Rational(1, 5) > Rational(-1, 5));
    CHECK(Rational(1) > Rational(1, 10));
    CHECK(Rational(-2, 5) > Rational(-3, 5));

    CHECK(Rational(-2, 5) <= Rational(-2, 5));
    CHECK(Rational(-2, 5) >= Rational(-2, 5));

}