#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "arrayd.h"
#include <iostream>

TEST_CASE("initialization and basics") {
	arrayd z;
	CHECK(z.Cap() == 1);
	CHECK(z.Size() == 0);
	CHECK(z.Empty());

	arrayd x(5);
	CHECK(x.Cap() == 8);
	CHECK(x.Size() == 5);
	CHECK(!x.Empty());
	for (int i = 0; i < 5; i++) {
		CHECK(x[i] == 0);
	}

	arrayd c(8, 5);
	CHECK(c.Cap() == 8);
	CHECK(c.Size() == 8);
	CHECK(!c.Empty());
	for (int i = 0; i < 8; i++) {
		CHECK(c[i] == 5);
	}

	arrayd cursed(8, 5);
	CHECK(c == cursed);
	CHECK(x != cursed);
	c.clear();
	CHECK(c == z);

	arrayd y(cursed);
	CHECK(y == cursed);
	for (int i = 0; i < 8; i++) {
		y[i] = i;
		CHECK(y[i] == i);
		CHECK(y[i] == y.at(i));
	}

	arrayd b({0, 1, 2, 3, 4, 5});
	CHECK(b.Cap() == 8);
	CHECK(b.Size() == 6);
	CHECK(b != y);
	CHECK(b.back() == 5);
	CHECK(b.front() == 0);
	CHECK(*b.begin() == b.front());
	CHECK(*(b.end() - 1) == b.back());

	arrayd r(1, 1);
	CHECK(*r.begin() == 1);
	CHECK(*(r.end() - 1) == 1);
	CHECK(r.end() - 1 == r.begin());
}

TEST_CASE("throws") {
	arrayd z(10, 10);
	arrayd x;
	CHECK_THROWS_WITH(arrayd(-1, 10), "kooky array size: < 0");
	CHECK_THROWS_WITH(z.resize(-1), "negative array size");
	CHECK_THROWS_WITH(x.pop_back(), "kovo ti popaesh?)");
	CHECK_THROWS_WITH(x[0], "ny kuda???");
	CHECK_THROWS_WITH(z[-1], "ny kuda???");
	CHECK_THROWS_WITH(z[12], "ny kuda???");
	CHECK_THROWS_WITH(z.erase(12), "invalid erasion index");
	CHECK_THROWS_WITH(z.erase(-1), "invalid erasion index");
	CHECK_THROWS_WITH(z.insert(-1, 0), "invalid insertion index");
	CHECK_THROWS_WITH(z.insert(12, 0), "invalid insertion index");
}

TEST_CASE("memory modifiers") {
	arrayd z(9, 10);
	z.resize(6);
	CHECK(z.Size() == 6);
	CHECK(z.Cap() == 16);
	for (int i = 0; i < z.Size(); i++) {
		CHECK(z[i] == 10);
	}
	z.assign(16, 5);
	CHECK(z.Size() == 16);
	CHECK(z.Cap() == 16);
	for (int i = 0; i < z.Size(); i++) {
		CHECK(z[i] == 5);
	}
	z.assign(5, 4);
	CHECK(z.Size() == 5);
	CHECK(z.Cap() == 16);
	for (int i = 0; i < z.Size(); i++) {
		CHECK(z[i] == 4);
	}
	arrayd x(100, 50);
	x.swap(z);
	for (int i = 0; i < 100; i++) {
		CHECK(z[i] == 50);
	}
	for (int i = 0; i < 5; i++) {
		CHECK(x[i] == 4);
	}
}

TEST_CASE("element modifiers") {
	arrayd z(10, 10);
	for (int i = 0; i < 20; i++) {
		z.push_back(i);
		CHECK(z.Size() == 10 + i + 1);
		for (int j = 0; j < 10; j++) {
			CHECK(z[j] == 10);
		}
	}
	CHECK(z.Cap() == 32);
	z.pop_back();
	CHECK(z.back() == 18);
	int x = z.Size();

	z.insert(10, 100);
	for (int i = 0; i < 10; i++) {
		CHECK(z[i] == 10);
	}
	CHECK(z[10] == 100);
	CHECK(z.Size() == x + 1);
	for (int i = 0; i < 19; i++) {
		CHECK(z[i + 11] == i);
	}

	z.insert(0, 101);
	CHECK(z[0] == 101);
	CHECK(z.Size() == x + 2);
	for (int i = 0; i < 10; i++) {
		CHECK(z[i + 1] == 10);
	}
	CHECK(z[11] == 100);
	for (int i = 0; i < 19; i++) {
		CHECK(z[i + 12] == i);
	}

	z.insert(z.Size() - 1, 102);
	CHECK(z[0] == 101);
	for (int i = 0; i < 10; i++) {
		CHECK(z[i + 1] == 10);
	}
	CHECK(z[11] == 100);
	CHECK(z[z.Size() - 2] == 102);
	CHECK(z.back() == 18);

	z.erase(0);
	for (int i = 0; i < 10; i++) {
		CHECK(z[i] == 10);
	}
	z.erase(10);
	for (int i = 0; i < 18; i++) {
		CHECK(z[10] == i);
		z.erase(10);
	}
	CHECK(z[10] == 102);
	z.erase(10);
	CHECK(z[10] == 18);
}
