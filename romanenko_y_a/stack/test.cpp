#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include "doctest.h"
#include "stack.h"


TEST_CASE("TEST STACK") {

	std::initializer_list<int> data = { 1, 2, 3, 4, 5 };

	Stack<int> st;
	CHECK(st.Size() == 0);
	CHECK(st.Empty());

	Stack<int> st1(data);
	Stack<int> st2;
	for (int i : data) {
		st2.Push(i);
	}
	CHECK(st1 == st2);
	CHECK(st1.Size() == data.size());
	
	Stack<int> st3(st1);
	CHECK(st1 == st3);
	st3 = st;
	CHECK(st3 == st);

	Stack<int> st4 = Stack<int>{ 1, 2, 3, 4, 5 };
	CHECK(st4.Size() == 5);

	st1.Push(4);
	CHECK(st1.Get() == 4);
	CHECK(st1.Size() == 6);
	st1.Pop();
	CHECK(st1.Get() == 5);
	CHECK(st1.Size() == 5);

	st1.Merge(st2);
	CHECK(st1 == Stack<int>{ 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 });
	CHECK(st1.Size()==10);
	CHECK(st2.Size()==0);

	st4.Swap(st1);
	CHECK(st4.Size()==10);
	CHECK(st1.Size()==5);
	CHECK(st1 == Stack<int>{ 1, 2, 3, 4, 5 });

	st1.Clear();
	CHECK(st1.Size() == 0);

	Stack<int> st5;
	CHECK_THROWS_WITH(st.Pop(), "stack is empty");
	CHECK_THROWS_WITH(st.Get(), "stack is empty");
}