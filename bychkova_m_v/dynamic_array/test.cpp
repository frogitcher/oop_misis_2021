#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("Constructor tests + accessing elements + empty + clear") {
	DynamicArray dempty;
	CHECK(dempty.Size() == 0);
	CHECK(dempty.Capacity() == 0);
	CHECK(dempty.empty());

	DynamicArray dlist({1, 2, 3, 4, 5});
	CHECK(dlist.Size() == 5);
	CHECK(dlist.Capacity() == 5);
	for (int i=0; i<dlist.Size(); i++) {
		CHECK(dlist[i] == i+1);
	}
	CHECK(*(dlist.begin()) == 1);

	DynamicArray da(5);
	CHECK(da.Size() == 5);
	CHECK(da.Capacity() >= da.Size());
	for (int i=0; i<da.Size(); i++) {
		CHECK(&da[i] == da.begin()+i);
		CHECK(da[i] == 0);
		CHECK(&da.at(i) == da.begin()+i);
		CHECK(da.at(i) == 0);
	}
	CHECK (da.empty() == false);
	CHECK_THROWS_WITH(da.at(5), "Index is out of range!");
	da.clear();
	CHECK (da.Size() == 0);
	CHECK (da.empty());

	DynamicArray da1(5, 1);
	CHECK(da1.Size() == 5);
	CHECK(da1.Capacity() >= da1.Size());
	for (int i=0; i<da1.Size(); i++) {
		CHECK(da1[i] == 1);
	}

	DynamicArray dcopy(da1);
	CHECK(dcopy.Size() == da1.Size());
	CHECK(dcopy.Capacity() == da1.Capacity());
	for (int i=0; i<dcopy.Size(); i++) {
		CHECK(da1[i] == dcopy[i]);
	}

	CHECK_THROWS_WITH(DynamicArray(-5), "Size must not be negative!");

}

TEST_CASE("Boolean check + operator= + swap") {
	DynamicArray d1(5, 2);
	DynamicArray d2({2, 2, 2, 2, 2});
	DynamicArray d3(4, 2);
	DynamicArray d4(5, 3);

	CHECK(d1 == d2);
	CHECK(d1 != d3);
	CHECK(d1 != d4);
	d4 = d2;
	CHECK(d1 == d4);
	d3.swap(d2);
	CHECK(d1 == d3);
	CHECK(d1 != d2);
}

TEST_CASE("erase + pop_back"){
	DynamicArray da({1, 2, 3, 4, 5, 6, 7});
	DynamicArray dacopy(da);
	da.erase(3);
	CHECK(da.Size() == 6);
	for (int i=0; i<3; i++) {
		CHECK(da[i] == dacopy[i]);
	}
	for (int i=3; i<da.Size(); i++) {
		CHECK(da[i] == dacopy[i+1]);
	}
	CHECK_THROWS_WITH(da.erase(7), "You're trying to access an element which is out of range!");
	CHECK_THROWS_WITH(da.erase(-7), "You're trying to access an element which is out of range!");

	dacopy = da;
	da.pop_back();
	CHECK(da.Size() == 5);
	for (int i=0; i<da.Size(); i++) {
		CHECK(da[i] == dacopy[i]);
	}

	DynamicArray dempty;
	CHECK_THROWS_WITH(dempty.pop_back(), "You're trying to access an element which is out of range!");
}

TEST_CASE("insert + push_back"){
	DynamicArray da({1, 2, 3, 4, 5});
	DynamicArray dacopy(da);

	da.push_back(6);
	CHECK(da.Size() == 6);
	CHECK(da[5] == 6);
	for (int i=0; i<5; i++) {
		CHECK(da[i] == dacopy[i]);
	}

	dacopy = da;
	da.insert(2, 10);
	CHECK(da.Size() == 7);
	CHECK(da[2] == 10);
	for (int i=0; i<2; i++) {
		CHECK(da[i] == dacopy[i]);
	}
	for (int i=3; i<da.Size(); i++) {
		CHECK(da[i] == dacopy[i-1]);
	}

	CHECK_THROWS_WITH(da.insert(-3, 4), "Index is out of range!");
}

TEST_CASE("resize"){
	DynamicArray da(5, 2);
	da.resize(10);
	CHECK(da.Size()==10);
	for (int i=0; i<5; i++) {
		CHECK(da[i] == 2);
	}
	for (int i=5; i<da.Size(); i++) {
		CHECK(da[i] == 0);
	}

	da.resize(3);
	CHECK(da.Size() == 3);
	for (int i=0; i<da.Size(); i++) {
		CHECK(da[i] == 2);
	}

	da.resize(0);
	CHECK(da.empty());

	CHECK_THROWS_WITH(da.resize(-5), "Size must not be negative!");
}

TEST_CASE("assign"){
	DynamicArray da({1, 2, 3, 4, 5, 6, 7});
	da.assign(15, 7);
	CHECK(da.Size() == 15);
	for (int i=0; i<da.Size(); i++) {
		CHECK(da[i] == 7);
	}
	CHECK_THROWS_WITH(da.assign(-5, 5), "Size must not be negative!");
}
