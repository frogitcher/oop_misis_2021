#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Testing dynamic_array") {
    DynamicArray arr1;
    CHECK(arr1.Size() == 0);
    CHECK(arr1.begin() == arr1.GetData());

    DynamicArray arr2(5, 7);
    CHECK(arr2.Size() == 5);
    CHECK(arr2.Capacity() >= arr2.Size());

    DynamicArray arr3(arr2);
    CHECK(arr3.Size() == arr2.Size());
    CHECK(arr3.Capacity() == arr2.Capacity());
    for (int64_t i = 0; i < arr2.Size(); i++) {
        CHECK(&(arr3[i]) == (arr3.begin() + i));
        CHECK(arr3[i] == arr2[i]);
    }

    DynamicArray arr4({2, 4, 8, 1, 1, 7});
    CHECK_FALSE(arr3 == arr4);
    CHECK(arr3 != arr4);
    CHECK_FALSE(arr3 != arr2);

    // arr1 empty
    CHECK(arr1.Empty());

    // arr2 not empty
    CHECK_FALSE(arr2.Empty());
    CHECK_THROWS_WITH(arr1.at(1), "Out of range!");
    int64_t old_size = arr2.Size();
    arr2.push_back(-17);
    CHECK(arr2.Size() == old_size + 1);
    CHECK(arr2[arr2.Size() - 1] == -17);
    DynamicArray arr4_copy(arr4);
    Reallocate(arr4, 50);
    CHECK(arr4_copy.Size() == arr4.Size());
    CHECK(arr4.Capacity() == arr4_copy.Capacity());
    for (int64_t i = 0; i < arr4.Size(); i++) {
        CHECK(arr4[i] == arr4_copy[i]);
    }

    old_size = arr4.Size();
    arr4.pop_back();
    CHECK(arr4.Size() == old_size - 1);
    for (int64_t i = 0; i < arr4.Size(); i++) {
        CHECK(arr4[i] == arr4_copy[i]);
    }
    CHECK_THROWS_WITH(arr1.pop_back(), "The array is empty!");

    arr4.clear();
    CHECK(arr4.Empty());

    DynamicArray arr2_copy(arr2);
    arr2.erase(0);
    CHECK(arr2.Size() == arr2_copy.Size() - 1);
    for (int64_t i = 0; i < arr2.Size(); i++) {
        CHECK(arr2[i] == arr2_copy[i + 1]);
    }
    arr2.erase(3);
    CHECK(arr2.Size() == arr2_copy.Size() - 2);
    for (int64_t i = 0; i < arr2.Size(); i++) {
        if (i >= 3) {
            CHECK(arr2[i] == arr2_copy[i + 2]);
            continue;
        }
        CHECK(arr2[i] == arr2_copy[i + 1]);
    }
    arr2.erase(arr2.Size() - 1);
    CHECK(arr2.Size() == arr2_copy.Size() - 3);
    for (int64_t i = 0; i < arr2.Size(); i++) {
        if (i >= 3) {
            CHECK(arr2[i] == arr2_copy[i + 2]);
            continue;
        }
        CHECK(arr2[i] == arr2_copy[i + 1]);
    }
    old_size = arr2.Size();
    arr2.resize(23, 125);
    CHECK(arr2.Size() == 23);
    for (int64_t i = 0; i < old_size; i++) {
        CHECK(arr2[i] == 7);
    }
    for (int64_t i = old_size + 1; i < arr2.Size(); i++) {
        CHECK(arr2[i] == 125);
    }

    CHECK_THROWS_WITH(arr2.resize(-500, 8), "The size of the array cannot be less than zero!");

    arr2.resize(0);
    CHECK(arr2.Empty());

    arr2.assign(14, 52);
    CHECK(arr2.Size() == 14);
    for (int64_t i = 0; i < arr2.Size(); i++) {
        CHECK(arr2[i] == 52);
    }

    CHECK_THROWS_WITH(arr2.assign(-16, 8), "Size cannot be less than zero!");

    arr2.assign(0);
    CHECK(arr2.Empty());
    CHECK(arr2.end() == arr2.GetData() + 0);

    int64_t old_size_arr3 = arr3.Size();
    int64_t old_size_arr4 = arr4.Size();
    int64_t old_capacity_arr3 = arr3.Capacity();
    int64_t old_capacity_d = arr4.Capacity();
    int* old_data_arr3 = arr3.GetData();
    int* old_data_d = arr4.GetData();
    arr4.swap(arr3);
    CHECK(arr4.Size() == old_size_arr3);
    CHECK(arr3.Size() == old_size_arr4);
    CHECK(arr4.Capacity() == old_capacity_arr3);
    CHECK(arr3.Capacity() == old_capacity_d);
    CHECK(arr4.GetData() == old_data_arr3);
    CHECK(arr3.GetData() == old_data_d);

    arr4_copy = arr4;
    arr4.insert(0, 512);
    CHECK(arr4[0] == 512);
    for (int64_t i = 1; i < arr4.Size(); i++) {
        CHECK(arr4[i] == arr4_copy[i - 1]);
    }
    arr4_copy = arr4;
    arr4.insert(4, 17);
    CHECK(arr4[4] == 17);
    for (int64_t i = 0; i < arr4.Size(); i++) {
        if (i == 4) {
            continue;
        }
        if (i > 4) {
            CHECK(arr4[i] == arr4_copy[i - 1]);
            continue;
        }
        CHECK(arr4[i] == arr4_copy[i]);
    }
    arr4_copy = arr4;
    arr4.insert(7, -1);
    CHECK(arr4[7] == -1);
    for (int64_t i = 0; i < arr4.Size(); i++) {
        if (i == 7) {
            continue;
        }
        CHECK(arr4[i] == arr4_copy[i]);
    }
}
