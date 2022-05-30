#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "dyn_array.h"
#include <iostream>

TEST_CASE("Testing constructors") {
    DynamicArray first(20);
    CHECK(first.Size() == 20);
    CHECK(first.Capacity() == 20);
    DynamicArray second;
    CHECK(first.Empty() == false);
    CHECK(second.Empty() == true);

    DynamicArray third{0, 1, 2, 3, 4, 5, 6};
    CHECK(third[1] == 1);
    CHECK(third[6] == 6);
    CHECK(third.Capacity() == 7);

    DynamicArray fourth(third);
    CHECK(fourth == third);

    DynamicArray fifth{0, 1, 2, 3};
    CHECK(fifth != fourth);
    fifth = fourth;
    CHECK(fifth == fourth);
    fifth.erase(1);
    CHECK(fifth != fourth);
}

TEST_CASE("Testing methods") {
    DynamicArray second;
    second.push_back(7);
    second.push_back(100);
    second.push_back(1);
    CHECK_THROWS_WITH(second.at(3), "Index out of range error");
    CHECK(second[2] == 1);
    CHECK(second[1] == 100);
    CHECK(second[0] == 7);
    CHECK(second.Capacity() == 3);
    CHECK(second.Size() == 3);

    second.pop_back();
    CHECK_THROWS_WITH(second.at(2), "Index out of range error");
    CHECK(second[1] == 100);
    CHECK(second.Size() == 2);
    CHECK(second.Capacity() == 3);

    second.clear();
    CHECK(second.Empty() == true);
    CHECK_THROWS_WITH(second.at(0), "Index out of range error");
    DynamicArray first{1, 2, 4, 8, 16, 32};

    first.erase(1);
    CHECK(first == DynamicArray{1, 4, 8, 16, 32});
    CHECK(first.Size() == 5);
    CHECK(first.Capacity() == 6);
    CHECK_THROWS_WITH(first.erase(5), "Index out of range error");

    first.insert(1, 2);
    CHECK(first == DynamicArray{1, 2, 4, 8, 16, 32});
    CHECK(first.Size() == 6);
    CHECK(first.Capacity() == 6);
    first.insert(0, 0);
    CHECK(first == DynamicArray{0, 1, 2, 4, 8, 16, 32});
    CHECK(first.Size() == 7);
    CHECK(first.Capacity() == 13);

    first.resize(9);
    CHECK(first.Size() == 9);
    first.resize(3);
    CHECK(first == DynamicArray{0, 1, 2});
    CHECK(first.Size() == 3);
    CHECK_THROWS_WITH(first.at(3), "Index out of range error");

    first.assign(5, 100);
    CHECK(first == DynamicArray{100, 100, 100, 100, 100});
    CHECK_THROWS_WITH(first.at(5), "Index out of range error");
    first.assign(3, 100);
    CHECK(first == DynamicArray{100, 100, 100});
    CHECK_THROWS_WITH(first.at(3), "Index out of range error");
    first.resize(0);
    first.push_back(0);
    first.push_back(1);
    first.push_back(2);
    DynamicArray third{2, 1, 0};

    first.swap(third);
    CHECK(first == DynamicArray{2, 1, 0});
    CHECK(third == DynamicArray{0, 1, 2});
    DynamicArray fourth{2, 1};
    DynamicArray fifth{4, 2, 1, 0};
    fourth.swap(fifth);
    CHECK(fifth == DynamicArray{2, 1});
    CHECK(fourth == DynamicArray{4, 2, 1, 0});

    DynamicArray first;
    CHECK(first.begin() == first.end());
    DynamicArray second{1, 2, 4, 8, 16, 32};
    DynamicArray third{1, 2, 4, 8, 16, 32};
    CHECK(second.begin() + second.Size() == second.end());

    CHECK(second == third);
    CHECK(second != first);
}