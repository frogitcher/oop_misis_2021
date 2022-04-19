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
	CHECK((-Rational(12, 7) == Rational(12, -7)));
	CHECK((-Rational(57, 3) == Rational(-57, 3)));
}

TEST_CASE("Arithmetic Testing") {

	CHECK((Rational(1, 2) + Rational(1, 3) == Rational(5, 6)));
	CHECK((Rational(1, 2) - Rational(1, 3) == Rational(1, 6)));
	CHECK((Rational(5, 11) * Rational(11, 5) == Rational(1, 1)));
	CHECK((Rational(30, 6) / Rational(1, 6) == Rational(30, 1)));

	CHECK((Rational(-25, 6) / Rational(-1, 6) == Rational(25, 1)));
	CHECK((Rational(3, 9) * Rational(9, -3) == Rational(1, -1)));
	CHECK((Rational(-1, -2) - Rational(-1, -3) == Rational(-1, -6)));
	CHECK((Rational(1, 2) + Rational(-1, 3) == Rational(1, 6)));

	CHECK((Rational(123456789, 6) / Rational(1, 6) == Rational(123456789, 1)));
	CHECK((Rational(5000, 1000) * Rational(1000, 10) == Rational(500, 1)));
	CHECK((Rational(3333333, 3) + Rational(222, 2) == Rational(1111222,1)));
	CHECK((Rational(10000, 2) - Rational(100, 2) == Rational(4950, 1)));
	CHECK((Rational(10000, 2) - Rational(10000, 2) == Rational(0, 1)));

	CHECK(((Rational(123456789, 6) / Rational(1, 6) == Rational(123456789, 2)) == false));
	CHECK(((Rational(5000, 1000) * Rational(1000, 10) == Rational(500, 123)) == false));
	CHECK(((Rational(3333333, 3) + Rational(222, 2) == Rational(1111222, 13)) == false));
	CHECK(((Rational(10000, 2) - Rational(100, 2) == Rational(0, 1)) == false));
}

TEST_CASE("Reassigment Testing") {

	CHECK((((Rational(20, 10) += Rational(40, 8)) == Rational(14, 2))));
	CHECK((((Rational(5, 1) -= Rational(3, 2)) == Rational(35, 10))));
	CHECK((((Rational(2, 1) *= Rational(2, 1)) == Rational(4, 1))));
	CHECK((((Rational(4, 1) /= Rational(2, 1)) == Rational(2, 1))));
	CHECK(((++Rational(28, 5)) == Rational(66, 10)));
	CHECK((((--Rational(43, 3)) == Rational(80, 6))));

	Rational x(28, 5);
	x++;
	CHECK((x == Rational(66, 10)));
	CHECK(((x == Rational(46, 10)) == false));
	x--;
	CHECK((x == Rational(56, 10)));
	CHECK(((x == Rational(96, 10)) == false));

	CHECK(((((Rational(20, 10) += Rational(40, 8)) == Rational(14, 22))) == false));
	CHECK(((((Rational(35, 10) -= Rational(7, 8)) == Rational(44, 9))) == false));
	CHECK(((((Rational(2011, 10) *= Rational(4067, 8)) == Rational(14, 52))) == false));
	CHECK(((((Rational(1820, 10) += Rational(3340, 8)) == Rational(1344, 92))) == false));
	CHECK((((++Rational(28, 5)) == Rational(666, 10)) == false));
	CHECK(((((--Rational(43, 3)) == Rational(80, 61))) == false));
}

TEST_CASE("Logical Testing") {

	CHECK((Rational(1, 2) > Rational(1, 6)));
	CHECK((Rational(1, 4) >= Rational(1, 6)));
	CHECK((Rational(1, 11) < Rational(5, 11)));
	CHECK((Rational(30, 6) <= Rational(30, 4)));
	CHECK((Rational(30, 6) != Rational(30, 4)));
	CHECK((Rational(100, 10) == Rational(10, 1)));

	CHECK(((Rational(100, 13) == Rational(145, 12))) == false);
	CHECK(((Rational(1, 4) > Rational(1, 2))) == false);
	CHECK(((Rational(2, 5) < Rational(1, 5)) == false));
	CHECK(((Rational(2, 5) < Rational(2, 5)) == false));
	CHECK(((Rational(122121, 5) <= Rational(1111, 3)) == false));
	CHECK(((Rational(78765, 5) >= Rational(5432167, 3)) == false));
	CHECK(((Rational(2323, 5) != Rational(4646, 10)) == false));
}

TEST_CASE("Denominator = 0 Testing") {

	CHECK_THROWS((Rational(1, 0))); 
	CHECK_THROWS((Rational(1, 0) - Rational(0,0)));
	CHECK_THROWS((Rational(1000000000, 0)));
	CHECK_THROWS((Rational(0, 0)));
	CHECK_THROWS((Rational(1, 1) / Rational(0, 1)));
	CHECK_THROWS((Rational(1, 1) /= Rational(0, 1)));
}