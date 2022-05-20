#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "DynamicArray.h"
#include <string>
// #include <iostream>
// using namespace std;

TEST_CASE("a") {

    DynamicArray a1{5, 1}, a2{1,1,1,1,1}, a3{6,1}, a4{5,1}, a5(5, 1), a6(5, 1), a7(5,2);
    SUBCASE("Testing boolean operators")
    {
        CHECK((a1 == a2) == false);
        CHECK((a1 == a3) == false);
        CHECK((a1 == a4) == true);
        CHECK((a5 == a6) == true);
        CHECK((a5 == a7) == false);
        CHECK((a1 != a2) == true);
        CHECK((a2 != a3) == true);
        CHECK((a1 != a4) == false);
        CHECK((a5 != a7) == true);
        CHECK((a5 != a6) == false);
    }
}

TEST_CASE("b") {
    DynamicArray a1(5, 1), a2{1,2,3,4,5,6,7};
    SUBCASE("Testing position operators")
    {
        CHECK_THROWS_WITH(a1.At(6), "index out of range");
        CHECK((a2[0] == 1) == true);
        CHECK((a2[1] == 2) == true);
        CHECK((a2[2] == 3) == true);
        CHECK((a2[3] == 4) == true);
        CHECK((a2[4] == 5) == true);
        CHECK((a2[5] == 6) == true);
        CHECK((a2[6] == 7) == true);

        CHECK((a2.At(0) == 1) == true);
        CHECK((a2.At(1) == 2) == true);
        CHECK((a2.At(2) == 3) == true);
        CHECK((a2.At(3) == 4) == true);
        CHECK((a2.At(4) == 5) == true);
        CHECK((a2.At(5) == 6) == true);
        CHECK((a2.At(6) == 7) == true);
    }
}

TEST_CASE("c") {
    DynamicArray a1{1,2,3,4,5}, a2;
    SUBCASE("Testing changing vector"){
        a1.Push_back(6);
        a1.Push_back(7);
        CHECK((a1 == DynamicArray{1,2,3,4,5,6,7}) == true);
        CHECK(a1.Size() == 7);
        a1.Pop_back();
        CHECK(a1.Size() == 6);
        CHECK((a1 == DynamicArray{1,2,3,4,5,6}) == true);

        for (int i = 0; i < 6; i++)
            a1.Pop_back();
        CHECK(a1.Size() == 0);
        CHECK((a1 == a2) == true);
        a1 = DynamicArray{1,2,3,4,5};
        CHECK(a1.Size() == 5);
        a1.Clear();
        CHECK(a1.Size() == 0);
        CHECK(a1.Empty());
        a1 = DynamicArray{1,2,3,4,5};
        a1.Erase(0);
        CHECK(a1 == DynamicArray{2,3,4,5});
        a1.Insert(0, 1);
        CHECK(a1 == DynamicArray{1,2,3,4,5});
        a1.Erase(2);
        CHECK(a1 == DynamicArray{1,2,4,5});
        a1.Insert(2, 3);
        CHECK(a1 == DynamicArray{1,2,3,4,5});
    }
}

TEST_CASE("D") {
    DynamicArray a1{6,5,4,3,2,1};
    a1.Resize(4);
    CHECK(a1.Size() == 4);
    a1.Assign(6, 1);
    for (int i = 0; i < 6; i++)
    {
        CHECK(a1[i] == 1);
    }
    DynamicArray a2{10,5,4};
    a2.Resize(6, 0);
    for (int i = 3; i < 6; i++)
    {
        CHECK(a2[i] == 0);
    }
    CHECK(*a2.Begin() == 10);
    CHECK(*(a2.End()-1) == 0);
    a1.Swap(a2);
    CHECK(a1 == DynamicArray{10,5,4,0,0,0});
    CHECK(a2 == DynamicArray{1,1,1,1,1,1});
}
