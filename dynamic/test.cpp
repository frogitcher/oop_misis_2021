#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "dynamic.h"
TEST_CASE("basic tests") {
	dynamic a(5), b(5, 1), d({ 1, 1, 1, 1, 1 });
	for (int i = 0; i < 5; i++)
		a[i] = 1;
	CHECK((a == b) == 1);
	CHECK((a != b) == 0);
	a[0] = 0;
	CHECK((a == b) == 0);
	CHECK((a != b) == 1);
	for(int i = 0; i < 5; i++)
		CHECK((d[i] == 1) == 1);

	CHECK((b == d) == 1);
	CHECK((a != d) == 1);

	dynamic c(a);
	CHECK((c == a) == 1);
	CHECK((c != b) == 1);
	std::cout << a[0] << ' ';
	c = b;
	std::cout << a[0] << ' ';
	CHECK((c == b) == 1);
	CHECK((c != a) == 1);

	c.at(0) = 0;
	CHECK((c == a) == 1);
	CHECK((c == b) == 0);

	CHECK((a.begin() != c.begin()) == 1);
	CHECK((a[0] == c[0]) == 1);

	CHECK((a.end() != c.end()) == 1);
	CHECK((a[4] == c[4]) == 1);
}

TEST_CASE("func tests") {
	dynamic a({ 1, 2, 3, 4, 5 }), b({ 1, 2, 3, 4, 5 }), c(5, 1);
	CHECK((a.size() == 5) == 1);
	CHECK((a.capacity() == 5) == 1);

	a.push_back(6);
	CHECK((a.size() == 6) == 1);
	CHECK((a.capacity() == 11) == 1);
	CHECK((a[5] == 6) == 1);

	a.pop_back();
	CHECK((a.size() == 5) == 1);
	CHECK((a.capacity() == 11) == 1);

	a.clear();
	CHECK((a.size() == 0) == 1);
	CHECK((a.capacity() == 11) == 1);
	CHECK((a.empty() == 1) == 1);

	a.swap(b);
	CHECK((a.size() == 0) == 0);
	CHECK((a.capacity() == 11) == 0);
	CHECK((a.empty() == 1) == 0);
	CHECK((b.size() == 0) == 1);
	CHECK((b.capacity() == 11) == 1);
	CHECK((b.empty() == 1) == 1);

	CHECK((a.size() == 5) == 1);
	CHECK((a.capacity() == 5) == 1);
	CHECK((a.empty() == 0) == 1);

	b.assign(5, 1);
	CHECK((b == c) == 1);

	a.erase(2);
	CHECK((a[1] == 2) == 1);
	CHECK((a[2] == 4) == 1);
	CHECK((a.size() == 4) == 1);

	a.insert(2, 3);
	CHECK((a[1] == 2) == 1);
	CHECK((a[2] == 3) == 1);
	CHECK((a.size() == 5) == 1);

	a.insert(a.begin(), 0);
	CHECK((a[0] == 0) == 1);
	CHECK((a[1] == 1) == 1);
	CHECK((a.size() == 6) == 1);

	a.erase(a.begin());
	CHECK((a[0] == 1) == 1);
	CHECK((a[1] == 2) == 1);
	CHECK((a.size() == 5) == 1);

	a.insert(a.end(), 6);
	CHECK((a[5] == 6) == 1);
	CHECK((a[4] == 5) == 1);
	CHECK((a.size() == 6) == 1);

	a.erase(a.end() - 1);
	CHECK((a[4] == 5) == 1);
	CHECK((a.size() == 5) == 1);

	a.resize(14);
	CHECK((a.size() == 14) == 1);
}
