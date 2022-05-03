#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"
#include <iostream>

TEST_CASE("testing constructors") {
    DynamicArray a(10);
    CHECK(a.Size() == 10);
    CHECK(a.Capacity() == 10);
    DynamicArray b;
    CHECK(b.Empty() == true);
    CHECK(a.Empty() == false);

    DynamicArray c{0, 1, 2, 3, 4, 5, 6};
    CHECK(c[1] == 1);
    CHECK(c[6] == 6);
    CHECK(c.Capacity() == 7);

    DynamicArray d(c);
    CHECK(d == c);

    DynamicArray e{0, 1, 2, 3};
    CHECK(e != d);
    e = d;
    CHECK(e == d);
    e.erase(1);
    CHECK(e != d);
}

TEST_CASE("testing methods") {
    DynamicArray b;
    b.push_back(7);
    b.push_back(100);
    b.push_back(1);
    CHECK_THROWS_WITH(b.at(3), "DynamicArray index out of range");
    CHECK(b[2] == 1);
    CHECK(b[1] == 100);
    CHECK(b[0] == 7);
    CHECK(b.Capacity() == 3);
    CHECK(b.Size() == 3);

    b.pop_back();
    CHECK_THROWS_WITH(b.at(2), "DynamicArray index out of range");
    CHECK(b[1] == 100);
    CHECK(b.Size() == 2);
    CHECK(b.Capacity() == 3);

    b.clear();
    CHECK(b.Empty() == true);
    CHECK_THROWS_WITH(b.at(0), "DynamicArray index out of range");
    DynamicArray a{1, 2, 4, 8, 16, 32};

    a.erase(1);
    CHECK(a == DynamicArray{1, 4, 8, 16, 32});
    CHECK(a.Size() == 5);
    CHECK(a.Capacity() == 6);
    CHECK_THROWS_WITH(a.erase(5), "DynamicArray index out of range");

    a.insert(1, 2);
    CHECK(a == DynamicArray{1, 2, 4, 8, 16, 32});
    CHECK(a.Size() == 6);
    CHECK(a.Capacity() == 6);
    a.insert(0, 0);
    CHECK(a == DynamicArray{0, 1, 2, 4, 8, 16, 32});
    CHECK(a.Size() == 7);
    CHECK(a.Capacity() == 13);

    a.resize(9);
    CHECK(a.Size() == 9);
    a.resize(3);
    CHECK(a == DynamicArray{0, 1, 2});
    CHECK(a.Size() == 3);
    CHECK_THROWS_WITH(a.at(3), "DynamicArray index out of range");

    a.assign(5, 100);
    CHECK(a == DynamicArray{0, 1, 2, 100, 100});
    CHECK_THROWS_WITH(a.at(5), "DynamicArray index out of range");
    a.assign(3, 100);
    CHECK(a == DynamicArray{0, 1, 2});
    CHECK_THROWS_WITH(a.at(3), "DynamicArray index out of range");
    DynamicArray c{2, 1, 0};

    a.swap(c);
    CHECK(a == DynamicArray{2, 1, 0});
    CHECK(c == DynamicArray{0, 1, 2});
    DynamicArray d{2, 1};
    DynamicArray e{4, 2, 1, 0};
    d.swap(e);
    CHECK(e == DynamicArray{2, 1});
    CHECK(d == DynamicArray{4, 2, 1, 0});
}

TEST_CASE("testing something else") {
    DynamicArray a;
    CHECK(a.begin() == a.end());
    DynamicArray b{1, 2, 4, 8, 16, 32};
    DynamicArray c{1, 2, 4, 8, 16, 32};
    CHECK(b.begin() + b.Size() == b.end());

    CHECK(b == c);
    CHECK(b != a);
}
