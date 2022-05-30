#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstdint>
#include "doctest.h"
#include "dynamic_array.h"


TEST_CASE("Dynamic array initialisation") {
    DynamicArray a;
    CHECK(a.Size() == 0);
    CHECK(a.begin() == a.GetData());

    DynamicArray b(5, 5);
    CHECK(b.Size());
    CHECK(b.begin() == b.GetData());
    for (auto v: b) {
        CHECK(v == 5);
    }


    DynamicArray c(b);
    CHECK(c.Size());
    CHECK(c.begin() == c.GetData());
    for (int64_t i = 0; i < c.Size(); ++i) {
        CHECK(c[i] == b[i]);
    }

    CHECK(c.end() == c.GetData() + c.Size());
    CHECK(c.end() != c.GetData() + 0);

    DynamicArray d = {5, 5, 5, 5, 5};
    CHECK(d.Size() == 5);
    CHECK(d.begin() == d.GetData());
    for (int64_t i = 0; i < b.Size(); ++i) {
        CHECK(d[i] == b[i]);
    }
}

TEST_CASE("Testing push_back() and pop_back()") {
    DynamicArray a;

    a.push_back(1);
    CHECK(a.Size() == 1);
    CHECK(a[0] == 1);
    a.push_back(2);
    CHECK(a.Size() == 2);
    CHECK(a[0] == 1);
    CHECK(a[1] == 2);

    for (int64_t i = 2; i <= 150; ++i) {
      a.push_back(i);
      CHECK(a.Size() == i + 1);
    };

    for (int64_t i = 2; i <= 150; ++i) {
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
    CHECK_THROWS_WITH(b.pop_back(), "Array is empty");
}

TEST_CASE("Testing erase()") {
    DynamicArray a = {1, 2, 3, 4, 5};
    DynamicArray after = {2, 3, 4, 5};

    CHECK(a.Size() == 5);
    a.erase(0);
    CHECK_THROWS_MESSAGE(a.erase(-1), "Index is out of range");
    CHECK_THROWS_MESSAGE(a.erase(10), "Index is out of range");
    CHECK(a.Size() == 4);
    for (int64_t i = 0; i < a.Size(); ++i) CHECK(a[i] == after[i]);

    DynamicArray b;
    CHECK_THROWS_MESSAGE(b.erase(1), "Array is empty");

}

TEST_CASE("Testing resize()") {

    DynamicArray c = {1, 2, 3};
    c.resize(5);
    CHECK(c == DynamicArray({1, 2, 3, 0, 0}));
    c.resize(2);
    CHECK(c == DynamicArray({1, 2}));
    c.resize(6, 4);
    CHECK(c == DynamicArray({1, 2, 4, 4, 4, 4}));
    c.resize(0);
    CHECK(c.Size() == 0);

    CHECK_THROWS_MESSAGE(c.resize(-3, 5), "Size must be positive");

}

TEST_CASE("Testing assign()") {
    DynamicArray b(5, 1);
    DynamicArray c(6, 2);

    b.assign(4, 2);
    for (int64_t i = 0; i < b.Size() - 1; ++i) CHECK(b[i] == c[i]);

    CHECK_THROWS_WITH(b.assign(-3, 5), "Size must not be negative");
}

TEST_CASE("Testing insert()") {
    DynamicArray a = {1, 2, 3, 4};
    DynamicArray b = {1, 2, 5, 3, 4};
    CHECK(a.Size() == 4);
    CHECK(b.Size() == 5);

    CHECK_THROWS_WITH(a.insert(-2, 5), "Index is out of range");

    a.insert(2, 5);
    CHECK(a.Size() == 5);
    for (int64_t i = 0; i < a.Size(); ++i) CHECK(a[i] == b[i]);

    DynamicArray c = {1, 2, 3};
    DynamicArray d = {1, 2, 3, 4};
    c.insert(3, 4);
    CHECK(c.Size() == 4);
    CHECK(c == d);
}

TEST_CASE("Testing swap()") {
    DynamicArray a = {1, 2, 3, 4};
    DynamicArray b = {5, 6, 7, 8, 9};
    DynamicArray before = {5, 6, 7, 8, 9};

    a.swap(b);
    CHECK(a.Size() == before.Size());
    CHECK(a.Capacity() == before.Capacity());
    CHECK(a == DynamicArray({5, 6, 7, 8, 9}));
    CHECK(b == DynamicArray({1, 2, 3, 4}));
}

TEST_CASE("Testing Empty()") {
    DynamicArray a;
    CHECK(a.Empty());

    a.push_back(1);
    CHECK_FALSE(a.Empty());

    a.pop_back();
    CHECK(a.Empty());
}

TEST_CASE("Testing at()") {
    DynamicArray a;
    CHECK_THROWS_WITH(a.at(1), "Index is out of range");

    a.push_back(1);
    CHECK(a.at(0) == 1);
}

TEST_CASE("Testing operator =") {
    DynamicArray a = {1, 2, 3};
    DynamicArray b;

    b = a;
    CHECK(b.Size() == a.Size());
    CHECK(b.Capacity() == a.Capacity());
    for (int64_t i = 0; i < b.Size(); i++) CHECK(b[i] == a[i]);
}
