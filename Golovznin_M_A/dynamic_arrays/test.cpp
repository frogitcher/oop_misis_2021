#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Testing dynamic array class") {
    DynamicArray a;
    CHECK(a.getSize() == 0);
    CHECK(a.begin() == a.getData());

    DynamicArray b(5, 4);
    CHECK(b.getSize() == 5);
    CHECK(b.getCapacity() >= b.getSize());

    DynamicArray c(b);
    CHECK(c.getSize() == b.getSize());
    CHECK(c.getCapacity() == b.getCapacity());
    for (int64_t i = 0; i < b.getSize(); ++i) {
        CHECK(&(c[i]) == (c.begin() + i));
        CHECK(c[i] == b[i]);
    }

    DynamicArray d({1, 2, 3, 4, 5, 6});
    CHECK_FALSE(c == d);
    CHECK(c != d);
    CHECK_FALSE(c != b);

    // a is empty
    CHECK(a.empty());

    // b is not empty
    CHECK_FALSE(b.empty());

    CHECK_THROWS_WITH(a.at(1), "Index was outside of bounds of an array");

    int64_t old_size = b.getSize();
    b.push_back(-9);
    CHECK(b.getSize() == old_size + 1);
    CHECK(b[b.getSize() - 1] == -9);

    DynamicArray d_copy(d);
    CHECK(d_copy.getSize() == d.getSize());
    CHECK(d.getCapacity() == d_copy.getCapacity());
    for (int64_t i = 0; i < d.getSize(); ++i) {
        CHECK(d[i] == d_copy[i]);
    }

    old_size = d.getSize();
    d.pop_back();
    CHECK(d.getSize() == old_size - 1);
    for (int64_t i = 0; i < d.getSize(); ++i) {
        CHECK(d[i] == d_copy[i]);
    }
    CHECK_THROWS_WITH(a.pop_back(), "Array is empty"); // pop_back() on empty array

    d.clear();
    CHECK(d.empty());

    // b = {4, 4, 4, 4, 4, -9};
    DynamicArray b_copy(b);
    b.erase(0);
    CHECK(b.getSize() == b_copy.getSize() - 1);
    for (int64_t i = 0; i < b.getSize(); ++i) {
        CHECK(b[i] == b_copy[i + 1]);
    }
    b.erase(3);
    CHECK(b.getSize() == b_copy.getSize() - 2);
    for (int64_t i = 0; i < b.getSize(); ++i) {
        if (i >= 3) {
            CHECK(b[i] == b_copy[i + 2]);
            continue;
        }
        CHECK(b[i] == b_copy[i + 1]);
    }
    b.erase(b.getSize() - 1);
    CHECK(b.getSize() == b_copy.getSize() - 3);
    for (int64_t i = 0; i < b.getSize(); ++i) {
        if (i >= 3) {
            CHECK(b[i] == b_copy[i + 2]);
            continue;
        }
        CHECK(b[i] == b_copy[i + 1]);
    }

    // b = {4, 4, 4}
    old_size = b.getSize();
    b.assign(23, 125);
    CHECK(b.getSize() == 23);
    for (int64_t i = 0; i < old_size; ++i) {
        CHECK(b[i] == 4);
    }
    for (int64_t i = old_size + 1; i < b.getSize(); ++i) {
        CHECK(b[i] == 125);
    }

    CHECK_THROWS_WITH(b.assign(-16, 8), "Array length can't be negative");

    b.resize(0);
    CHECK(b.empty());

    b.assign(14, 52);
    CHECK(b.getSize() == 14);
    for (int64_t i = 0; i < b.getSize(); ++i) {
        CHECK(b[i] == 52);
    }

    CHECK_THROWS_WITH(b.assign(-16, 8), "Array length can't be negative");

    b.resize(0);
    CHECK(b.empty());
    CHECK(b.end() == b.getData() + 0);

    int64_t old_getSize_c = c.getSize();
    int64_t old_getSize_d = d.getSize();
    int64_t old_capacity_c = c.getCapacity();
    int64_t old_capacity_d = d.getCapacity();
    int* old_data_c = c.getData();
    int* old_data_d = d.getData();
    d.swap(c);
    CHECK(d.getSize() == old_getSize_c);
    CHECK(c.getSize() == old_getSize_d);
    CHECK(d.getCapacity() == old_capacity_c);
    CHECK(c.getCapacity() == old_capacity_d);
    CHECK(d.getData() == old_data_c);
    CHECK(c.getData() == old_data_d);

    d_copy = d;
    d.insert(0, 75);
    CHECK(d[0] == 75);
    for (int64_t i = 1; i < d.getSize(); ++i) {
        CHECK(d[i] == d_copy[i - 1]);
    }
    d_copy = d;
    d.insert(4, 32);
    CHECK(d[4] == 32);
    for (int64_t i = 0; i < d.getSize(); ++i) {
        if (i == 4) {
            continue;
        }
        if (i > 4) {
            CHECK(d[i] == d_copy[i - 1]);
            continue;
        }
        CHECK(d[i] == d_copy[i]);
    }
    d_copy = d;
    d.insert(7, 0);
    CHECK(d[7] == 0);
    for (int64_t i = 0; i < d.getSize(); ++i) {
        if (i == 7) {
            continue;
        }
        CHECK(d[i] == d_copy[i]);
    }
}