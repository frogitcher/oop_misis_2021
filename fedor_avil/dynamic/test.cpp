#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"
#include "iostream"

Dynamic_Array a(2, 4);
Dynamic_Array b(5);
Dynamic_Array a_copy = a;

TEST_CASE("Testing Contructors") {
    for (int i = 0; i < a.Size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < b.Size(); i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
    CHECK(a_copy == a);
}

TEST_CASE("Testing Editors") {
    Dynamic_Array a_copy2 = a_copy;
    a_copy2.push_back(4);
    CHECK(a_copy2 == Dynamic_Array(3, 4));
    a_copy2.pop_back();
    CHECK(a_copy2 == Dynamic_Array(2, 4));
    a_copy2.clear();
    CHECK(a_copy2 == Dynamic_Array(0));

}

/*TEST_CASE("Testing boolean functions") {
    CHECK(Dynamic_Array(1, 2)<=Dynamic_Array(1,2));
    CHECK(Dynamic_Array(1, 2)<Dynamic_Array(1,3));
    CHECK(Dynamic_Array(1, 2)<Dynamic_Array(3,2));
    CHECK(Dynamic_Array(2)<Dynamic_Array(3,2));
    CHECK(Dynamic_Array(3, 2)>Dynamic_Array(3,1));
    CHECK(Dynamic_Array(3, 2)>Dynamic_Array(1,2));
    CHECK(Dynamic_Array(3, 2)>Dynamic_Array(3));
    CHECK(Dynamic_Array(3, 2)>=Dynamic_Array(3,2));
    CHECK(Dynamic_Array(2)==Dynamic_Array(2));
    CHECK(Dynamic_Array(2)!=Dynamic_Array(3));
}*/


TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Dynamic_Array(2)[2], "Index Out Of Range");
    CHECK_THROWS_WITH(Dynamic_Array(0).pop_back(), "Array Size <0");
}