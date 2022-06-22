#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Basic functions") {
CHECK((DynamicArray(5).Size()) == 5);
CHECK((DynamicArray(5).Capacity()) == 5);
CHECK((DynamicArray(5).Empty()) == false);

CHECK((DynamicArray{1,2,3,4,5}[2]) == 3);
CHECK((DynamicArray{1,2,3,4,5}.at(2)) == 3);
DynamicArray arr4{1,2,3,4,5};
arr4.push_back(6);
CHECK((arr4) == DynamicArray{1,2,3,4,5,6});
DynamicArray arr5{1,2,3,4,5,6};
arr5.pop_back();
CHECK((arr5) == DynamicArray{1,2,3,4,5});
DynamicArray arr6{1,2,3,4,5};
arr6.clear();
CHECK((arr6.Empty()) == true);
DynamicArray arr7{1,2,3,4,5};
arr7.erase(2);
CHECK((arr7) == DynamicArray{1,2,4,5});
DynamicArray arr8{1,2,4,5};
arr8.insert(2,3);
CHECK((arr8.Size()) == 5);
DynamicArray arr9{1,2,4,5};
arr9.resize(3);
CHECK((arr9.Size()) == 3);
DynamicArray arr10{1,2,4,5};
arr10.resize(7);
CHECK((arr10.Size()) == 7);
DynamicArray arr11{1,2,4,5};
arr11.assign(3, 0);
CHECK((arr11) == DynamicArray{0,0,0});
DynamicArray arr12{1,2,4,5};
arr12.assign(7, 0);
CHECK((arr12) == DynamicArray{0,0,0,0,0,0,0});
DynamicArray arr1{1,2,3,4,5};
DynamicArray arr2{5,4,3,2,1};
DynamicArray arr3{1,2,3,4,5};
arr1.swap(arr2);
CHECK(arr2 == arr3);
CHECK((arr2 == arr3) == true);
CHECK((arr1 != arr2) == true);
}
TEST_CASE("Testing exceptions") {
CHECK_THROWS_WITH((DynamicArray(5).at(7)), "Index must be lower than size of array");
CHECK_THROWS_WITH((DynamicArray(0).pop_back()), "There is nothing to pop");
CHECK_THROWS_WITH((DynamicArray{1,2,3,4,5}.erase(7)), "Index out of range");
CHECK_THROWS_WITH((DynamicArray{1,2,3,4,5}.insert(7,0)),"Index out of range");
}