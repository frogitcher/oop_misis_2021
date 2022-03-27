#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"
#include "iostream"

Dynamic_Array a = Dynamic_Array(2, 4);
Dynamic_Array b(5);
Dynamic_Array a_copy(a);
Dynamic_Array a_copy2 = a;

TEST_CASE("Testing Contructors") {
    for (int i = 0; i < a.Size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < b.Size(); i++) {
        std::cout << b[i] << " ";
    } 
    CHECK(b.Size() == 5);
    std::cout << std::endl;
    std::cout << a_copy.Size() << std::endl;
}

TEST_CASE("Testing Editors"){

    a_copy2.push_back(4);
    std::cout << a_copy2.Size() << " " << a_copy2.Capacity() << std::endl;
    CHECK(a_copy2 == Dynamic_Array(3, 4));
    a_copy2.pop_back();
    std::cout << a_copy2.Size() << " " << a_copy2.Capacity() << std::endl;
    CHECK(a_copy2 == Dynamic_Array(2, 4));
    a_copy2.clear();
    std::cout << a_copy2.Size() << " " << a_copy2.Capacity() << std::endl;
    CHECK(a_copy2 == Dynamic_Array(0));
    CHECK(a_copy2.Empty());
    a_copy2.insert(0, 1);
    std::cout << a_copy2.Size() << " " << a_copy2.Capacity() << std::endl;
    CHECK(a_copy2 == Dynamic_Array(1,1));
    a_copy2.assign(5, 3);
    std::cout << a_copy2.Size() << " " << a_copy2.Capacity() << std::endl;
    CHECK(a_copy2 == Dynamic_Array(5, 3));
    a_copy2.erase(1);
    std::cout << a_copy2.Size() << " " << a_copy2.Capacity() << std::endl;
    std::cout << a_copy.Size() << " ";
    //std::cout << a_copy2.Size() << " ";
    CHECK(a_copy2 == Dynamic_Array(4, 3));
    a_copy2.swap(a_copy);
    //std::cout << a_copy2.Size();

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
    //CHECK_THROWS_WITH(Dynamic_Array(0).pop_back(), "Array Size <0");
    //CHECK_THROWS_WITH(Dynamic_Array(0).insert(1, 1); , "Index Out Of Range");

}