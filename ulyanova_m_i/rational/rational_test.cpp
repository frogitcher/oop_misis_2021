#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Rational.h"
#include "doctest.h"

TEST_CASE("Main Testing") {

	CHECK((Rational() == Rational(0, 1)));
	CHECK((Rational() == Rational(0, 123)));
	CHECK((Rational(2, 4) == Rational(1, 2)));
	CHECK((Rational(2, -4) == Rational(1, -2)));
	CHECK((Rational(-2, -4) == Rational(1, 2)));
	CHECK((Rational(-2, 4) == Rational(-1, 2)));
	CHECK((Rational(0, 7) == Rational(0, 1)));
}

TEST_CASE("Arithmetic Testing") {

	CHECK((Rational(1, 2) + Rational(1, 3) == Rational(5, 6)));
	CHECK((Rational(1, 2) - Rational(1, 3) == Rational(1, 6)));
	CHECK((Rational(5, 11) * Rational(11, 5) == Rational(1, 1)));
	CHECK((Rational(30, 6) / Rational(1, 6) == Rational(30, 1)));
}

TEST_CASE("Reassigment Testing") {

	CHECK((((Rational(20, 10) += Rational(40, 8)) == Rational(14, 2))));
	CHECK((((Rational(5, 1) -= Rational(3, 2)) == Rational(35, 10))));
	CHECK((((Rational(2, 1) *= Rational(2, 1)) == Rational(4, 1))));
	CHECK((((Rational(4, 1) /= Rational(2, 1)) == Rational(2, 1))));
	CHECK(((++Rational(28, 5)) == Rational(66, 10)));
	CHECK((((--Rational(43, 3)) == Rational(80, 6))));
}

TEST_CASE("Logical Testing") {

	CHECK((Rational(1, 2) > Rational(1, 6)));
	CHECK((Rational(1, 4) >= Rational(1, 6)));
	CHECK((Rational(1, 11) < Rational(5, 11)));
	CHECK((Rational(30, 6) <= Rational(30, 4)));
	CHECK((Rational(30, 6) != Rational(30, 4)));
	CHECK((Rational(100, 10) == Rational(10, 1)));
}

TEST_CASE("Denominator = 0 Testing") {

	CHECK_THROWS((Rational(1, 0))); 
	CHECK_THROWS((Rational(1, 0) - Rational(0,0)));
	CHECK_THROWS((Rational(1000000000, 0)));
	CHECK_THROWS((Rational(0, 0)));
}