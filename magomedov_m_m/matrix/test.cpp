#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "flat.h"
#include "matrix.h"
#include "table.h"
#include "doctest.h"


TEST_CASE("Testing table matrix") {
	Table<int> a(5, 6, 1);
	CHECK(a.Get(1,3)==1);
	CHECK(a[1][3]==1);
	CHECK_THROWS_WITH(a.Get(5,4),"chel ti v mute");
	CHECK(a.Get_c() == 6);
	CHECK(a.Get_r() == 5);
	Table<int> b(3, 3, 5);
	CHECK_THROWS_WITH(a += b, "chel ti v mute");
	Table<int>c(a);
	a += c;
	CHECK(a[0][0]==2);
	Table<int> m({ { 1,2,3 }, { 1,2,3 } });
	CHECK(m.Get_r() == 2);
	CHECK(m.Get_c() == 3);
	CHECK(m[0][0] == 1);
	CHECK(m[0][1] == 2);
	CHECK(m[0][2] == 3);
	CHECK(m[1][0] == 1);
	CHECK(m[1][1] == 2);
	CHECK(m[1][2] == 3);
	CHECK_THROWS_WITH(m.Get(5, 4), "chel ti v mute");


}
TEST_CASE("Testing flat matrix") {
	Flat<int> a(5, 6, 1);
	CHECK(a.Get(1, 3) == 1);
	CHECK(a[1][3] == 1);
	CHECK_THROWS_WITH(a.Get(5, 4), "chel ti v mute");
	CHECK(a.Get_c() == 6);
	CHECK(a.Get_r() == 5);
	Flat<int> b(3, 3, 5);
	CHECK_THROWS_WITH(a += b, "impossible");
	Flat<int>c(a);
	a += c;
	CHECK(a[0][0] == 2);
	Flat<int> m({ { 1,2,3 }, { 1,2,3 } });
	CHECK(m.Get_r() == 2);
	CHECK(m.Get_c() == 3);
	CHECK(m[0][0] == 1);
	CHECK(m[0][1] == 2);
	CHECK(m[0][2] == 3);
	CHECK(m[1][0] == 1);
	CHECK(m[1][1] == 2);
	CHECK(m[1][2] == 3);
	CHECK_THROWS_WITH(m.Get(5, 4), "chel ti v mute");
}