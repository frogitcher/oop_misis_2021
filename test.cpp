#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "rac.h"
#include "rac.cpp"
#include <string>

TEST_CASE("testing rac class") {
	int a = 2, c=1;
	rational r1(1,2),r2(2,3);
	CHECK(r1 + a == rational(5,2));
	CHECK(r1 + a == a + r1);//rac + int
	CHECK(++r1 + a == rational(7,2));
	CHECK(r1 == rational(3,2));
	--r1;
	CHECK(r1 == rational(1,2));
	CHECK(r1 - a == rational(-3,2));//rac - int
	CHECK(a - r1 == rational(3,2));//int - rac
	r1++;
	CHECK(r1 == rational(3,2));
	r1--;
	CHECK(r1 == rational(1,2));
	r1 += a;
	CHECK(r1 == rational(5,2));
	r1 -= c;
	CHECK(r1 == rational(3,2));
	r1--;
	CHECK(r1 * a == rational(1,1));//rac*int
	CHECK(a*r1 == r1*a);//int*rac
	CHECK(r1/a == rational(1,4));//rac/int
	CHECK(a/r1 == rational(4,1));//int/rac
	CHECK(r1 + r2 == rational(7,6));//rac+rac
	CHECK(r1 + r2 == r2 + r1);
	CHECK(r1 - r2 == rational(-1,6));//rac-rac
	CHECK(r2 - r1 == rational(1,6));
	CHECK(r1 - r2 == (r2 - r1)*-1);
	CHECK(r1 * r2 == rational(1,3));//rac*rac
	CHECK(r1 * r2 == r2*r1);
	CHECK(r1 / r2 == rational(3,4));//rac/rac
	CHECK(r2 / r1 == rational(4,3));
}
