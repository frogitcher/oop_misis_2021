#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("constructor tests") {
    CHECK(Rational(2, 4) == Rational(1, 2));
	CHECK(Rational(123, -47) == Rational(-123, 47));
	CHECK(Rational(1, 1) == Rational(1));
	CHECK(Rational(1024, -2) == Rational(-512));
	CHECK_THROWS_WITH(Rational(12345, 0), "Denominator must not be equal 0");
}

TEST_CASE("arithmetic tests") {
    Rational a(1, 7);
    Rational b(1, 5);
    a = b;
    CHECK(a == b);

    CHECK(Rational(2, 8) + Rational(3, 12) == Rational(1, 2));
	CHECK(Rational(2, 3) - Rational(1) == Rational(-1, 3));
	CHECK(Rational(1, 5) * Rational(0, 3) == Rational(0));
	CHECK(Rational(9, 2) / Rational(-128, 3) == Rational(-27, 256));
	CHECK_THROWS_WITH((Rational(1, 5) / Rational(0, 3)), "Denominator must not be equal 0");
	CHECK((Rational(1054, 13) += Rational(2331, 17)) == Rational(48221, 221));
	CHECK((Rational(1000) -= Rational(1, 9)) == Rational(8999, 9));
	CHECK((Rational(27) *= Rational(-1, 27)) == Rational(-1));
	CHECK((Rational(512) /= Rational(1024, 3)) == Rational(3, 2));
	CHECK_THROWS_WITH((Rational(12345, 6789) /= Rational(0, 13541)), "Denominator must not be equal 0");
	CHECK((-Rational(1, 3)) == Rational(-1, 3));
}

TEST_CASE("boolean tests") {
    CHECK(Rational(-2, 8) == Rational(3, -12));
	CHECK(Rational(2, 8) != Rational(-3, 12));
	CHECK(Rational(2, 8) >= Rational(3, 12));
	CHECK(Rational(2, 8) >= Rational(1, 12345));
	CHECK(Rational(2, 8) > Rational(3, 15));
	CHECK(Rational(-2, -8) <= Rational(3, 12));
	CHECK(Rational(1, 2345) < Rational(1, 123));
}
