#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"
#include "iostream"

Dynamic_Array a = Dynamic_Array(2, 4);
Dynamic_Array b(5);
Dynamic_Array a_copy(a);
Dynamic_Array a_copy2 = a;
Dynamic_Array c{ 1,2,3,4 };
TEST_CASE("Testing Contructors") {
    std::cout << "TWO ARGUMENTS: ";
    for (int i = 0; i < a.Size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl << "ONE ARGUMENT: ";
    for (int i = 0; i < b.Size(); i++) {
        std::cout << b[i] << " ";
    } 

    CHECK(b.Size() == 5);
    std::cout << std::endl<<"INITIALIZER: ";
    for (int i = 0; i < c.Size(); i++) {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl;
}

TEST_CASE("Testing Editors"){

    a_copy2.push_back(4);
    CHECK(a_copy2 == Dynamic_Array(3, 4));
    a_copy2.pop_back();
    CHECK(a_copy2 == Dynamic_Array(2, 4));
    a_copy2.clear();
    CHECK(a_copy2 == Dynamic_Array(0));
    CHECK(a_copy2.Empty());
    a_copy2.insert(0, 1);
    CHECK(a_copy2 == Dynamic_Array(1,1));
    a_copy2.assign(5, 3);
    CHECK(a_copy2 == Dynamic_Array(5, 3));
    a_copy2.erase(1);
    CHECK(a_copy2 == Dynamic_Array(4, 3));
    a_copy2.swap(a_copy);

    CHECK(a_copy2 == a);
}

TEST_CASE("Testing boolean functions") {
    CHECK(Dynamic_Array(1,2)<=Dynamic_Array(1,2));
    CHECK(Dynamic_Array(1, 2)<Dynamic_Array(1,3));
    CHECK(Dynamic_Array(1, 2)<Dynamic_Array(3,2));
    CHECK(Dynamic_Array(2)<Dynamic_Array(3,2));
    CHECK(Dynamic_Array(3, 2)>Dynamic_Array(3,1));
    CHECK(Dynamic_Array(3, 2)>Dynamic_Array(1,2));
    CHECK(Dynamic_Array(3, 2)>Dynamic_Array(3));
    CHECK(Dynamic_Array(3, 2)>=Dynamic_Array(3,2));
    CHECK(Dynamic_Array(2) == Dynamic_Array(2));
    CHECK(Dynamic_Array(2)!=Dynamic_Array(3));
}

TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(Dynamic_Array(2)[2], "Index Out Of Range");
    CHECK_THROWS_WITH(Dynamic_Array(0).pop_back(), "Array Size <0");
    CHECK_THROWS_WITH(Dynamic_Array(0).insert(1, 1); , "Index Out Of Range");
}