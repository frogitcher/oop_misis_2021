#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Numbers.h"

TEST_CASE("Rational") {
	Rational a(1, -2), b(3, 4), c(-5, 6), d(7, 2);

	// +,-,*,/
	CHECK(a + b == Rational(1, 4));
	CHECK(a - d == Rational(-4));
	CHECK(c * d == Rational(-35, 12));
	CHECK(a / b == Rational(-2, 3));
	CHECK((a - b) * c + b / d == Rational(211, 168));

	// +=,-=,*=,/=
	CHECK((c += b) == Rational(-1, 12));
	CHECK((a -= d) == Rational(-4));
	CHECK((b *= d) == Rational(21, 8));
	CHECK((d /= 9) == Rational(7, 18));

	Rational q(11, 2), w(-4, 4), e(8, 6), r(5, 2);

	// >,<,>=,<=,!=,==
	CHECK(q > Rational(1, 12));
	CHECK(w < Rational(5));
	CHECK(e >= Rational(16, 12));
	CHECK(r <= Rational(100, 18));
	CHECK(r != Rational(6, 18));
	CHECK((r == Rational(5, 2)) == true);
	CHECK((q != Rational(11, 2)) == false);
	CHECK((w == Rational(11, 2)) == false);

	// ++,--, -, +
	CHECK(++q == Rational(13, 2));
	CHECK(q == Rational(13, 2));
	CHECK(--r == Rational(3, 2));
	CHECK(r == Rational(3, 2));
	CHECK(w++ == Rational(-1, 1));
	CHECK(w == Rational());
	CHECK(e-- == Rational(8, 6));
	CHECK(e == Rational(2, 6));
	CHECK(-Rational(3, 4) == Rational(-3, 4));
	CHECK(-Rational(3, -4) == Rational(3, 4));
	CHECK(+Rational(3, 4) == Rational(3, 4));

	//exceptionj
	CHECK_THROWS_WITH(Rational(1, 0), "denominator - 0");
	CHECK_THROWS_WITH(Rational(-3, 0), "denominator - 0");
}