#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Dynamic Array") {
	DynamicArray a(5, 10);

	CHECK(a.Size() == 5);
	CHECK(a.Capacity() >= a.Size());
	CHECK(*(a.begin()) == 10);
	CHECK(*(a.end() -  1) == 10);
	CHECK(a == DynamicArray({ 10, 10, 10, 10, 10 }));
	CHECK(a.empty() == false);
	a.clear();
	CHECK(a.empty() == true);
	CHECK(a.Size() == 0);
	CHECK(a.Capacity() == 0);
	CHECK(a == DynamicArray());

	DynamicArray b({ 5, 6, 7, 1, 2, 3 });

	CHECK(b.at(3) == 1);
	CHECK(b[b.Size() - 1] == 3);
	CHECK(b.Size() == 6);
	b.insert(3, 300);
	CHECK(b == DynamicArray({5, 6, 7, 300, 1, 2, 3 }));
	CHECK(b.Size() == 7);
	b.erase(5);
	CHECK(b == DynamicArray({ 5, 6, 7, 300, 1, 3 }));
	CHECK(b.Size() == 6);
	b.swap(a);
	CHECK(a.Size() == 6);
	CHECK(a == DynamicArray({ 5, 6, 7, 300, 1, 3 }));
	CHECK(b.Size() == 0);
	CHECK(b.Capacity() == 0);

	DynamicArray c;
	CHECK(c.Size() == 0);
	CHECK(c.Capacity() == 0);
	c.resize(10);
	CHECK(c.Size() == 10);
	CHECK(c == DynamicArray({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }));
	c.assign(5, 7);
	CHECK(c.Size() == 5);
	CHECK(c == DynamicArray({ 7, 7, 7, 7, 7 }));

	DynamicArray d(c);
	CHECK(d == DynamicArray({ 7, 7, 7, 7, 7 }));

	CHECK_FALSE(b == d);
	CHECK(b != d);
	a = d;
	CHECK(a == DynamicArray({ 7, 7, 7, 7, 7 }));

	CHECK_THROWS_WITH(b.pop_back(), "size 0");
	CHECK_THROWS_WITH(b.erase(4), "size 0 or index out");
	CHECK_THROWS_WITH(a.insert(6, 77), "index out");
	CHECK_THROWS_WITH(a.at(6), "index out");
	CHECK_THROWS_WITH(a[6], "index out");
}
