#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include "stable_dinamic_array.h"


TEST_CASE("Testing iterator"){

    Stable_Dynamic_Array mas={1, 2, 3, 4, 5, 6};
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

