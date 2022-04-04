#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "rac_chisl.h"
#include <string>

TEST_CASE("testing rac class") {
	CHECK(f(0,1,2,3) == rac(7,2));//rac + int
	CHECK(f(1,1,2,3) == rac(7,2));//int + rac
	CHECK(f(2,1,2,3) == rac(-5,2));//rac - int
	CHECK(f(3,1,2,3) == rac(5,2));//int - rac
	CHECK(f(4,1,2,3) == rac(3,2));//rac*int
	CHECK(f(5,1,2,3) == rac(3,2));//int*rac
	CHECK(f(6,1,2,3) == rac(1,6));//rac/int
	CHECK(f(7,1,2,3) == rac(6,1));//int/rac
	CHECK(f(8,1,2,1,3) == rac(5,6));//rac+rac
	CHECK(f(9,1,2,1,3) == rac(1,6));//rac-rac
	CHECK(f(10,1,2,1,3) == rac(1,6));//rac*rac
	CHECK(f(11,1,2,1,3) == rac(3,2));//rac/rac
}
