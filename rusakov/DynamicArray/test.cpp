#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "DynamicArray.h"

TEST_CASE("Testing init dynamic array") {
	DynamicArray arr;
	CHECK(arr.Size() == 0);
	CHECK(arr.Capacity() == 0);
	CHECK(arr.Empty() == true);

	DynamicArray arr1(5,1);
	CHECK(arr1.Size() == 5);
	CHECK(arr1.Capacity() == 10);
	CHECK(arr1.Empty() == false);
	CHECK(arr1[4] == 1);

	DynamicArray a{ 1,2,3,4,5 };
	DynamicArray b = a;
	CHECK(a.Size() == b.Size());
	CHECK(a[2] == b[2]);
	CHECK(a == b);
}

TEST_CASE("Testing void Empty") {
	DynamicArray a;
	CHECK(a.Empty() == true);
	DynamicArray b{ 1,2,3 };
	CHECK(b.Empty() == false);
}

TEST_CASE("Testing void push_back") {
	DynamicArray a; 
	a.push_back(1);
	CHECK(a.Size() == 1);
	CHECK(a[0] == 1);
	a.push_back(2);
	CHECK(a.Size() == 2);
	CHECK(a[0] == 1);
	CHECK(a[1] == 2);
	a.push_back(3);
	CHECK(a.Size() == 3);
	CHECK(a[0] == 1);
	CHECK(a[1] == 2);
	CHECK(a[2] == 3);

	DynamicArray b{ 1,2,3,4,5 };
	CHECK(b.Size() == 5);
	b.push_back(6);
	CHECK(b.Size() == 6);
	CHECK(b[5] == 6);
}

TEST_CASE("Testing Resize void") {
	DynamicArray a{ 1,2,3,4,5 };
	CHECK(a.Size() == 5);
	a.resize(7);
	CHECK(a.Size() == 7);
	CHECK(a[5] == 0);
	CHECK(a[4] == 5);
	a.resize(3);
	CHECK(a.Size() == 3);
	CHECK(a[2] == 3);

	DynamicArray c{ 1,2,3 };
	c.resize(3);
	CHECK(c.Size() == 3);
	CHECK(c[0] == 1);
	CHECK(c[1] == 2);
	CHECK(c[2] == 3);
}

TEST_CASE("Testing void at") {
	DynamicArray a{5, 6, 7, 8, 9};
	CHECK(a.at(0) == 5);
	CHECK_THROWS_WITH(a.at(5), "exception - Index more then size of array");
	CHECK_THROWS_WITH(a.at(-1), "exception - Index more then size of array");
}

TEST_CASE("Testing operator[]") {
	DynamicArray a{ 1,2,3,4,5 };
	CHECK(a[0] == 1);
	CHECK(a[1] == 2);
	CHECK(a[2] == 3);
	CHECK(a[3] == 4);
	CHECK(a[4] == 5);
	CHECK_THROWS_WITH(a[5], "exception - Index more then size of array");
	CHECK_THROWS_WITH(a[-1], "exception - Index more then size of array");
}

TEST_CASE("Testing void pop_back") {
	DynamicArray a;
	CHECK_THROWS_WITH(a.pop_back(), "Size equal zero");
	a.push_back(10);
	CHECK(a.Size() == 1);
	CHECK(a[0] == 10);
	a.pop_back();
	CHECK(a.Size() == 0);

	DynamicArray b{ 1,2,3,4,5 };
	b.pop_back();
	CHECK(b.Size() == 4);
	CHECK(b[3] == 4);
}

TEST_CASE("Testing void clear") {
	DynamicArray a{ 5, 4, 3, 19, 20 };
	CHECK(a.Size() == 5);
	a.clear();
	CHECK(a.Size() == 0);

	DynamicArray b;
	b.clear();
	CHECK(b.Size() == 0);
}

TEST_CASE("Testing void erase") {
	DynamicArray a{ 1,2,3,4,5 };
	CHECK(a[4] == 5);
	a.erase(4);
	DynamicArray b{ 1,2,3,4 };
	CHECK(a == b);
	CHECK_THROWS_WITH(a.erase(6), "exception - index more then size");
	a.erase(2);
	DynamicArray c{ 1,2,4 };
	CHECK(c == a);
	CHECK(a.Size() == 3);
}

TEST_CASE("Testing void begin") {
	DynamicArray a{ 1,2,3,4 };
	CHECK(*a.begin() == 1);
	CHECK(*a.end() == 4);
	
	DynamicArray b;
	CHECK(b.begin() == nullptr);
	CHECK(b.end() == nullptr);
}

TEST_CASE("Testing void swap") {
	DynamicArray a{ 1,2,3,4,5 };
	DynamicArray b{ 6,9,4 };
	a.swap(b);
	CHECK(a.Size() == 3);
	CHECK(b.Size() == 5);
	CHECK(a[2] == 4);
	CHECK(b[4] == 5);

	DynamicArray empty;
	a.swap(empty);
	CHECK(a.Size() == 0);
	CHECK(empty.Size() == 3);
}

TEST_CASE("Testing void assign") {
	DynamicArray a;
	a.assign(5, 1);
	CHECK(a.Size() == 5);
	CHECK(a[0] == 1);
	CHECK(a[4] == 1);

	DynamicArray b{ 1,2,3,4,5 };
	b.assign(3, 1);
	CHECK(b.Size() == 3);
	CHECK(b[0] == 1);
}

TEST_CASE("testing bool operator") {
	DynamicArray a{ 1,2,3,4,5 };
	DynamicArray b{ 1,2,3,4,5 };
	CHECK(a == b);
	a.pop_back();
	CHECK(a != b);
}

TEST_CASE("Testing operator =") {
	DynamicArray a{ 1,2,3,4,5 };
	DynamicArray b = a;
	CHECK(b.Size() == a.Size());
}