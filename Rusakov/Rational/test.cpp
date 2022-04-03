#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"
#include <iostream>

TEST_CASE("test exception when denominator equal 0") {
	CHECK_THROWS_WITH(Rational(2, 0), "exception - denominator must be more then 0");
}

TEST_CASE("test Normalize void") {
	CHECK(Rational(2, 4) == Rational(1, 2));
	CHECK(Rational(-3, 6) == Rational(-1, 2));
}

TEST_CASE("test Rational(const Rational& other) void") {
	CHECK(Rational(Rational(1,2)) == Rational(1, 2));
	CHECK(Rational(Rational(-3, 6)) == Rational(-1, 2));
}

TEST_CASE("test bool operators") {
	CHECK(Rational(1, 2) == Rational(1, 2));
	CHECK(Rational(2, 4) == Rational(1, 2));

	CHECK(Rational(-11, 20) != Rational(11,20));
	CHECK(Rational(0, 4) != Rational(1, 8));

	CHECK(Rational(1, 2) > Rational(1, 4));
	CHECK(Rational(2, 4) > Rational(-1, 2));
	CHECK(Rational(1, 4) > Rational(1, 8));
	CHECK(Rational(100, 1) > Rational(1,40));

	CHECK(Rational(1, 4) < Rational(1));
	CHECK(Rational(-11, 2) < Rational(11, 2));
	CHECK(Rational(10) < Rational(100));
}

TEST_CASE("test unary operators") {
	CHECK((Rational(1, 2) += Rational(1, 2)) == Rational(1, 1));
	CHECK((Rational(-1, 2) += Rational(1, 2)) == Rational(0));
	CHECK((Rational(1, 4) += Rational(1, 8)) == Rational(3,8));

	CHECK((Rational(1, 2) -= Rational(1, 2)) == Rational(0));
	CHECK((Rational(1) -= Rational(-1, 2)) == Rational(1,2));
	CHECK((Rational(-1, 4) -= Rational(-1, 4)) == Rational(-1, 2));

	CHECK((Rational(1, 2) *= Rational(3)) == Rational(3,2));
	CHECK((Rational(2) *= Rational(-1, 2)) == Rational(-1));
	CHECK((Rational(-1, 4) *= Rational(-1, 4)) == Rational(1, 16));

	CHECK((Rational(-2, 9) /= Rational(-2,9)) == Rational(1));
	CHECK((Rational(2) /= Rational(-1)) == Rational(-2));
	CHECK((Rational(-1) /= Rational(1, 2)) == Rational(-2));
	CHECK((Rational(100,1) /= Rational(1, 2)) == Rational(200));
}

TEST_CASE("test binary operators") {
	CHECK((Rational(1, 2) + Rational(1, 2)) == Rational(1, 1));
	CHECK((Rational(-1, 2) + Rational(1, 2)) == Rational(0));
	CHECK((Rational(1, 4) + Rational(1, 8)) == Rational(3, 8));

	CHECK((Rational(1, 2) - Rational(1, 2)) == Rational(0));
	CHECK((Rational(1) - Rational(-1, 2)) == Rational(1, 2));
	CHECK((Rational(-1, 4) - Rational(-1, 4)) == Rational(-1, 2));

	CHECK((Rational(1, 2) * Rational(3)) == Rational(3, 2));
	CHECK((Rational(2) * Rational(-1, 2)) == Rational(-1));
	CHECK((Rational(-1, 4) * Rational(-1, 4)) == Rational(1, 16));

	CHECK((Rational(-2, 9) / Rational(-2, 9)) == Rational(1));
	CHECK((Rational(2) / Rational(-1)) == Rational(-2));
	CHECK((Rational(-1) / Rational(1, 2)) == Rational(-2));
	CHECK((Rational(100, 1) / Rational(1, 2)) == Rational(200));
	CHECK_THROWS_WITH(Rational(1, 1) / Rational(0), "exception - denominator must be more then 0");
}

TEST_CASE("test binary operators") {
	CHECK(++Rational(1) == Rational(2));
	CHECK(++Rational(-1, 2) == Rational(1, 2));
	CHECK(++Rational(1, 3) == Rational(4, 3));

	CHECK(--Rational(1, 1) == Rational(0));
	CHECK(--Rational(-1, 2) == Rational(-3, 2));

}

TEST_CASE("test unary operators") {
	Rational a = Rational(1,2);
	CHECK(a++ == Rational(1,2));
	CHECK(a == Rational(3, 2));

	Rational b = Rational(1, 2);
	CHECK(b-- == Rational(1, 2));
	CHECK(b == Rational(-1, 2)); 
}