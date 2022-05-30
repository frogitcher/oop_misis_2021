#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Testing operators and methods") {

    CHECK(DynamicArray(2, 0).Size() == 2);
    CHECK(DynamicArray(2, 0).Capacity() == 2);
    CHECK(!DynamicArray(2, 0).Empty());

    CHECK(DynamicArray{1, 2, 3, 4, 5}[2] == 3);
    CHECK(DynamicArray{1, 2, 3, 4, 5}.at(2) == 3);


    DynamicArray arr1{1, 2, 3, 4, 5};
    arr1.push_back(6);
    CHECK(arr1 == DynamicArray{1, 2, 3, 4, 5, 6});


    DynamicArray arr2{1, 2, 3, 4, 5, 6};
    arr2.pop_back();
    CHECK(arr2 == DynamicArray{1, 2, 3, 4, 5});


    DynamicArray arr3{1, 2, 3, 4, 5};
    arr3.clear();
    CHECK(arr3.Empty() == true);


    DynamicArray arr4{1, 2, 3, 4, 5};
    arr4.erase(2);
    CHECK(arr4 == DynamicArray{1, 2, 4, 5});


    DynamicArray arr5{1, 2, 4, 5};
    arr5.insert(2, 3);
    CHECK(arr5.Size() == 5);
    CHECK(arr5 == DynamicArray{1, 2, 3, 4, 5});


    DynamicArray arr6{1, 2, 3, 4};
    arr6.resize(2);
    CHECK(arr6.Size() == 2);
    CHECK(arr6[1] == 2);

    DynamicArray arr7{1, 2, 3, 4};
    arr7.resize(7, 0);
    CHECK(arr7.Size() == 7);
    CHECK(arr7[6] == 0);


    DynamicArray arr8{1, 2, 3, 4};
    arr8.assign(5, 0);
    CHECK(arr8 == DynamicArray{0, 0, 0, 0, 0});


    DynamicArray arr9{1, 2, 3, 4, 5};
    arr9.assign({5, 4, 3, 2, 1, 0});
    CHECK(arr9 == DynamicArray{5, 4, 3, 2, 1, 0});


    DynamicArray arr10{1, 2, 3, 4, 5};
    DynamicArray arr11{5, 4, 3, 2, 1};
    DynamicArray temp_arr = arr10;
    arr10.swap(arr11);
    CHECK(temp_arr == arr11);

    CHECK(DynamicArray{1, 2, 3, 4, 5} != DynamicArray{5, 4, 3, 2, 1});
}

TEST_CASE("Testing exceptions") {
    DynamicArray arr1{1, 2, 3, 4, 5};
    CHECK_THROWS_WITH(arr1[100], "Index out of range.");
    CHECK_THROWS_WITH((DynamicArray(5, 0).at(7)), "Index out of range.");
    CHECK_THROWS_WITH((DynamicArray{1, 2, 3, 4, 5}.insert(7, 0)), "Index out of range.");
    CHECK_THROWS_WITH((DynamicArray(0, 0).pop_back()), "Array is empty.");
    CHECK_THROWS_WITH((DynamicArray{1, 2, 3, 4, 5}.erase(7)), "Index out of range.");
}