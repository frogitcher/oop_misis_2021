#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"
#include "iostream"
using namespace std;

TEST_CASE("initialization") {
	Rational z(7, 8), x(-7, 8), c(7, -8), cursed(6, 7);

	CHECK(x == c);
	CHECK(Rational(-14, 16) == x);
	CHECK(Rational(14, -16) == x);
	CHECK(Rational(12, 14) == cursed);

	CHECK(Rational(10) == Rational(10, 1));
	CHECK(Rational(40, 5) == Rational(80, 10));
}

TEST_CASE("throws") {
	CHECK_THROWS_WITH(Rational(100, 0), "Denominator != 0");
	CHECK_THROWS_WITH(Rational(100) / 0, "Division by 0");
	CHECK_THROWS_WITH(Rational(100) / Rational(0, 10), "Division by 0");
}

TEST_CASE("basic arithmetics") {
	Rational z(1, 2), x(1), c(-1, 2), cursed(1, 7), y(2);
	CHECK(x + z == Rational(3, 2));
	CHECK(-z + x == z);
	CHECK(x - z == z);
	CHECK(z + z == x);
	CHECK(z + c == Rational(0));

	CHECK(x * y == y);
	CHECK(y * z == x);
	CHECK(z * c == Rational(-1, 4));
	CHECK(z * cursed == Rational(1, 14));

	CHECK(z / y == Rational(1, 4));
	CHECK(z / cursed == Rational(7, 2));
	CHECK(z / c == Rational(-1));
	CHECK(z / c == -x);
}

TEST_CASE("pre-increment and post-increment") {
	Rational x(7, 8);
	Rational x0 = x;
	Rational inc = x + Rational(1);
	Rational dec = x - Rational(1);
	CHECK(x++ == x0);
	CHECK(x == inc);

	CHECK(x-- == inc);
	CHECK(x == x0);

	CHECK(++x == inc);
	CHECK(--x == x0);
	CHECK(x == x0);
}

TEST_CASE("boolean operators") {
	Rational z(7, 8), x(-7, 8), c(7, -8), cursed(6, 7);

	CHECK(z > cursed);
	CHECK(cursed < z);
	CHECK(cursed != z);
	CHECK(cursed <= z);
	CHECK(z >= cursed);

	CHECK(Rational(-5, 8) > x);
	CHECK(Rational(-1) < x);
	CHECK(Rational(1) > z);
	CHECK(!(Rational(1) <= z));
}

// Comment out this section if you want, was tinkering with doctest
TEST_SUITE("") {
	TEST_CASE("brute") {
		for (int i = -100; i <= 100; i++) {
			for (int j = -100; j <= 100; j++) {
				if (i == 0 || j == 0) {
					continue;
				} else {
					auto x = Rational(i, j);
					auto y = Rational(j, i);
					CHECK(x / x == Rational(1));
					CHECK(x + x == Rational(2 * i, j));
					CHECK(x - x == Rational(0));
					SUBCASE("Comparators") {
						CHECK(x * x == Rational(i * i, j * j));
					}
				}
			}
		}
	}
}
