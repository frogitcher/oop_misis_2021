#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "DynamicArray.h"
#include <string>
#include <iostream>
#include <algorithm>

TEST_CASE("testing Push_back, Pop_back, Clear, [], At, Size") {

    DynamicArray h;
    h.Push_back(228);
    h.Push_back(1337);
    h.Push_back(1553);
    CHECK(h[0] == 228);
    CHECK(h.At(2) == 1553);
    h.Pop_back();
    h.Pop_back();
    CHECK_THROWS_WITH(h[1], "Incorrect index");
    CHECK(h.Size() == 1);
    DynamicArray  b{228, 2, 3, 4};
    CHECK(b == DynamicArray({228, 2, 3, 4}));
    CHECK(b[0] == 228);
    CHECK(b.Size() == 4);
    b.Pop_back();
    b.Pop_back();
    b.Pop_back();
    b.Pop_back();
    CHECK_THROWS_WITH(b.Pop_back(), "you cannot delete an element from an empty array");

}

TEST_CASE("testing Size, Clear, Resize, ==") {
    DynamicArray a(4, 1), b, c({1, 2, 3}), d(4, 3);

    CHECK_FALSE(a == b);
//
    b.Resize(4);
//
    CHECK(a.Size() == b.Size());
    b.Clear();
    b.Push_back(1);
    b.Push_back(2);
    b.Push_back(3);
//
    CHECK(c == b);
//
    d.Resize(2);
    CHECK(d == DynamicArray({3, 3}));
}




TEST_CASE("testing Erase, Insert, Assign"){
    DynamicArray a(4, 1), b, c({1, 2, 3}), checking({0, 1, 2});

    a.Assign(3, 2);
    c.Insert(0, 4);
   c.Erase(c.Size() - 1);
//
    CHECK(a.Size() == c.Size());
    CHECK(a[2] == 2);
    CHECK(c[0] == 4);
    CHECK_THROWS_WITH(b.Erase(0), "you cannot delete an element from an empty array");
    CHECK_THROWS_WITH(a.Erase(100), "Incorrect index");
    b.Resize(4);
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
