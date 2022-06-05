#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "doctest.h"
#include "dynamic.h"

TEST_CASE("Testing methods") {
    DynamicArray a(5, 13);
    DynamicArray b{1, 2, 3, 4, 5};
    DynamicArray c{1, 2, 3, 4, 5};
    CHECK(a.Size() == 5);
    CHECK(!(a.Empty()));
    CHECK(a[1]==13);
    CHECK(a.at(1)==13);
    a.push_back(13);
    CHECK(a == DynamicArray(6, 13));
    a.pop_back();
    CHECK(a == DynamicArray(5, 13));
    a.clear();
    CHECK(a == DynamicArray(0));
    CHECK(a.Empty());
    a.insert(0, 1);
    CHECK(a == DynamicArray(1, 1));
    a.assign(8, 13);
    CHECK(a == DynamicArray(8, 13));
    a.insert(0, 23);
    CHECK(a[0] == 23);
    a.erase(0);
    CHECK(a == DynamicArray(8, 13));
    a.swap(b);
    CHECK(a ==c);
}

TEST_CASE("Testing boolean functions") {
    DynamicArray a(5, 13);
    DynamicArray b{1, 2, 3, 4, 5};
    DynamicArray c{13, 13, 13, 13, 13};
    CHECK(a == DynamicArray(5, 13));
    CHECK(a == c);
    CHECK(!(a == b));
    CHECK(a != b);
}

TEST_CASE("Testing exceptions") {
    DynamicArray a = DynamicArray(5, 13);
    CHECK_THROWS_WITH(a.at(5), "index out of range");
    CHECK_THROWS_WITH(DynamicArray(0).pop_back(), "size can't be < 0");
    CHECK_THROWS_WITH(a.erase(6), "index out of range");
    CHECK_THROWS_WITH(a.insert(6, 7), "index out of range");

}
