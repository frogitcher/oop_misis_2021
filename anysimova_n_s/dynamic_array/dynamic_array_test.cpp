#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dynamic_array.h"

TEST_CASE("DynamicArray constructors & member access operators") {
	DynamicArray empty;
	CHECK(empty.Size() == 0);
	CHECK(empty.Capacity() == 0);
	CHECK(empty.begin() == empty.end());
	CHECK(empty.empty());

	DynamicArray DA(5, 6);
	CHECK(DA.Size() == 5);
	CHECK(DA.Capacity() >= DA.Size());
	for (int i = 0; i < DA.Size(); i++) {
		CHECK(&(DA[i]) == (DA.begin() + i));
		CHECK(DA[i] == 6);
		CHECK(&(DA.at(i)) == (DA.begin() + i));
		CHECK(DA.at(i) == 6);
	}

	DynamicArray oflist{ 1, 2, 3, 4, 5, 6, 7, 8 ,9, 10 };
	CHECK(oflist.Size() == 10);
	CHECK(oflist.Capacity() >= oflist.Size());
	for (int i = 0; i < oflist.Size(); i++){
		CHECK(oflist [i] == i + 1);
	}

	DynamicArray copy(DA);
	CHECK(copy.Size() == DA.Size());
	CHECK(copy.Capacity() == DA.Capacity());
	for (int i = 0; i < copy.Size(); i++) {
		CHECK(copy[i] == DA[i]);
	}

	CHECK_THROWS_WITH(DA.at(DA.Size()), "index out of range");
	CHECK_THROWS_WITH(DynamicArray st(-5), "The size must be positive number");
}

TEST_CASE("push_back") {
	DynamicArray first{ 0, 9, 8, 7, 6 };
	DynamicArray second(first);

	first.push_back(12);
	CHECK(first.Size() == 6);
	CHECK(first[5] == 12);
	for (int i = 0; i < first.Size() - 1; i++) {
		CHECK(first[i] == second[i]);
	}
}

TEST_CASE("pop_back") {
	DynamicArray first{ 0, 9, 8, 7, 6 };
	DynamicArray second(first);
	DynamicArray empty;

	first.pop_back();
	CHECK(first.Size() == 4);
	for (int i = 0; i < first.Size(); i++) {
		CHECK(first[i] == second[i]);
	}

	CHECK_THROWS_WITH(empty.pop_back(), "The size is equal to zero");
}

TEST_CASE("erase") {
	DynamicArray first{ 0, 9, 8, 7, 6, 13, 42, 4, 2, 1 };
	DynamicArray second(first);
	DynamicArray third(first);

	first.erase(4);
	CHECK(first.Size() == 9);
	for (int i = 0; i < 3; i++) {
		CHECK(first[i] == second[i]);
	}
	for (int i = 3; i < first.Size(); i++) {
		CHECK(first[i] == second[i + 1]);
	}
	for (int i = 0; i < first.Size(); i++) {
		CHECK(first[i] != 7);
	}

	third.erase(third.Size());
	CHECK(first.Size() == 9);
	for (int i = 0; i < third.Size(); i++) {
		CHECK(third[i] == second[i]);
	}
	
}

TEST_CASE("clear & empty") {
	DynamicArray first{ 0, 9, 8, 7, 6, 13, 42, 4, 2, 1 };
	
	first.clear();
	CHECK(first.Size() == 0);
	CHECK(first.empty());
}

TEST_CASE("resize") {
	DynamicArray first{ 13, 42, 4, 2, 1 };
	DynamicArray second(first);
	DynamicArray third{ 13, 42, 4, 2};
	third.push_back(1);

	first.resize(8);
	CHECK(first.Size() == 8);
	for (int i = 0; i < second.Size(); i++) {
		CHECK(first[i] == second[i]);
	}
	for (int i = second.Size(); i < first.Size(); i++) {
		CHECK(first[i] == 0);
	}

	third.resize(8);
	CHECK(third.Size() == 8);
	for (int i = 0; i < second.Size(); i++) {
		CHECK(third[i] == second[i]);
	}
	for (int i = second.Size(); i < third.Size(); i++) {
		CHECK(third[i] == 0);
	}

	third.resize(3);
	CHECK(third.Size() == 3);
	for (int i = 0; i < third.Size(); i++) {
		CHECK(third[i] == second[i]);
	}

	CHECK_THROWS_WITH(third.resize(0), "The size must be positive number");
	CHECK_THROWS_WITH(first.resize(-6), "The size must be positive number");
}

TEST_CASE("assign") {
	DynamicArray first{ 13, 42, 4, 2, 1 };

	first.assign(8, 5);
	CHECK(first.Size() == 8);
	for (int i = 0; i < first.Size(); i++) {
		CHECK(first[i] == 5);
	}

	first.assign(3, 11);
	CHECK(first.Size() == 3);
	for (int i = 0; i < first.Size(); i++) {
		CHECK(first[i] == 11);
	}

	CHECK_THROWS_WITH(first.assign(0, 4), "The size must be positive number");
	CHECK_THROWS_WITH(first.assign(-6, 13), "The size must be positive number");
}

TEST_CASE("insert") {
	DynamicArray first{ 13, 42, 4, 2, 1, 5, 87};
	DynamicArray second(first);
	DynamicArray third{ 13, 42, 4, 2, 1, 5};
	third.push_back(87);

	first.insert(1, 15);
	CHECK(first.Size() == 8);
	CHECK(first[0] == 15);
	for (int i = 1; i < first.Size(); i++) {
		CHECK(first[i] == second[i - 1]);
	}
	first.erase(1);

	first.insert(6, 18);
	CHECK(first.Size() == 8);
	CHECK(first[5] == 18);
	for (int i = 0; i < 5; i++) {
		CHECK(first[i] == second[i]);
	}
	for (int i = 6; i < first.Size(); i++) {
		CHECK(first[i] == second[i - 1]);
	}
	first.erase(6);

	first.insert(first.Size() + 1, 76);
	CHECK(first.Size() == 8);
	CHECK(first[7] == 76);
	for (int i = 0; i < first.Size() - 1; i++) {
		CHECK(first[i] == second[i]);
	}

	third.insert(6, 143);
	CHECK(third.Size() == 8);
	CHECK(third[5] == 143);
	for (int i = 0; i < 5; i++) {
		CHECK(third[i] == second[i]);
	}
	for (int i = 6; i < third.Size(); i++) {
		CHECK(third[i] == second[i - 1]);
	}
}

TEST_CASE("swap") {
	DynamicArray first{ 13, 42, 4, 2, 1 };
	DynamicArray second(first);
	DynamicArray third{ 12, 56, 8, 6, 3 };
	DynamicArray forth(third);

	first.swap(third);
	for (int i = 0; i < 5; i++) {
		CHECK(first[i] == forth[i]);
		CHECK(third[i] == second[i]);
	}
}

TEST_CASE("begin & end") {
	DynamicArray first{ 13, 42, 4, 2, 1 };

	CHECK(*(first.begin()) == 13);
	CHECK(*(first.end()) == 1);
}

TEST_CASE("operator=") {
	DynamicArray first{ 13, 42, 4, 2, 1, 5, 87 };
	DynamicArray second(10, 5);
	DynamicArray third(3, 2);

	first = second;
	CHECK(first.Size() == second.Size());
	for (int i = 0; i < first.Size(); i++) {
		CHECK(first[i] == 5);
		CHECK(second[i] == 5);
	}

	first = third;
	CHECK(first.Size() == third.Size());
	for (int i = 0; i < first.Size(); i++) {
		CHECK(first[i] == 2);
		CHECK(third[i] == 2);
	}
}

TEST_CASE("operator== & operator!=") {
	DynamicArray first{ 13, 42, 4, 2, 1, 5, 87 };
	DynamicArray second(7, 5);
	DynamicArray third(7, 5);

	CHECK(!(first == second));
	CHECK(!(first == third));
	CHECK(second == third);
	CHECK(first != second);
	CHECK(first != third);
	CHECK(!(second != third));
}