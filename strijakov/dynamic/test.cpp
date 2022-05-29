#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"

DynamicArray a(8,1), b(5);
DynamicArray c{4,8,16,32};
DynamicArray d(a);
DynamicArray e;
DynamicArray b_copy = b;


TEST_CASE("Testing constructors and initialization") {
    CHECK(a.Size() == 8);
    CHECK(a[3] == 1);
    CHECK(b[5] == 0);
    CHECK(c.Size() == 4);
    CHECK(c[2] == 16);
    CHECK(d == a);
    CHECK(c != b);
    CHECK(e.Size() == 0);
    CHECK(b_copy.Size() == 5);
    CHECK(b == DynamicArray({0,0,0,0,0}));
}

TEST_CASE("Testing methods") {
    a.push_back(0);
    CHECK(a.Size()==9);
    a.pop_back();
    CHECK(a.Size()==8);
    b_copy.clear();
    CHECK(b_copy.Empty());
    a.erase(0);
    CHECK(a[0] == 1);
    a.insert(0, 1);
    CHECK(a.Size() == 8);
    b.resize(10);
    CHECK(b[9] == 0);
    b.resize(5);
    CHECK(b.Size() == 5);
    d.assign(13,2);
    CHECK(d.Size() == 13);
    CHECK(d[11] == 2);
    CHECK(d != c);
    CHECK(*c.begin() == 4);
}

TEST_CASE ("Testing exceptions") {
    CHECK_THROWS_WITH(DynamicArray(4).at(5), "Index out of range");
    CHECK_THROWS_WITH(DynamicArray(4).erase(4), "The index is not match for an array!");
    CHECK_THROWS_WITH(DynamicArray(0).pop_back(), "Array have no elements!");
}
