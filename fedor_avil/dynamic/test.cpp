#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"
#include "iostream"
#include "string"

DynamicArray a = DynamicArray(2, 4);
DynamicArray b(5);
DynamicArray a_copy(a);
DynamicArray a_copy2 = a;
DynamicArray c{ 1,2,3,4 };
TEST_CASE("Testing Contructors") {
    std::stringstream ss;
    
    for (int i = 0; i < a.Size(); i++) {
        ss << a[i];
    }
    CHECK(ss.str() == "44");
    ss.str(std::string());
    for (int i = 0; i < b.Size(); i++) {
        ss << b[i];
    }
    CHECK(ss.str() == "00000");
    CHECK(b.Size() == 5);
    ss.str(std::string());
    for (int i = 0; i < c.Size(); i++) {
        ss << c[i];
    }
    CHECK(ss.str() == "1234");
    ss.str(std::string());
    /*  int result = 0;
    while (true) {
        Dynamic_Array a;
        a.assign(10000, 1);
        for (auto item : a) result += item;
        std::cout << result << std::endl;
    }*/
}

TEST_CASE("Testing Editors") {

    a_copy2.push_back(4);
    a_copy2.push_back(4);
    a_copy2.push_back(4);
    a_copy2.push_back(4);
    CHECK(a_copy2 == DynamicArray(6, 4));
    a_copy2.pop_back();
    a_copy2.pop_back();
    a_copy2.pop_back();
    a_copy2.pop_back();
    CHECK(a_copy2 == DynamicArray(2, 4));
    a_copy2.clear();
    CHECK(a_copy2 == DynamicArray(0));
    CHECK(a_copy2.Empty());
    a_copy2.insert(0, 1);
    CHECK(!(a_copy2.Empty()));
    CHECK(a_copy2 == DynamicArray(1, 1));
    a_copy2.assign(5, 3);
    CHECK(a_copy2 == DynamicArray(5, 3));
    a_copy2.insert(1, 5);
    CHECK(a_copy2[1] == 5);
    a_copy2.erase(1);
    CHECK(a_copy2 == DynamicArray(5, 3));
    a_copy2.swap(a_copy);
    CHECK(a_copy2 == a);
}

TEST_CASE("Testing boolean functions") {
    CHECK(DynamicArray(1, 2) <= DynamicArray(1, 2));
    CHECK(DynamicArray(1, 2) < DynamicArray(1, 3));
    CHECK(DynamicArray(1, 2) < DynamicArray(3, 2));
    CHECK(DynamicArray(2) < DynamicArray(3, 2));
    CHECK(DynamicArray(3, 2) > DynamicArray(3, 1));
    CHECK(DynamicArray(3, 2) > DynamicArray(1, 2));
    CHECK(DynamicArray(3, 2) > DynamicArray(3));
    CHECK(DynamicArray(3, 2) >= DynamicArray(3, 2));
    CHECK(DynamicArray(2) == DynamicArray(2));
    CHECK(DynamicArray(2,2) == DynamicArray(2,2));
    CHECK(DynamicArray(3,2) == DynamicArray(3,2));
    CHECK(DynamicArray(2) != DynamicArray(3));
}

TEST_CASE("Testing exceptions") {
    CHECK_THROWS_WITH(DynamicArray(2).at(2), "Index Out Of Range");
    CHECK_THROWS_WITH(DynamicArray(2).erase(2), "Index Out Of Range");
    CHECK_THROWS_WITH(DynamicArray(0).pop_back(), "Array Size <0");
    CHECK_THROWS_WITH(DynamicArray(0).insert(1, 1);, "Index Out Of Range");
}