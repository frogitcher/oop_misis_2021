#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "din.h"
#include "din.cpp"
#include <string>

TEST_CASE("testing din_mas") {
	DinamicArray a(3,2);
	CHECK(a.Size() == 3);
	CHECK(*a.begin() == a[0]);
	a.Insert(1,3);
	CHECK(a.Size() == 4);
	CHECK(a[1] == 3);
	a.Pop_back();
	CHECK(a.Size() == 3);
	a.Push_back(5);
	CHECK(a.Size() == 4);
	CHECK(a[a.Size()-1] == 5);
	CHECK(*(a.end()-1) == 5);
	//a.Clear();
	//CHECK(a.Size() == 0);
	a.Resize(3);
	CHECK(a.Size() == 3);
	DinamicArray b(1,2);
	CHECK(!(b == a));
	a.Clear();
	a.Assign(3,4);
	CHECK(a.Size() == 3);
}
