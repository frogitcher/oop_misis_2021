#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Arithmetic operations and normalization") 
{
	//Normalization
	CHECK(Rational(2, 4) == Rational(1, 2));
	CHECK(Rational(5, 5) == Rational(1));
	CHECK(Rational(5, -1) == Rational(-5));

	//Operations
	CHECK(Rational(1, 2) + Rational(1, 2) == Rational(1));
	CHECK(Rational(3, 5) + Rational(3, -5) == Rational(0));
	CHECK(Rational(0, 123) + Rational(1) == Rational(1));
	CHECK(Rational(1, 2) - Rational(2, 2) == Rational(-1, 2));
	CHECK(Rational(1, 2) - Rational(0) == Rational(1, 2));
	CHECK(Rational(0) - Rational(5, 7) == Rational(-5, 7));
	CHECK(Rational(4, 5) * Rational(4, 5) == Rational(16, 25));
	CHECK(Rational(0) * Rational(3, 7) == Rational(0));
	CHECK(Rational(12) * Rational(0) == Rational(0));
	CHECK(Rational(0) / Rational(1) == Rational(0));
	CHECK(Rational(1, 8) / Rational(1, 8) == Rational(1));
	CHECK((Rational(12, 15) += Rational(4, 5)) == Rational(8, 5));
	CHECK((Rational(12, 15) -= Rational(8, 5)) == Rational(-4, 5));
	CHECK((Rational(12, 15) /= Rational(8, 5)) == Rational(1, 2));


}

TEST_CASE("Boolean functions")
{
	CHECK(Rational(12, 5) == Rational(12, 5));
	CHECK(Rational(12, 4) == Rational(3));
	CHECK(Rational(321, 123) != Rational(1, 2));
	CHECK(Rational(111, 32) > Rational(-32, 123));
	CHECK(Rational(123, 32) >= Rational(32, 123));
	CHECK(Rational(1) >= Rational(1));
	CHECK(Rational(32, 1) < Rational(32323, 2));
	CHECK(Rational(87, 3) <= Rational(88, 3));
	CHECK(Rational(54, 4) <= Rational(54, 4));

}

TEST_CASE("Unary operators")
{
	CHECK(+Rational(32, 2) == Rational(16));
	CHECK(-Rational(31, 5) == Rational(-31, 5));
	CHECK((++Rational(1, 2) == Rational(3, 2)));
	Rational t(4, 5);
	t++;
	CHECK(t == Rational(9, 5));
	t--;
	CHECK(t == Rational(4, 5));
	CHECK(++t == Rational(9, 5));
	CHECK(--t == Rational(4, 5));
}

TEST_CASE("Other functions and exceptions")
{
	CHECK(Rational(4, 3).GetNumerator() == 4);
	CHECK(Rational(3, 5).GetDenominator() == 5);
	CHECK(Rational(5).GetDenominator() == 1);
	CHECK_THROWS_WITH(Rational(5, 0), "Denominator must not be equal 0.");
	CHECK_THROWS_WITH(Rational(4, 5) / Rational(0), "Division by zero.");
}