#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Stack constructor default", T, int, float, double, long long) {
	Stack<T> first;
	CHECK(first.Size() == 0);
	CHECK(first.empty());
	for (T i = 0; i < 10; i++) {
		first.push(i);
		CHECK(first.get() == i);
		CHECK(first.Size() == (int)(i + 1));
	}
	for (T i = first.Size(); i <= 0; i--) {
		CHECK(first.Size() == i);
		CHECK(first.get() == i);
		first.pop();
	}
}

TEST_CASE_TEMPLATE("Stack other constructors & operator= & relational operators", T, int, float, double, long long) {
	Stack<T> first{ (T)6, (T)5, (T)4, (T)3, (T)2, (T)1 };
	Stack<T> tosmsize{ (T)6, (T)5, (T)4, (T)3, (T)2, (T)1, (T)19, (T)24, (T)43};
	Stack<T> second(first);
	tosmsize = first;
	CHECK_FALSE(first.empty());
	CHECK(first == second);
	Stack<T> third{ (T)8, (T)1 };
	CHECK_FALSE(first == third);
	Stack<T> temp(first);
	Stack<T> temp2(first);
	Stack<T> forth(std::move(temp));
	Stack<T> fifth{ (T)8, (T)1 };
	third = first;
	CHECK_FALSE(first != third);
	fifth = std::move(temp2);
	CHECK(first.Size() == 6);
	CHECK(second.Size() == 6);
	CHECK(third.Size() == 6);
	CHECK(forth.Size() == 6);
	CHECK(fifth.Size() == 6);
	CHECK(tosmsize.Size() == 6);
	for (T i = 1; i < 7; i++) {
		CHECK(first.get() == i);
		CHECK(second.get() == i);
		CHECK(third.get() == i);
		CHECK(forth.get() == i);
		CHECK(fifth.get() == i);
		CHECK(tosmsize.get() == i);
		first.pop();
		second.pop();
		third.pop();
		forth.pop();
		fifth.pop();
		tosmsize.pop();
	}
}

TEST_CASE_TEMPLATE("Stack swap & merge", T, int, float, double, long long) {
	Stack<T> first{ (T)5, (T)4, (T)3, (T)2, (T)1 };
	Stack<T> second{ (T)10, (T)9, (T)8, (T)7, (T)6 };
	Stack<T> third{ (T)8, (T)1 };
	Stack<T> forth(first);
	first.merge(second);
	CHECK(first.Size() == 10);
	CHECK(second.Size() == 0);
	for (T i = 1; i < 10; i++) {
		CHECK(first.get() == i);
		first.pop();
	}
	forth.swap(third);
	CHECK(forth.Size() == 2);
	CHECK(third.Size() == 5);
	for (T i = 1; i < 5; i++) {
		CHECK(third.get() == i);
		third.pop();
	}
	for (T i = 1; i < 8; i += 7) {
		CHECK(forth.get() == i);
		forth.pop();
	}
}