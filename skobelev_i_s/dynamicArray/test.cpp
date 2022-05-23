#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"

TEST_CASE("checking results") {
    DynamicArray one;
    DynamicArray two{15, 5, 6, 7, 8, 10};
    DynamicArray three(5, 9);
    DynamicArray four(7, 0);
    DynamicArray copy(two);

	CHECK(*(two.begin()) == 15);
	CHECK(*(two.end() - 1) == 10);
    CHECK(one.Size() == 0);
    CHECK(three.Size() == 5);
    CHECK(one.Empty() == true);
    CHECK(three.Capacity() == 5);
    CHECK_THROWS_WITH(three.at(100), "index out of range");
    CHECK_THROWS_WITH(one.Pop_back(), "The array is empty");

    for (int i = 0; i < three.Size(); i++) {
        CHECK(three.at(i) == 9);
        CHECK(three[i] == 9);
    }

    for (int i = 0; i < two.Size(); i++) {
        CHECK(two[i] == copy[i]);
    }
    CHECK(two.Size() == copy.Size());

    CHECK(two.Size() == copy.Size());

    two.Push_back(5);
    CHECK(two[two.Size() - 1] == 5);
    two.Pop_back();
    CHECK(two[two.Size() - 1] == 10);

    four.Clear();
    CHECK(four.Size() == 0);

    two.Erase(0);
    CHECK(two[0] == 5);

    four.Resize(5);
    CHECK(four.Size() == 5);
    for (int i = 0; i < four.Size(); i++) {
        CHECK(four[i] == 0);
    }

    four.Assign(10, 5);
    CHECK(four.Size() == 10);
    for (int i = 0; i < four.Size(); i++) {
        CHECK(four[i] == 5);
    }

    CHECK_THROWS_WITH(four.Insert(-100, 5), "index out of range");
    four.Insert(5, 50);
    CHECK(four[5] == 50);

    DynamicArray test1{1, 2, 3};
    DynamicArray copy1(test1);
    DynamicArray test2{4, 5, 6, 7};
    DynamicArray copy2(test2);

    test1.Swap(test2);
    for (int i = 0; i < 3; i++) {
        CHECK(test1[i] == copy2[i]);
    }
    for (int i = 0; i < 4; i++) {
        CHECK(test2[i] == copy1[i]);
    }

    CHECK(test2 == copy1);
    CHECK(test1 != copy1);

    copy1 = copy2;
    for (int i = 0; i < 4; i++) {
        CHECK(copy1[i] == copy2[i]);
    }
}
