#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"
TEST_CASE("testing constructors and editors") {
	DynamicArray a(1);
	DynamicArray b(3, 1);
	DynamicArray c = { 1, 1, 1 };
	DynamicArray d(b);
	CHECK(a.Size() == 1);
	CHECK(b.Size() == 3);
	CHECK(c.Size() == 3);
	CHECK(b == c);
	CHECK(d == b);
	CHECK_THROWS_WITH((c.at(4) == 1), "Index out of range");
	CHECK_THROWS_WITH((c.at(-1) == 1), "Index out of range");
}
TEST_CASE("testing and compare editors") {
	DynamicArray a(1);
	DynamicArray b(3, 4);
	DynamicArray c = { 1, 1, 1 };
	DynamicArray d = b;
	CHECK(a.Size() == a.Capacity());
	a.push_back(1);
	CHECK(a.Size() == 2);
	CHECK(a[1] == 1);
	a.pop_back();
	CHECK(a.Size() == 1);
	a.clear();
	CHECK(a.Empty());
	b.insert(1, 1);
	CHECK(b.Size() == 4);
	CHECK(b[1] == 1);
	b.erase(1);
	CHECK(b.Size() == 3);
	CHECK(b[1] == 4);
	b.clear();
	CHECK(b.Empty());
	b.resize(8);
	CHECK(b.Size() == 8);
	b.resize(2);
	CHECK(b.Size() == 2);
	b.assign(5, 1);
	CHECK(b.Size() == 5);
	d = b;
	b.swap(c);
	CHECK(b.Size() == 3);
	CHECK(c == d);
	CHECK(b != d);
}