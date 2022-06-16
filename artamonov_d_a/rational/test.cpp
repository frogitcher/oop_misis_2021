#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"

TEST_CASE("Testing initialization.") {
	CHECK(Rational(2) == Rational(2, 1));
	CHECK(Rational(11, 3).get_numerator() == 11);
	CHECK(Rational(11, 3).get_denumerator() == 3);
	CHECK(Rational(30, 20).get_numerator() == 3);
	CHECK(Rational(30, 20).get_denumerator() == 2);
	CHECK(Rational(11, -3) == Rational(-11, 3));
	CHECK(Rational(30, 20) == Rational(3, 2));
	CHECK(Rational(-3, -2) == Rational(3, 2));
	CHECK(Rational(0, 10000) == Rational(0, 1));
	CHECK(Rational(Rational(7, 2))==Rational(7, 2));
	CHECK_THROWS_WITH(Rational(10000, 0), "Denominator != 0");
	}

TEST_CASE("Testing arithmetics operators.") {
	CHECK(Rational(1, 2) + Rational(1, 2) == Rational(1, 1));
	CHECK(Rational(3, 3) - Rational(1, 2) == Rational(2, 4));
	CHECK(Rational(1, 3) - Rational(5, 3) == Rational(-4, 3));
	CHECK(Rational(2, 5) * Rational(1, 2) == Rational(2, 10));
	CHECK(Rational(5, 1) / Rational(1, 2) == Rational(10, 1));
	CHECK(Rational(4, 3) / Rational(-3, 4) == Rational(-16, 9));
	CHECK((Rational(5, 1) += Rational(3, 1)) == Rational(8, 1));
	CHECK((Rational(5, 1) *= Rational(0, 5)) == Rational(0));
	CHECK((Rational(7, 2) -= Rational(0, 5723)) == Rational(7, 2));
	CHECK((Rational(8, 2) /= Rational(1, 2)) == Rational(8, 1));
	CHECK_THROWS_WITH(Rational(8, 2) /= Rational(0, 2), "Division by 0");
	CHECK(Rational(2, 1) + Rational(-2, 1) == Rational(0));
	CHECK(Rational(3, 8) - Rational(1, 8) == Rational(1, 4));
	CHECK(Rational(0, 3) - Rational(0, 3) == Rational(0));
	CHECK(Rational(2, 12) * Rational(12, 2) == Rational(1, 1));
	CHECK(Rational(5, 1) / Rational(1, 5) == Rational(25, 1));
	CHECK(Rational(0, 1) / Rational(100, 4) == Rational(0, 1));
	CHECK((Rational(5, 3) += Rational(3, 5)) == Rational(34, 15));
	CHECK((Rational(5, 1) *= Rational(9, 5)) == Rational(9, 1));
	CHECK((Rational(7, 2) -= Rational(2, 2)) == Rational(5, 2));
	CHECK((Rational(100, 4) /= Rational(5, 1)) == Rational(5, 1));
}

TEST_CASE("Testing operators of order.") {
	CHECK(Rational(5, 6) > Rational(2, 3));
	CHECK(Rational(5, 6) > Rational(-11, 3));
	CHECK(Rational(2, 3) < Rational(5, 6));
	CHECK(Rational(-2, 3) < Rational(1, 6));
	CHECK(Rational(5, 6) >= Rational(5, 6));
	CHECK(Rational(5, 6) >= Rational(2, 3));
	CHECK(Rational(5, 6) <= Rational(5, 6));
	CHECK(Rational(2, 3) <= Rational(5, 6));
	CHECK(Rational(2, 3) == Rational(4, 6));
	CHECK(Rational(2, 3) != Rational(3, 6));
	CHECK(Rational(0, 3) == Rational(0, 6));
	CHECK(!(Rational(5, 6) < Rational(2, 3)));
	CHECK(!(Rational(5, 6) < Rational(-11, 3)));
	CHECK(!(Rational(2, 3) > Rational(5, 6)));
	CHECK(!(Rational(-2, 3) > Rational(1, 6)));
	CHECK(!(Rational(5, 6) < Rational(5, 6)));
	CHECK(!(Rational(5, 6) <= Rational(2, 3)));
	CHECK(!(Rational(5, 6) > Rational(5, 6)));
	CHECK(!(Rational(2, 3) >= Rational(5, 6)));
	CHECK(!(Rational(2, 3) != Rational(4, 6)));
	CHECK(!(Rational(2, 3) == Rational(3, 6)));
	CHECK(!(Rational(0, 3) != Rational(0, 6)));
}
