#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "dynamic_array.cpp"

#include "doctest/doctest.h"

TEST_CASE("Testing DynamicArray constructors")
{
  CHECK(DynamicArray() == DynamicArray(0));
  CHECK(DynamicArray() == DynamicArray(0, 0));
  CHECK(DynamicArray(5) == DynamicArray(5, 0));

  DynamicArray arr(1, 7);
  CHECK(arr == DynamicArray(1, 7));
  CHECK(arr.size() == 1);

  DynamicArray arr1 = DynamicArray(2, 7);
  CHECK(arr1 == DynamicArray(2, 7));
  CHECK(arr1.size() == 2);

  DynamicArray arr2 = {3, 3};
  CHECK(arr2 == DynamicArray(2, 3));
  CHECK(arr2.size() == 2);

  DynamicArray arr3{4, 4, 4};
  CHECK(arr3 == DynamicArray(3, 4));
  CHECK(arr3.size() == 3);

  DynamicArray arr4({5, 5, 5, 5, 5, 5});
  CHECK(arr4 == DynamicArray(6, 5));
  CHECK(arr4.size() == 6);

  DynamicArray arr5 = {};
  CHECK(arr5 == DynamicArray());
  CHECK(arr5 == DynamicArray(0));
  CHECK(arr5.size() == 0);
}

TEST_CASE("Testing DynamicArray operators")
{
  DynamicArray arr(7, 2);
  DynamicArray arr1(3, 6);

  arr = arr1;
  CHECK(arr == arr1);
  CHECK(arr == DynamicArray(3, 6));
  CHECK(arr != DynamicArray(7, 2));

  for (int i = 0; i < arr.size(); ++i)
    CHECK(&arr[i] == arr.begin() + i);
}

TEST_CASE("Testing DynamicArray methods #1")
{
  DynamicArray arr(10, 5);
  CHECK(arr.size() == 10);
  CHECK(arr.capacity() == 10);
  CHECK(arr.empty() == false);

  arr.resize(2);
  CHECK(arr == DynamicArray(2, 5));
  CHECK(arr.size() == 2);
  CHECK(arr.capacity() >= 2);

  arr.shrink_to_fit();
  CHECK(arr.size() == 2);
  CHECK(arr.capacity() == 2);

  arr.push_back(5);
  CHECK(arr.size() == 3);
  CHECK(arr.capacity() == 4);

  arr.push_back(5);
  CHECK(arr.size() == 4);
  CHECK(arr.capacity() == 4);

  arr.push_back(5);
  CHECK(arr.size() == 5);
  CHECK(arr.capacity() == 8);

  arr.reserve(100);
  CHECK(arr.size() == 5);
  CHECK(arr.capacity() == 100);

  arr.resize(90, 7);
  CHECK(arr.size() == 90);
  CHECK(arr.capacity() == 100);

  arr.resize(110, 10);
  CHECK(arr.size() == 110);
  CHECK(arr.capacity() == 110);

  arr.push_back(10);
  CHECK(arr.size() == 111);
  CHECK(arr.capacity() == 220);

  arr.shrink_to_fit();
  CHECK(arr.size() == 111);
  CHECK(arr.capacity() == 111);

  arr.resize(0);
  CHECK(arr.size() == 0);
  CHECK(arr.capacity() == 111);
  CHECK(arr.empty() == true);
}

TEST_CASE("Testing DynamicArray methods #2")
{
  DynamicArray arr(100, 100);
  arr.clear();
  CHECK(arr.size() == 0);
  CHECK(arr.capacity() == 100);
  CHECK(arr.empty() == true);

  DynamicArray arr1({1, 2, 3, 4, 5});

  arr1.resize(8);
  DynamicArray arr2({1, 2, 3, 4, 5, 0, 0, 0});
  CHECK(arr1 == arr2);

  arr1.resize(6, 10);
  DynamicArray arr3({1, 2, 3, 4, 5, 0});
  CHECK(arr1 == arr3);

  arr1.resize(9, 15);
  DynamicArray arr4({1, 2, 3, 4, 5, 0, 15, 15, 15});
  CHECK(arr1 == arr4);
}

TEST_CASE("Testing DynamicArray methods #3")
{
  DynamicArray arr(2, 5);

  arr.pop_back();
  CHECK(arr.size() == 1);
  CHECK(arr.capacity() == 2);
  CHECK(arr.empty() == false);

  arr.pop_back();
  CHECK(arr.size() == 0);
  CHECK(arr.capacity() == 2);
  CHECK(arr.empty() == true);

  DynamicArray arr1;
  DynamicArray arr2;

  arr1.assign({1, 2, 3, 4});
  arr2.assign({5, 6, 7, 8, 9});
  arr1.swap(arr2);

  CHECK(arr1 == DynamicArray({5, 6, 7, 8, 9}));
  CHECK(arr2 == DynamicArray({1, 2, 3, 4}));
}

TEST_CASE("Testing DynamicArray methods #4")
{
  DynamicArray arr;
  arr.assign(2, 5);
  CHECK(arr == DynamicArray(2, 5));

  arr.assign(0, 0);
  CHECK(arr == DynamicArray());
  CHECK(arr.empty() == true);

  DynamicArray arr1({1, 2, 3, 4, 5});
  arr1.erase(1);
  CHECK(arr1 == DynamicArray({1, 3, 4, 5}));

  arr1.insert(1, 5);
  CHECK(arr1 == DynamicArray({1, 5, 3, 4, 5}));

  arr1.erase(4);
  CHECK(arr1 == DynamicArray({1, 5, 3, 4}));

  arr1.erase(0);
  CHECK(arr1 == DynamicArray({5, 3, 4}));

  arr1.insert(0, 8);
  CHECK(arr1 == DynamicArray({8, 5, 3, 4}));

  arr1.insert(4, 9);
  CHECK(arr1 == DynamicArray({8, 5, 3, 4, 9}));

  arr1.insert(4, 2);
  CHECK(arr1 == DynamicArray({8, 5, 3, 4, 2, 9}));
}

TEST_CASE("Testing DynamicArray methods #5")
{
  DynamicArray arr({1, 2, 3, 4, 5, 4, 3, 2, 1});
  std::ostringstream oss;
  for (auto a : arr)
    oss << a << " ";
  CHECK(oss.str() == "1 2 3 4 5 4 3 2 1 ");

  oss.str("");
  arr.at(0) = 5;
  arr[arr.size() - 1] = 5;
  for (auto a : arr)
    oss << a << " ";
  CHECK(oss.str() == "5 2 3 4 5 4 3 2 5 ");
}
