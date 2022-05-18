#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rational.h"


TEST_CASE("bool") {
	CHECK(rational(1, 5) < rational(1, 4));
	CHECK(rational(1, -5) < rational(1, 4));
	CHECK(rational(0, -5) == rational(0, 1));
	CHECK(rational(1, -5) == rational(-1, 5));
	CHECK(rational(1, -5) <= rational(-1, 5));
	CHECK(rational(4, -5) <= rational(-1, 5));
	CHECK(rational(-1, -5) > rational(1, 22));
	CHECK(rational(8, 24) >= rational(1, 3));
	CHECK(rational(-8, -24) >= rational(1, -33));
	CHECK(rational(100, 25) != rational(4, 2));
	CHECK(rational(100, -25) == rational(-4, 1));
	CHECK(rational(100, 25) != rational(-4, 1));
	CHECK(rational(100, 25) != rational(-4, 1));


}
TEST_CASE("arifmetica") {
	CHECK((rational(1, 5) += rational(1, 4)) == rational(9, 20));
	CHECK((rational(2, 3) + rational(1, 3)) == rational(1, 1));
	CHECK((rational(23, 8) - rational(0, 6)) == rational(23, 8));
	CHECK((rational(23, 8) * rational(23, 8)) == rational(529, 64));
	CHECK((rational(23, 8) / rational(23, 4)) == rational(1, 2));
	CHECK((rational(23, 8) -= rational(0, 6)) == rational(23, 8));
	CHECK((rational(0, 8) *= rational(23, 8)) == rational(0, 1));
	CHECK((rational(23, 8) /= rational(23, 4)) == rational(1, 2));
	CHECK((rational(40, 2) = rational(2, 4)) == rational(1, 2));
	CHECK(rational(555551, 666666) + rational(123456, 654321) == rational(148604201189, 145404521262));
}
TEST_CASE("++ --") {
	CHECK((rational(40, 2)++) == rational(21, 1));
	CHECK(++(rational(40, 2)) == rational(21, 1));
	CHECK((rational(40, 2)--) == rational(19, 1));
	CHECK(--(rational(40, 2)) == rational(19, 1));

}