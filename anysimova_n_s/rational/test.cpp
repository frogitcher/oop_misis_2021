#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"


TEST_CASE("Rational constructors") {
	CHECK(Rational() == Rational(0, 1));
	CHECK(Rational(5) == Rational(5, 1));
	CHECK(Rational(-3, -4) == Rational(3, 4));
	CHECK(Rational(3, -4) == Rational(-3, 4));
	CHECK(Rational(5, 10) == Rational(1, 2));
	CHECK_THROWS_WITH(Rational(1, 0), "You cannot divide by zero");
}

TEST_CASE("Rational arithmetic & assignment") {
	Rational a; Rational b(1, 3);
	a = b; CHECK(a == b);
	CHECK(-Rational(1, 2) == Rational(-1, 2));
	CHECK(Rational(1, 4) + Rational(1, 8) == Rational(3, 8));
	CHECK(Rational(1, 4) - Rational(1, 8) == Rational(1, 8));
	CHECK(Rational(2, 3) * Rational(1, 8) == Rational(1, 12));
	CHECK(Rational(1, 4) / Rational(1, 8) == Rational(2, 1));
	CHECK((Rational(8, 15) += Rational(9, 35)) == Rational(83, 105));
	CHECK((Rational(8, 15) -= Rational(9, 35)) == Rational(29, 105));
	CHECK((Rational(8, 15) *= Rational(9, 35)) == Rational(24, 175));
	CHECK((Rational(8, 15) /= Rational(9, 35)) == Rational(56, 27));
	CHECK_THROWS_WITH(Rational(1, 4) / Rational(0, 8), "You cannot divide by zero");
	CHECK_THROWS_WITH(Rational(1, 4) /= Rational(0, 8), "You cannot divide by zero");
}

TEST_CASE("Rational increment & decrement") {
	Rational a(1, 3); Rational b(1, 3); Rational c(2, 5);
	c = b++;
	CHECK(c == Rational(1, 3));
	CHECK(b == Rational(4, 3));
	c = ++b;
	CHECK(c == Rational(7, 3));
	CHECK(b == Rational(7, 3));
	a = b--;
	CHECK(a == Rational(7, 3));
	CHECK(b == Rational(4, 3));
	a = --b;
	CHECK(a == Rational(1, 3));
	CHECK(b == Rational(1, 3));
}

TEST_CASE("Rational input/output") {
	Rational t(1, 2);
	std::ostringstream output;
	output << t;
	CHECK(output.str() == "1/2");
	std::istringstream input("5/3");
	input >> t;
	CHECK(t == Rational(5, 3));
}

TEST_CASE("Rational relational") {
	CHECK(Rational(5, 4) > Rational(1, 3));
	CHECK(Rational(5, 4) >= Rational(5, 4));
	CHECK(Rational(-5, 4) < Rational(1, 4));
	CHECK(Rational(-5, 4) <= Rational(-5, 4));
	CHECK(Rational(1, 2) != Rational(5, 8));
}