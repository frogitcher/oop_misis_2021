#include "dynamic_array.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>

using namespace Tripolsky_D_A;

TEST_CASE("Iterator"){

    DynamicArray<int> v{1, 2, 3, 4, 5, 6};
    SUBCASE("check *"){
        auto it=v.begin();
        it++;
        CHECK(*it==2);
    }
    SUBCASE("swap"){
        auto it=v.begin();
        std::swap(v[0], v[1]);
        CHECK(*it == 2);
    }
    SUBCASE("pushbacks"){
        auto it=v.begin();
        for (int i = 0; i < 667; ++i) {
            v.push_back(i);
        }
        it+=672;
        CHECK(*it==666);
    }
    SUBCASE("end() iterator"){
        auto it=v.begin();
        it+=v.size();
        CHECK((it == v.end()));
        CHECK(*(v.end()-1)==6);

    }
    SUBCASE("moving pointers"){
        auto it=v.begin();
        CHECK(*(it+1) ==2);
        it+=4;
        CHECK(*(it) == 5);
        CHECK(*(it-2)==3);
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

TEST_CASE("size,push,empty,pop"){
    DynamicArray<int> v={1, 2, 3, 4, 5};
    CHECK(v.size()==5);
    CHECK(v.Empty() == false);
    for(int i=0; i<77; i++){
        v.push_back(i);
    }
    CHECK(v.size()==82);
    CHECK(v.Empty() == false);
    for(int i=0; i<82; i++){
        v.pop_back();
    }
    CHECK(v.size()==0);
    CHECK(v.Empty() == true);
    v.resize(93);
    CHECK(v.size()==93);
    CHECK(v.Empty() == false);
}


TEST_CASE("push_back/insert") {
    SUBCASE("empty array") {
        DynamicArray<int> v;
        SUBCASE("push_back") {
            v.push_back(4);
            CHECK(v.size() == 1);
            CHECK(v[0] == 4);
        }
        SUBCASE("insert") {
            v.insert(0, 4);
            CHECK(v.size() == 1);
            CHECK(v[0] == 4);
        }
    }
    SUBCASE("array with some elements") {
        DynamicArray<int> v = {1, 2, 3, 4};
        SUBCASE("push_back") {
            v.push_back(10);
            CHECK((v.size() == 5));
            CHECK((v[4] == 10));
        }
        SUBCASE("insert in end") {
            v.insert(4, 10);
            CHECK(v.size() == 5);
            CHECK(v[4] == 10);
        }
        SUBCASE("insert in middle") {
            v.insert(2, 10);
            CHECK(v.size() == 5);
            CHECK(v == DynamicArray<int>{1, 2, 10, 3, 4});
        }
    }
    SUBCASE("some test for insert"){
        DynamicArray<int> v;
        CHECK_THROWS_WITH(v.insert(4,444), "out of range");
    }
}

TEST_CASE("check [] and at()"){
    DynamicArray<int> v={1};
    CHECK(v[0]==1);
    CHECK(v.at(0)==1);
    CHECK_THROWS_WITH(v.at(1), "out of range");
}
