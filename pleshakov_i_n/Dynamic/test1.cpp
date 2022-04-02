#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Dynamic.h"
#include <string>
#include <iostream>

TEST_CASE("testing") {

    DynamicArray a(10,1), b(5);
    DynamicArray d(a);

    CHECK(a.Size() == 10);
    CHECK(a[1] == 1);
    CHECK(b[1] == 0);
    CHECK(b.Empty() == false);
    CHECK(a[-1] == 1);
    CHECK(d.Size() == 10);
    CHECK(d[2] == 1);

    a.push_back(10);
    CHECK(a[-1] == 10);
    CHECK(a[-2] == 1);
    CHECK(*a.end() == 10);
    CHECK(a.at(-1) == 10);

    a.pop_back();
    CHECK(*a.end() == 1);

    a.resize(20);
    CHECK(a.Size() == 20);
    CHECK(*a.end() == 0);

    DynamicArray c(3);
    c[0] = 2;
    c[1] = 3;
    c[2] = 4;

    c.erase(1);
    CHECK(c[1] == 4);
    CHECK(c.Size() == 2);


    c.insert(1, 8);
    c.insert(3, 9);
    c.insert(0, 10);
    //c = [10, 2, 8, 4, 9]

    CHECK(*c.begin() == 10);
    CHECK(c == DynamicArray({10, 2, 8, 4, 9}));


    DynamicArray f(3), F(f), C({10, 2, 8, 4, 9});
    c.swap(f);
    CHECK(c == F);
    CHECK(C == f);

    c.assign(3, 0);
    CHECK(c == DynamicArray({0, 0, 0}));

    DynamicArray l = DynamicArray({1, 2, 3});
    CHECK(l == DynamicArray({1, 2, 3}));

    DynamicArray h(3, 1);
    h.resize(4);
    CHECK(h == DynamicArray({1, 1, 1, 0}));
    h.resize(5);
    CHECK(h == DynamicArray({1, 1, 1, 0, 0}));
    h.push_back(5);
    CHECK(h == DynamicArray({1, 1, 1, 0, 0, 5}));

    DynamicArray v({5, 4, 3, 2, 1});

}
