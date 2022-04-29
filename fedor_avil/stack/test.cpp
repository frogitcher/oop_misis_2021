#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"
#include "iostream"

TEST_CASE("Testing Contructors") {
	Stack<int> st;
	Stack<int> st1 = st;
	Stack<int> st3 = st;
	Stack<int> st2(st1);
	Stack<int> st_init{ 1,2,3,4 };
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
	Stack<int> st;
	Stack<int> st1 = st;
	Stack<int> st2(st1);
	Stack<int> st_init{ 1,2,3,4 };
	st.Push(1);
	CHECK(st.Get() == 1);
	st.Push(2);
	st1 = st;
	st.Pop();
	CHECK(st.Get() == 1);	
	st.Push(3);
	st.merge(st1);
	CHECK(st.Get()==1);	
	st2 = st1;
	st2.Push(4);
	st1.Push(1);
	st2.swap(st1);
	CHECK(st2.Get()==1);
}

TEST_CASE("Testing Operators") {
	Stack<int> st;
	Stack<int> st1 = st;
	Stack<int> st2(st1);
	CHECK(st2 == st1);
	st1.Push(2);
	CHECK(st2 != st1);
}
TEST_CASE("Testing Exceptions") {
	Stack<int> st2;
	CHECK_THROWS_WITH(st2.Pop(), "Stack is empty");
	CHECK_THROWS_WITH(st2.Get(), "Stack is empty");
}