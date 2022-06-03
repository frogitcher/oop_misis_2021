#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("testing some inputs") {
    CHECK(rational(0, 3) == rational(0));
    CHECK(rational(1, 2) == rational(2, 4));
    CHECK(rational(1, 2) < rational(3, 4));
    CHECK(rational(2, 4) >= rational(2, 4));
    CHECK(rational(2) + rational(3) == rational(15, 3));
    CHECK(rational(5) * rational(2, 5) == rational(2));
    CHECK(rational(7) / rational(7, 6) == rational(6));
    CHECK(rational(4, 3) > rational(1));
    CHECK(rational(5, 6) != rational(6, 5));
    CHECK(rational(3, 1) - rational(1, 2) == rational(5, 2));
    CHECK(rational(2) <= rational(2, 1));
    CHECK((rational(3, 1) += rational(3, 1)) == rational(6, 1));
    CHECK((rational(4, 5) *= rational(0, 1)) == rational(0));
    CHECK((rational(7, 3) -= rational(0)) == rational(7, 3));
    CHECK((rational(4, 4) /= rational(4, 4)) == rational(1));
}

TEST_CASE("testing exceptions") {
    CHECK_THROWS_WITH(rational(1, 0), "denominator must not be equal to 0");
    CHECK_THROWS_WITH((rational(1, 2) /= rational(0, 1)), "cannot divide by 0");
}