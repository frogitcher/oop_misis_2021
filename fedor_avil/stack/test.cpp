#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.cpp"
#include "iostream"
Stack<int> st;
Stack<int> st1=st;
Stack<int> st3=st;
Stack<int> st2(st1);
Stack<int> st_init{ 1,2,3,4 };
TEST_CASE("Testing Contructors") {
	st.Push(1);
	st1 = st;
	st3 = st;
	st2 = Stack<int>(st1);
	CHECK(st1 == st);
	CHECK(st3 == st);
	CHECK(st2 == st);
	CHECK(st_init.Get() == 4);
}
TEST_CASE("Testing Editors") {
	st.Push(1);
	CHECK(st.Get() == 1);
	st.Push(2);
	st1 = st;
	st3 = st;
	st.Pop();
	CHECK(st.Get() == 1);	
	st.Push(3);
	st.merge(st1);
	CHECK(st.Get()==2);	
	st2 = st1;
	st2.Push(4);
	st2.swap(st1);
	CHECK(st2.Get()==2);
}

TEST_CASE("Testing Operators") {
	CHECK(st2 == st3);
	CHECK(st2 != st);
}
TEST_CASE("Testing Exceptions") {
	Stack<int> st2;
	CHECK_THROWS_WITH(st2.Pop(), "Stack is empty");
}