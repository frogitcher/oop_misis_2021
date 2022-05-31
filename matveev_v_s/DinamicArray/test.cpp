#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdint>
#include "doctest.h"
#include "DinamicArray.h"

TEST_CASE("Testing push_back() and pop_back()")
{
    DynamicArray a;

    a.push_back(1);
    CHECK(a.Size() == 1);
    CHECK(a[0] == 1);
    a.push_back(2);
    CHECK(a.Size() == 2);
    CHECK(a[0] == 1);
    CHECK(a[1] == 2);

    for (int64_t i = 2; i <= 150; ++i)
    {
        a.push_back(i);
        CHECK(a.Size() == i + 1);
    };

    for (int64_t i = 2; i <= 150; ++i)
    {
        CHECK(a[i] == i);
    };

    DynamicArray b = {1, 2, 3};
    b.pop_back();
    CHECK(b.Size() == 2);
    CHECK(b[0] == 1);
    CHECK(b[1] == 2);
    b.pop_back();
    CHECK(b.Size() == 1);
    b.pop_back();
    CHECK(b.Size() == 0);
    CHECK_THROWS_WITH(b.pop_back(), "The array is empty.");
}

TEST_CASE("Testing resize()")
{

    DynamicArray c = {1, 2, 3};
    c.resize(5);
    CHECK(c == DynamicArray({1, 2, 3, 0, 0}));
    c.resize(2);
    CHECK(c == DynamicArray({1, 2}));
    c.resize(6, 4);
    CHECK(c == DynamicArray({1, 2, 4, 4, 4, 4}));
    c.resize(0);
    CHECK(c.Size() == 0);

    CHECK_THROWS_MESSAGE(c.resize(-3, 5), "The size must be positive.");
}

TEST_CASE("Testing assign()")
{
    DynamicArray b(5, 1);
    DynamicArray c(6, 2);

    b.assign(4, 2);
    for (int64_t i = 0; i < b.Size() - 1; ++i)
        CHECK(b[i] == c[i]);

    CHECK_THROWS_WITH(b.assign(-3, 5), "Size must not be negative.");
}

TEST_CASE("Testing swap()")
{
    DynamicArray a = {5, 6, 7, 8};
    DynamicArray b = {9, 10, 11, 12, 13};
    DynamicArray before = {9, 10, 11, 12, 13};

    a.swap(b);
    CHECK(a.Size() == before.Size());
    CHECK(a.Capacity() == before.Capacity());
    CHECK(a == DynamicArray({9, 10, 11, 12, 13}));
    CHECK(b == DynamicArray({5, 6, 7, 8}));
}

TEST_CASE("Testing Empty()")
{
    DynamicArray a;
    CHECK(a.Empty());

    a.push_back(1);
    CHECK_FALSE(a.Empty());

    a.pop_back();
    CHECK(a.Empty());
}
