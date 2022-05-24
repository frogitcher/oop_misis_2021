#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

#include <iostream>

TEST_CASE("Testing dynamic array's")
{
    dynamic_array a;
    CHECK(a.empty());
    CHECK(a.Size() == 0);
    CHECK(a.begin() == a.end());
    CHECK(a.Capacity() == 0);
    CHECK_THROWS_WITH(a[2], "Index out of range!");
    CHECK_THROWS_WITH(a.Pop_back(), "Size is empty!");

    dynamic_array b(3, 1);
    CHECK_FALSE(b.empty());
    CHECK(b[b.Size() - 1] == 1);
    CHECK(b.Size() <= b.Capacity());
    dynamic_array new_b(b);
    b.Push_back(2);
    CHECK(new_b.Size() != b.Size());
    CHECK(new_b.Size()+1 == b.Size());

    dynamic_array x(b);
    CHECK(x.Size() == b.Size());
    CHECK(x.Capacity() == b.Capacity());
    CHECK(x[1] == b.at(1));

    dynamic_array y({ 1,2,3,4,5 });
    CHECK_FALSE(x != b);
    CHECK_FALSE(x == y);
    CHECK(x != y);

    dynamic_array new_y(y);
    CHECK(new_y.Size() == y.Size());
    new_y.Pop_back();
    CHECK(new_y.Size() < y.Size());
    CHECK(new_y.Capacity() == y.Capacity());
    new_y.Push_back(5);
    new_y.Erase(0);
    CHECK(new_y.Size() < y.Size());

    y.Resize(12, 4);
    CHECK(y.Size() == 12);
    y.Resize(0);
    CHECK(y.Size() == 0);
    new_y.Clear();
    CHECK(new_y.empty());
    b.insert(2, 6);
    CHECK(b[2] == 6);
}