#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"

TEST_CASE("Test dynamic array") {
	DynamicArray a;
	CHECK(a.Size() == 0);
	CHECK(a.Capacity() == 0);
	
	DynamicArray b(10, 123);
	CHECK(b.Size() == 10);
	CHECK(b.Capacity() >= b.Size());
	CHECK(b[2] == 123);
	b[4] = 23;
	CHECK(b[4] == 23);
	CHECK(b.at(2) == 123);
	
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
	CHECK(a.Size() == 0);
	
	a.pop_back();
	CHECK(a.Size() == 0);

	b.clear();
	CHECK(b.Size() == 0);
	CHECK(b.Capacity() == 0);
	
	DynamicArray d({ 10, 10, 10, 10 });
	d.resize(10, -1);
	CHECK(d[7] == -1);
	CHECK(d.Size() == 10);
	
	d.insert(3, -10);
	CHECK(d[3] == -10);

	d.resize(4, 0);
	d.erase(3);
	CHECK(d.Size() == 9);
	CHECK(d[3] != -10);

	CHECK()





}