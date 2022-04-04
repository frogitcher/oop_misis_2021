#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "din_mas.h"
#include <string>

TEST_CASE("testing din_mas") {
	DinamicArray a(3,2);
	CHECK(a.Size() == 3);
	CHECK(*a.begin() == a[0]);
	a.insert(1,3);
	CHECK(a.Size() == 4);
	CHECK(a[1] == 3);
	a.pop_back();
	CHECK(a.Size() == 3);
	a.push_back(5);
	CHECK(a.Size() == 4);
	CHECK(a[a.Size()-1] == 5);
	CHECK(*(a.end()-1) == 5);
	//a.clear();
	//CHECK(a.Size() == 0);
	a.resize(3);
	CHECK(a.Size() == 3);
	DinamicArray b(1,2);
	CHECK(!(b == a));
	a.clear();
	a.assign(3,4);
	CHECK(a.Size() == 3);
}
