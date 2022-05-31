#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "stack.h"
#include "doctest.h"

TEST_CASE("Constructors and bool operators"){
	Stack<int> st1;
	CHECK(st1.Size() == 0);
	CHECK(st1.Empty());

	Stack<int> st2{1, 2, 3};
	CHECK(st2.Size() == 3);

	Stack<int> st3(st2);
	CHECK(st3.Size() == 3);
	CHECK(st3.Get() == 3);
	CHECK(st2 == st3);
	CHECK(st2 == st2);
	CHECK(st3 != st1);
	CHECK(not(st3.Empty()));
}

TEST_CASE("other functions") {
	Stack<int> st1{1, 2, 3, 4, 5};
	st1.Push(6);
	CHECK(st1.Size() == 6);
	CHECK(st1.Get() == 6);

	Stack<int> st2;
	st2 = st1;

	st1.Pop();
	CHECK(st1.Size() == 5);
	CHECK(st1.Get() == 5);
	CHECK(st2.Get() == 6);

	st1.Clear();
	CHECK(st1.Size() == 0);
	CHECK_THROWS_WITH(st1.Pop(), "Stack is empty!");
	CHECK_THROWS_WITH(st1.Get(), "Stack is empty!");

	st1.Swap(st2);
	CHECK(st1.Get() == 6);

	Stack<int> st3 {7, 8};
	st1.Merge(st3);
	CHECK(st3.Size() == 0);
	CHECK(st1.Size() == 8);
}
