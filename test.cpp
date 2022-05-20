#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Dynamic.h"
#include <string>
#include <iostream>

TEST_CASE("just testing") {
    DynamicArray a({1,2,3,4}), b(5, 1), c(2), d(c), e;

    CHECK(a.getSize() == 4);
    CHECK(b.getSize() == 5);
    CHECK(c.getSize() == 2);
    CHECK(d.getSize() == 2);

    c.assign(3, 2);
    CHECK(c.getSize() == 3);
    CHECK(c[0] == 2);

    c.swap(b);
    CHECK(c.getSize() == 5);
    CHECK(b.getSize() == 3);
    CHECK(c[0] == 1);
    CHECK(b[0] == 2);

    CHECK(a[0] == 1);
    CHECK(b[0] == 1);

    CHECK(e.empty() == true);
    CHECK_THROWS_WITH(e.at(1), "Array out of bounds");
    CHECK_THROWS_WITH(e.erase(1), "Array out of bounds");
    CHECK_THROWS_WITH(e.pop_back(), "Array is empty");

    a.push_back(5);
    CHECK(a.getSize() == 5);
    CHECK(a[4] == 5);

    a.pop_back();
    CHECK(a.getSize() == 4);
    CHECK(a[3] == 4);

    a.insert(2, 10);
    CHECK(a.getSize() == 4);
    CHECK(a[2] == 10);
    CHECK(a[3] == 4);
    
    a.erase(2);
    CHECK(a.getSize() == 3);
    CHECK(a[2] == 4);

    a.clear();
    CHECK(a.getSize() == 0);

    a.resize(10);
    CHECK(a.getSize() == 10);
}