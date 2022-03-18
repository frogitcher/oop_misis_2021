#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Rational.h"

TEST_CASE("Testing init and operational functions") {
	CHECK(Rational(3, 2) == Rational(3, 2));
	CHECK(Rational(4, 2) == Rational(2, 1));
	CHECK(Rational(3) == Rational(3, 1));
	CHECK(Rational(Rational(-5, 3)) == Rational(-5, 3));
	CHECK(Rational(-2, -6) == Rational(1, 3));
	CHECK(Rational(0, 2) == Rational(0, 1));
	CHECK(Rational(10, -3) == Rational(-10, 3));
	CHECK(Rational(0) == Rational(0, 10));
	CHECK(Rational(1, 5).getNum() == 1);
	CHECK(Rational(1, 5).getDet() == 5);
	CHECK(Rational(2, 4).getNum() == 1);
	CHECK(Rational(2, 4).getDet() == 2);
	CHECK_THROWS_WITH(Rational(10, 0), "Denominator cannot be equal to 0");
	//CHECK((double)Rational(1, 2) == 0.5);
	CHECK(Rational(3, 2).ToProperFraction() == std::make_pair(1, Rational(1, 2)));
}

TEST_CASE("Testing comparison operators") {
	CHECK(Rational(3, 1) == Rational(3, 1));
	CHECK(Rational(4, 3) < Rational(3, 2));
	CHECK(Rational(7, 5) > Rational(5, 7));
	CHECK(Rational(4, 5) >= Rational(2, 5));
	CHECK(Rational(4, 2) >= Rational(2));
	CHECK(Rational(10, 4) <= Rational(6, 2));
	CHECK(Rational(10, 4) <= Rational(10, 4));
	CHECK(Rational(3, 2) != Rational(1, 2));
	CHECK(Rational(-10, -11) > Rational(-10, 11));
	CHECK(Rational(-3, 5) < Rational(0));
	CHECK(!Rational(-5) == false);
	CHECK(!!Rational(5));
	CHECK(!Rational(0));
	CHECK(-Rational(1, 2) == Rational(-1, 2));
	CHECK(-Rational(1, 2) == Rational(1, -2));
}

TEST_CASE("Testing arithmetic operators") {
	CHECK(Rational(2, 3) + Rational(4, 3) == Rational(6, 3));
	CHECK(Rational(5, 3) + Rational(7, 6) == Rational(17, 6));
	CHECK(Rational(1, 3) + Rational(-2, 3) == Rational(-1, 3));
	CHECK(Rational(-3, 5) + Rational(-2, 5) == Rational(-1));
	CHECK(Rational(5, 3) + 3 == Rational(14, 3));
	CHECK(Rational(4, 3) - Rational(8, 6) == Rational(0));
	CHECK(Rational(7, 6) - Rational(5, 4) == Rational(-1, 12));
	CHECK(Rational(17, 5) - Rational(12, 7) == Rational(59, 35));
	CHECK(Rational(-1, 2) - Rational(-2, 3) == Rational(1, 6));
	CHECK(Rational(9, 4) - 2 == Rational(1, 4));
	CHECK(Rational(6) - 5 == Rational(1));
	CHECK(Rational(5, 2) * Rational(7, 3) == Rational(35, 6));
	CHECK(Rational(-9, 2) * Rational(1, 3) == -Rational(3, 2));
	CHECK(Rational(4, 3) * 0 == Rational(0, 1));
	CHECK(Rational(4, 3) * 10 == Rational(40, 3));
	CHECK(Rational(40, 3) / Rational(4, 3) == Rational(10));
	CHECK(Rational(4, 1) / 4 == Rational(1));
	CHECK(Rational(-9, 2) / Rational(-12, 5) == Rational(15, 8));
	CHECK_THROWS_WITH(Rational(5, 2) / Rational(0, 1), "Denominator cannot be equal to 0");
	CHECK_THROWS_WITH(Rational(5, 2) / 0, "Denominator cannot be equal to 0");
	CHECK(Rational(Rational(2, 3) += Rational(4, 3)) == Rational(2));
	CHECK(Rational(Rational(2, 3) -= Rational(2, 3)) == Rational(0));
	CHECK(Rational(Rational(2, 3) *= Rational(2, 3)) == Rational(4, 9));
	CHECK(Rational(Rational(2, 3) /= Rational(2, 3)) == Rational(1));
	CHECK(--Rational(1) == Rational(0));
	CHECK(++Rational(1) == Rational(2));
	CHECK(Rational(1, 3)++ == Rational(1, 3));
	CHECK(Rational(1, 3)-- == Rational(1, 3));
	CHECK(--Rational(2, 3) + -Rational(1, -3) == Rational(0));
}