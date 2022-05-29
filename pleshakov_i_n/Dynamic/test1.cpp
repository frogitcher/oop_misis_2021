#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Dynamic.h"
#include <string>
#include <iostream>
#include <algorithm>

TEST_CASE("testing Push_back, Pop_back, Clear, [], At, Size") {

    DynamicArray a(5, 1), b(3), c({1, 2, 3, 4, 5}), d(b), checking({1, 2, 3, 4, 5, 10});
    DynamicArray h;

    h.Push_back(10);
    h.Push_back(9);
    h.Push_back(8);

    c.Push_back(10);

    b.Push_back(9);

    a.Push_back(8);

    CHECK(h[0] == 10);
    CHECK(h.At(2) == 8);

    CHECK(b == DynamicArray({0, 0, 0, 9}));

    CHECK(a[1] == 1);
    CHECK_THROWS_WITH(a[6], "Incorrect index");

    CHECK(d.Size() == 3);
    d.Pop_back();
    CHECK(d.Size() == 2);

    d.Pop_back();
    CHECK_THROWS_WITH(d[1], "Incorrect index");

    d.Pop_back();
    CHECK_THROWS_WITH(d.Pop_back(), "Array is empty");

    for (int i=0; i<6; ++i){
        CHECK(checking[i] == c[i]);
    }
}

TEST_CASE("testing Size, Clear, Resize, ==") {
    DynamicArray a(4, 1), b, c({1, 2, 3}), d(4, 3);

    CHECK_FALSE(a == b);

    b.Resize(4);

    CHECK(a.Size() == b.Size());

    b.Clear();
    b.Push_back(1);
    b.Push_back(2);
    b.Push_back(3);

    CHECK(b == c);

    d.Resize(2);
    CHECK(d == DynamicArray({3, 3}));
}

TEST_CASE("testing Erase, Insert, Assign"){
    DynamicArray a(4, 1), b, c({1, 2, 3}), d(5), checking({0, 1, 2});

    a.Assign(3, 2);
    d.Erase(2);
    d.Insert(2, 2);
    c.Insert(0, 4);
    c.Erase(c.Size() - 1);

    CHECK(a.Size() == c.Size());
    CHECK(a[2] == 2);
    CHECK(c[0] == 4);
    CHECK_THROWS_WITH(b.Erase(0), "Array is empty");
    CHECK_THROWS_WITH(a.Erase(100), "Incorrect index");
    CHECK(d == DynamicArray({0, 0, 2, 0, 0}));

    b.Insert(0, 0);
    b.Insert(1, 2);
    b.Insert(1, 1);
    b.Insert(2, 3);
    b.Erase(2);
    for (int i=0; i<3; ++i){
        CHECK(checking[i] == b[i]);
    }

}

TEST_CASE("testing begin, end, Swap"){
    DynamicArray a(4, 1), c({1, 2, 3}), d({3, 1, 4, 6});

    a.Swap(c);
    CHECK(a == DynamicArray({1, 2, 3}));
    CHECK(c[1] == 1);
    CHECK(c.Size() == 4);

    std::sort(d.begin(), d.end());
    CHECK(d == DynamicArray({1, 3, 4, 6}));

}
