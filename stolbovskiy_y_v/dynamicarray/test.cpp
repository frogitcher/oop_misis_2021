#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamicarray.h"

TEST_CASE("testing dynamic arrays") {
	dynamicarray a(3, 1);
	CHECK(a.Size() == 3);
	a.clear();
	CHECK(a.empty());

	a = { 0,1,2,3,4 };
	CHECK(a.Size() == 5);
	CHECK(a[0] == 0);
	CHECK(a[2] == 2);
	a.push_back(5);
	CHECK(a[5] == 5);
	a.pop_back();
	CHECK(a.Size() == 5);
	a.resize(6);
	CHECK(a.Size() == 6);
	CHECK(a[5] == 0);

	a.erase(3);
	CHECK(a.Size() == 5);
	CHECK(a[3] == 4);
	a.insert(3, 3);
	CHECK(a.Size() == 6);
	CHECK(a[3] == 3);

	a.assign(100, 1);
	CHECK(a.Size() == 100);
	CHECK(a[99] == 1);

	a.assign(5, 1);
	a[2] = 2;

	dynamicarray b(a);
	CHECK(b == a);
	a.swap(b);
	CHECK(a == b);
	CHECK(b[1] == 1);

	CHECK(*(a.begin()) == 1);
}

TEST_CASE("testing exceptions") {
	CHECK_THROWS_WITH(dynamicarray(5,0).at(5), "index out of range");
	CHECK_THROWS_WITH(dynamicarray(5, 0).insert(10, 10), "index out of range");
	CHECK_THROWS_WITH(dynamicarray(5, 0).erase(-1), "index out of range");
	CHECK_THROWS_WITH(dynamicarray({}).pop_back(), "empty array before pop");
	dynamicarray a(5, 0);
	CHECK_THROWS_WITH(a.resize(-5), "bad array new length");
	dynamicarray b(5, 0);
	CHECK_THROWS_WITH(b.assign(-5, 5), "bad array new length");
}