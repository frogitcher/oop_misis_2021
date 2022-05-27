#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "darrey.h"




TEST_CASE("TEST THE TEST3") {
	
	darrey a(1);
	darrey b(3, 1);
	darrey c = {1, 1, 1};
	darrey d = a;
	CHECK(a[0] == 0);
	CHECK(c[2] == 1);
	CHECK(d[0] == a[0]);
	a.pop_back();
	CHECK_THROWS_WITH(a.pop_back(), "Array Size <0");
	CHECK_THROWS_WITH(a.at(10), "dynamicarray index out of range");
	for (int i = 0; i < 10000; i++)
	{
		a.push_back(i);
		CHECK(a[i] == i);
	}
	for (int i = 10000 - 1; i > 1; i--)
	{
		a.pop_back();
		CHECK(a[i - 1] == i - 1);
	}
	c.clear();
	CHECK(c.getsize() == 0);
	darrey m = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	m.erase(5);
	CHECK(m[5] == 6);
	a.resize(10);
	CHECK(a.getsize() == 10);
	a.assign(15, 7);
	for (int i = 0; i < a.getsize(); i++)
	{
		CHECK(a[i] == 7);
	}
	darrey s{ 1, 2 }, s_cons, k{ 2, 1 }, k_cons;
	s_cons = s;
	k_cons = k;
	k.swap(s);
	CHECK(s_cons == k);
	CHECK(s_cons != k_cons);
	CHECK(k_cons == s);
	CHECK(s_cons.getcapacity() == 2);
	s.insert(0, 13);
	CHECK(s[0] == 13);
	s.clear();
	CHECK(!s.empty());
}
//TEST_CASE("testing and compare editors") {
//	DynamicArray a(1);
//	DynamicArray b(3, 4);
//	DynamicArray c = { 1, 1, 1 };
//	DynamicArray d = b;
//	a.push_back(1);
//	CHECK(a.Size() == 2);
//	CHECK(a[1] == 1);
//	a.pop_back();
//	CHECK(a.Size() == 1);
//	a.clear();
//	CHECK(a.Empty());
//	b.insert(1, 1);
//	CHECK(b.Size() == 3);
//	CHECK(b[1] == 1);
//	b.erase(1);
//	CHECK(b.Size() == 2);
//	CHECK(b[1] == 4);
//	b.clear();
//	CHECK(b.Empty());
//	b.assign(3, 1);
//	CHECK(b.Size() == 3);
//}