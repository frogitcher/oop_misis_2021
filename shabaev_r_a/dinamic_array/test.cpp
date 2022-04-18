#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include "stable_dinamic_array.h"


TEST_CASE("Testing iterator"){

    Stable_Dynamic_Array mas{1, 2, 3, 4, 5, 6};
    SUBCASE("check *"){
        auto it=mas.begin();
        it++;
        CHECK(*it==2);
    }
    SUBCASE("swapping elements"){
        auto it=mas.begin();
        std::swap(mas[0], mas[1]);
        CHECK(*it == 2);
    }
    SUBCASE("a lot of pushback"){
        auto it=mas.begin();
        for (int i = 0; i < 1000; ++i) {
            mas.push_back(i);
        }
        it+=1005;
        CHECK(*it==999);
    }
    SUBCASE("check end"){
        auto it=mas.begin();
        it+=mas.Size();
        CHECK((it == mas.end()));
        CHECK(*(mas.end()-1)==6);

    }
    SUBCASE("check arithmetic"){
        auto it=mas.begin();
        CHECK(*(it+2) ==3);
        it+=4;
        CHECK(*(it) == 5);
        CHECK(*(it-1)==4);
        it-=2;
        CHECK(*(it)==3);
        CHECK(*(it++)==3);
        CHECK(*(it)==4);
        CHECK(*(it--)==4);
        CHECK(*(it)==3);
        CHECK(*(++it)==4);
        CHECK(*(--it)==3);
    }

}

TEST_CASE("testing size and empty"){
    Stable_Dynamic_Array mas={1, 2, 3};
    CHECK(mas.Size()==3);
    CHECK(mas.Empty() == false);
    for(int i=0; i<100; i++){
        mas.push_back(i);
    }
    CHECK(mas.Size()==103);
    CHECK(mas.Empty() == false);
    for(int i=0; i<103; i++){
        mas.pop_back();
    }
    CHECK(mas.Size()==0);
    CHECK(mas.Empty() == true);
    mas.resize(100);
    CHECK(mas.Size()==100);
    CHECK(mas.Empty() == false);
}


TEST_CASE("testing push_back/insert") {
    SUBCASE("empty array") {
        Stable_Dynamic_Array mas;
        SUBCASE("push_back") {
            mas.push_back(4);
            CHECK(mas.Size() == 1);
            CHECK(mas[0] == 4);
        }
        SUBCASE("insert") {
            mas.insert(0, 4);
            CHECK(mas.Size() == 1);
            CHECK(mas[0] == 4);
        }
    }
    SUBCASE("array with some elements") {
        Stable_Dynamic_Array mas = {1, 2, 3, 4};
        SUBCASE("push_back") {
            mas.push_back(10);
            CHECK((mas.Size() == 5));
            CHECK((mas[4] == 10));
        }
        SUBCASE("insert in end") {
            mas.insert(4, 10);
            CHECK(mas.Size() == 5);
            CHECK(mas[4] == 10);
        }
        SUBCASE("insert in middle") {
            mas.insert(2, 10);
            CHECK(mas.Size() == 5);
            CHECK(mas == Stable_Dynamic_Array{1, 2, 10, 3, 4});
        }
    }
    SUBCASE("some test for insert"){
        Stable_Dynamic_Array mas;
        CHECK_THROWS_WITH(mas.insert(4, 4), "out of range");
    }
}

TEST_CASE("check [] and at()"){
    Stable_Dynamic_Array mas={1};
    CHECK(mas[0]==1);
    CHECK(mas.at(0)==1);
    CHECK_THROWS_WITH(mas.at(1), "out of range");
}

TEST_CASE("check =="){
    SUBCASE("empty mas"){
        Stable_Dynamic_Array mas, mas1;
        CHECK(mas==mas1);
        mas.push_back(1);
        CHECK(mas!=mas1);
    }
    SUBCASE("uwu"){

        Stable_Dynamic_Array mas={1, 1, 1, 2};
        Stable_Dynamic_Array mas1(4, 1);
        CHECK(mas!=mas1);
        mas1.pop_back();
        mas1.push_back(2);
        CHECK(mas==mas1);
    }
}





