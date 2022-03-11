#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Rational.h"

TEST_CASE("Testing Rational.h") {
	CHECK(Rational(10,3).operator>(Rational(10, 7)));
	CHECK(Rational(2, 3).operator-().getNum() == -2);
	CHECK(Rational(10, 5).operator+(Rational(3, 10)).getNum() == 23);
	CHECK(Rational(6, 2).getDet() == 1);
	CHECK(Rational(3, 2).operator+(3).getNum() == 9);
	CHECK(Rational(3, 2).ToProperFraction().first == 1);
}