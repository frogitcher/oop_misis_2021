#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Testing dynamic array class") {
    DynamicArray a;
    CHECK(a.Size() == 0);
    CHECK(a.begin() == a.GetData());

    DynamicArray b(5, 4);
    CHECK(b.Size() == 5);
    CHECK(b.Capacity() >= b.Size());

    DynamicArray c(b);
    CHECK(c.Size() == b.Size());
    CHECK(c.Capacity() == b.Capacity());
    for (int64_t i = 0; i < b.Size(); ++i) {
        CHECK(&(c[i]) == (c.begin() + i));
        CHECK(c[i] == b[i]);
    }

    DynamicArray d({1, 2, 3, 4, 5, 6});
    CHECK_FALSE(c == d);
    CHECK(c != d);
    CHECK_FALSE(c != b);

    // a is empty
    CHECK(a.Empty());

    // b is not empty
    CHECK_FALSE(b.Empty());

    CHECK_THROWS_WITH(a.at(1), "Index is out of range!");

    int64_t old_size = b.Size();
    b.push_back(-9);
    CHECK(b.Size() == old_size + 1);
    CHECK(b[b.Size() - 1] == -9);

    DynamicArray d_copy(d);
    d.reallocate(50);
    CHECK(d_copy.Size() == d.Size());
    CHECK(d.Capacity() == 50);
    for (int64_t i = 0; i < d.Size(); ++i) {
        CHECK(d[i] == d_copy[i]);
    }

    old_size = d.Size();
    d.pop_back();
    CHECK(d.Size() == old_size - 1);
    for (int64_t i = 0; i < d.Size(); ++i) {
        CHECK(d[i] == d_copy[i]);
    }
    CHECK_THROWS_WITH(a.pop_back(), "Array is empty!"); // pop_back() on empty array

    d.clear();
    CHECK(d.Empty());

    // b = {4, 4, 4, 4, 4, -9};
    DynamicArray b_copy(b);
    b.erase(0);
    CHECK(b.Size() == b_copy.Size() - 1);
    for (int64_t i = 0; i < b.Size(); ++i) {
        CHECK(b[i] == b_copy[i + 1]);
    }
    b.erase(3);
    CHECK(b.Size() == b_copy.Size() - 2);
    for (int64_t i = 0; i < b.Size(); ++i) {
        if (i >= 3) {
            CHECK(b[i] == b_copy[i + 2]);
            continue;
        }
        CHECK(b[i] == b_copy[i + 1]);
    }
    b.erase(b.Size() - 1);
    CHECK(b.Size() == b_copy.Size() - 3);
    for (int64_t i = 0; i < b.Size(); ++i) {
        if (i >= 3) {
            CHECK(b[i] == b_copy[i + 2]);
            continue;
        }
        CHECK(b[i] == b_copy[i + 1]);
    }

    // b = {4, 4, 4}
    old_size = b.Size();
    b.resize(23, 125);
    CHECK(b.Size() == 23);
    for (int64_t i = 0; i < old_size; ++i) {
        CHECK(b[i] == 4);
    }
    b.resize(15, 2);
    for (int64_t i = 0; i < b.Size(); ++i) {
        CHECK(b[i] == 2);
    }

    CHECK_THROWS_WITH(b.resize(-16, 8), "Length can't be negative!");

    b.resize(0);
    CHECK(b.Empty());

    b.assign(14, 52);
    CHECK(b.Size() == 14);
    for (int64_t i = 0; i < b.Size(); ++i) {
        CHECK(b[i] == 52);
    }

    CHECK_THROWS_WITH(b.assign(-16, 8), "Length can't be negative!");

    b.assign(0);
    CHECK(b.Empty());
    CHECK(b.end() == b.GetData() + 0);

    int64_t old_size_c = c.Size();
    int64_t old_size_d = d.Size();
    int64_t old_capacity_c = c.Capacity();
    int64_t old_capacity_d = d.Capacity();
    int* old_data_c = c.GetData();
    int* old_data_d = d.GetData();
    d.swap(c);
    CHECK(d.Size() == old_size_c);
    CHECK(c.Size() == old_size_d);
    CHECK(d.Capacity() == old_capacity_c);
    CHECK(c.Capacity() == old_capacity_d);
    CHECK(d.GetData() == old_data_c);
    CHECK(c.GetData() == old_data_d);

    d_copy = d;
    d.insert(0, 75);
    CHECK(d[0] == 75);
    for (int64_t i = 1; i < d.Size(); ++i) {
        CHECK(d[i] == d_copy[i - 1]);
    }
    d_copy = d;
    d.insert(4, 32);
    CHECK(d[4] == 32);
    for (int64_t i = 0; i < d.Size(); ++i) {
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
    for (int64_t i = 0; i < d.Size(); ++i) {
        if (i == 7) {
            continue;
        }
        CHECK(d[i] == d_copy[i]);
    }
}
