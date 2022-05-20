#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic.h"

TEST_CASE("Testing dynamic array constructors and stuff") {
    DynamicArray d;
    CHECK(d.Size() == 0);
    CHECK(d.Capacity() == 0);
	CHECK(d.begin() == d.GetData());
    CHECK(d.Empty());

    DynamicArray a(10, 4);
    CHECK(a.Size() == 10);
    CHECK((a.Size() == 0) == false);
    CHECK(a.Capacity() >= a.Size());
	CHECK(a.at(3) == 4);
	CHECK_FALSE(a.at(1) == 10);

	DynamicArray c(a);
	CHECK(c == a);
	CHECK(c.Size() == a.Size());
	CHECK(c.Capacity() == a.Capacity());
	for (int64_t i = 0; i < a.Size(); ++i) {
		CHECK(&(c[i]) == (c.begin() + i));
		CHECK(c[i] == a[i]);
	}

	DynamicArray list{ 0, 1, 2, 3, 4, 5, 6, 7, 8 ,9 };
	CHECK(list.Size() == 10);
	CHECK_FALSE(list == a);
	CHECK(a != list);
	CHECK(list.Capacity() >= list.Size());
	for (int i = 0; i < list.Size(); i++) {
		CHECK(list[i] == i );
	}
	
	CHECK_THROWS_WITH(DynamicArray err(-4), "bad array new length");
	list.clear();
	CHECK(list.Size() == 0);
	CHECK(list.Empty());
	CHECK_THROWS_WITH(list.at(1), "Index is Out of range");

	CHECK_FALSE(c.Empty());
	DynamicArray copy(c);
	CHECK(copy.Size() ==c.Size());
	CHECK(copy.Capacity() == c.Capacity());
	for (int i = 0; i < copy.Size(); i++) {
		CHECK(copy[i] == c[i]);
	}


	DynamicArray x(10, 3);

	for (int64_t i = 0; i < x.Size(); i++) {

		CHECK(&(x[i]) == (x.GetData() + i));
		CHECK(x[i] == 3);
		CHECK(&(x.at(i)) == &(x[i]));
		CHECK(&(x.at(i)) == (x.GetData() + i));
	}

}

TEST_CASE("testing push_back and pop_back") {
	DynamicArray first{ 0, 1, 2, 3, 4 };
	DynamicArray second(first);
	DynamicArray empty;

	first.pop_back();
	CHECK(first.Size() == 4);
	for (int i = 0; i < first.Size(); i++) {
		CHECK(first[i] == second[i]);
	}

	CHECK_THROWS_WITH(empty.pop_back(), "Out of range");
	second = first;
	first.push_back(5);
	CHECK(first.Size() == 5);
	CHECK(first[4] == 5);
	for (int i = 0; i < second.Size(); i++) {
		CHECK(first[i] == second[i]);
	}
	CHECK(!(first == second));
	CHECK_FALSE(first == second);
}

TEST_CASE(" testing erase") {
	DynamicArray first{ 3, 4, 3, 12, 7, 5, 89, 7 };
	DynamicArray second(first);
	DynamicArray empty;
	first.erase(5);
	CHECK(first.Size() == 7);
	for (int i = 0; i < 5; i++) {
		CHECK(first[i] == second[i]);
	}
	for (int i = 5; i < first.Size(); i++) {
		CHECK(first[i] == second[i+1]);
	}
	for (int i = 0; i < first.Size(); i++) {
		CHECK(first[i] != 5);
	}
	CHECK_THROWS_WITH(empty.erase(1), "Out of range");
	CHECK_THROWS_WITH(first.erase(-1), "Out of range");
	CHECK_THROWS_WITH(empty.erase(11), "Out of range");
}

TEST_CASE("testing insert") {
	DynamicArray first{ 12, 17, 80, 91, 39};
	DynamicArray second(first);

	CHECK(first.Size() == 5);
	first.insert(0, 15);
	CHECK(first.Size() == 6);
	CHECK(first[0] == 15);

	for (int i = 1; i < first.Size(); i++) {
		CHECK(first[i] == second[i - 1]);
	}

	first.insert(3, 7);
	CHECK(first.Size() == 7);
	CHECK(first[3] == 7);
	
	for (int i = 1; i < 3; i++) {
		CHECK(first[i] == second[i-1]);
	}
	for (int i = 3+1; i < first.Size(); i++) {
		CHECK(first[i] == second[i - 2]);
	}
	first.erase(3);
	first.erase(0);
	CHECK(first == second);

	CHECK_THROWS_WITH(first.insert(-5, 12), "Out of range");
	CHECK_THROWS_WITH(first.insert(12, 9), "Out of range");
}

TEST_CASE("Resize Testing") {

	DynamicArray first(6, 1);
	DynamicArray second(first);
	DynamicArray empty;
	int64_t s = first.Size();

	first.resize(10);
	CHECK(first.Size() == 10);
	CHECK(s < 10);
	for (int64_t i = 0; i < s; i++) {
		CHECK(first[i] == second[i]);
	}
	for (int64_t i = s; i < first.Size(); i++) {
		CHECK(first[i] == 0);
	}
	DynamicArray third{ 12, 23, 4, 23, 5, 12 };
	second = third;
	CHECK(second.Size() == 6);
	third.resize(10);
	for (int64_t i = 0; i < second.Size(); i++) {
		CHECK(third[i] == second[i]);
	}
	for (int64_t i = second.Size(); i < third.Size(); i++) {
		CHECK(first[i] == 0);
	}
	third.resize(0);
	CHECK(third == empty);


	CHECK_THROWS_WITH(third.resize(-3), "The size is negative");
}

TEST_CASE("testing assign") {
	DynamicArray first{ 1, 15 , 18, 0, 22 };
	DynamicArray empty;
	first.assign(3, 4);
	CHECK(first.Size() == 3);
	for (int i = 0; i < first.Size(); i++) {
		CHECK(first[i] == 4);
	}
	first.assign(0, 1);
	CHECK(first == empty);
	CHECK_THROWS_WITH(first.assign(-6, 13), "The size can't be below 0");
}


TEST_CASE("testing begin & end") {
	DynamicArray first{ 110,21, 15, 16, 1, 7 };

	CHECK(*(first.begin()) == 110);
	CHECK(*(first.end() -1) == 7);
}

TEST_CASE("testing swap") {
	DynamicArray first{ 17, 16, 1, 23, 4 };
	DynamicArray second(first);
	DynamicArray third{ 115, 3, 23, 9, 0 };
	DynamicArray fourth(third);

	first.swap(third);
	for (int i = 0; i < 4; i++) {
		CHECK(first[i] == fourth[i]);
		CHECK_FALSE(first[i] == second[i]);
		CHECK(third[i] == second[i]);
		CHECK_FALSE(third[i] == fourth[i]);
	}
}

