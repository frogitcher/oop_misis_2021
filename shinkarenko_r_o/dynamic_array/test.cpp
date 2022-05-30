#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"
#include <algorithm>
#include <iostream>

TEST_CASE("Test dynamic array") {
	DynamicArray a;
	CHECK(a.Size() == 0);
	CHECK(a.Capacity() >= a.Size());
	CHECK(a.Empty());
	
	DynamicArray b(10, 123);
	CHECK(b.Size() == 10);
	CHECK(b.Capacity() >= b.Size());
	CHECK(b[2] == 123);
	b[4] = 23;
	CHECK(b[4] == 23);
	CHECK(b.at(4) == 23);
	
	DynamicArray c(b);
	CHECK(c.Size() == b.Size());
	CHECK(c.Capacity() == b.Capacity());
	for (int i = 0; i < c.Size(); ++i) {
		CHECK(c[i] == b[i]);
	}
	CHECK(c != a);
	CHECK(c == b);
	
	a.push_back(10);
	CHECK(a[0] == 10);
	DynamicArray t;
	CHECK(t.Size() == 0);
	t.resize(1, 0);
	CHECK(t.Size() == 1);
	CHECK(t[0] == 0);
	CHECK(a[0] == 10);
	CHECK(a.Size() == 1);
	
	a.pop_back();
	CHECK(a.Size() == 0);

	b.clear();
	CHECK(b.Size() == 0);
	
	DynamicArray d({ 10, 10, 10, 10 });
	d.resize(10, -1);
	CHECK(d[7] == -1);
	CHECK(d.Size() == 10);
	
	d.insert(3, -10);
	CHECK(d[3] == -10);

	d.resize(4, 0);
	d.erase(3);
	CHECK(d.Size() == 3);
	CHECK(d[2] != -10);

	DynamicArray a_1({4, 3, 1, 2});
	DynamicArray b_1({ 0, 0, 0 });
	DynamicArray c_1({ 4, 3, 1, 2 });
	DynamicArray d_1({ 0, 0, 0 });
	CHECK(a_1 == c_1);
	CHECK(b_1 == d_1);
	a_1.swap(b_1);
	CHECK(a_1 == d_1);
	CHECK(b_1 == c_1);
	
	std::sort(b_1.begin(), b_1.end());
	CHECK(b_1 == DynamicArray({ 1, 2, 3, 4 }));

	CHECK_THROWS_WITH(b_1.at(10), "Index is out of range");
	CHECK_THROWS_WITH(b_1.resize(-123, 0), "Array size must be positive");

	DynamicArray a_2;
	CHECK_THROWS_WITH(a_2.pop_back(), "Empty array");
	CHECK_THROWS_WITH(b_1.erase(123), "Index is out of range");
	CHECK_THROWS_WITH(a_2.erase(0), "Index is out of range");
	CHECK_THROWS_WITH(a_2.insert(10, 5), "Index is out of range");

}