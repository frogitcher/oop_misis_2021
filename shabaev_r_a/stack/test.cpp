//
// Created by 11_11 on 23.04.2022.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "stack.h"

TEST_CASE("check iterators"){
    list<int> mas={1,2,3,4,5,6,7,8,9};
    SUBCASE("check .begin()"){
        auto it=mas.begin();
        CHECK(*it == 1);
        it=std::next(it,3);
        CHECK(*it==4);
        it=std::next(it,3);
        CHECK(*it==7);
        it=std::prev(it, 1);
        CHECK(*it==6);
        const auto m2=mas;
        const auto it1=m2.begin();
        CHECK(typeid(it1).name() == typeid(list<int>::const_iterator).name());
    }



}