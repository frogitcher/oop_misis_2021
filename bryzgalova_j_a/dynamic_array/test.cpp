#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "iostream"
#include "string"
#include "doctest.h"
#include "dynamic.h"

DynamicArray a = DynamicArray(1, 4);
DynamicArray a_copy(a);
DynamicArray a_copy2 = a;
DynamicArray b(5);
DynamicArray c{0, 1, 2, 3};

TEST_CASE("Testing dynamic_array_01") {
    std::stringstream sl;
    for (int i = 0; i < a.Size(); i++) {
        sl << a[i];
    }
  
    CHECK(sl.str() == "4");
    sl.str(std::string());
    for (int i = 0; i < b.Size(); i++) {
        sl << b[i];
    }
  
    CHECK(sl.str() == "00000");
    CHECK(b.Size() == 5);
    sl.str(std::string());
    for (int i = 0; i < c.Size(); i++) {
        sl << c[i];
    }
    CHECK(sl.str() == "0123");
    sl.str(std::string());
}

TEST_CASE("Testing dynamic_array_02") {
      CHECK(DynamicArray(5) == DynamicArray(5));
    CHECK(DynamicArray(2,2) == DynamicArray(2,2));
    CHECK(DynamicArray(5,2) == DynamicArray(5,2));
    CHECK(DynamicArray(2) != DynamicArray(5));
    CHECK(DynamicArray(1, 2) <= DynamicArray(1, 2));
    CHECK(DynamicArray(1, 2) < DynamicArray(1, 5));
    CHECK(DynamicArray(1, 2) < DynamicArray(5, 2));
    CHECK(DynamicArray(2) < DynamicArray(5, 2));
    CHECK(DynamicArray(3, 2) > DynamicArray(3, 1));
    CHECK(DynamicArray(5, 2) > DynamicArray(1, 2));
    CHECK(DynamicArray(3, 2) > DynamicArray(3));
    CHECK(DynamicArray(3, 2) >= DynamicArray(3, 2));
}


TEST_CASE("Testing dynamic_array_03") {
    a_copy2.push_back(4);
    a_copy2.push_back(4);
    a_copy2.push_back(4);
    CHECK(a_copy2 == DynamicArray(4, 4));
    a_copy2.pop_back();
    a_copy2.pop_back();
    a_copy2.pop_back();
    CHECK(a_copy2 == DynamicArray(1, 4));
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

TEST_CASE("Testing dynamic_array_04") {
    CHECK_THROWS_WITH(DynamicArray(2).at(2), "Index out of range!");
    CHECK_THROWS_WITH(DynamicArray(2).erase(2), "Index out of range!");
    CHECK_THROWS_WITH(DynamicArray(0).pop_back(), "Array Size < 0");
    CHECK_THROWS_WITH(DynamicArray(0).insert(1, 1);, "Index out of range!");
}
