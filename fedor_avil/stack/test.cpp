#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.cpp"
#include "iostream"
Stack<int> st;
TEST_CASE("Testing Contructors") {
}
TEST_CASE("Testing Editors") {
	st.Push(1);
	CHECK(st.Get() == 1);
	st.Push(2);
	Stack<int> st1(st);
	st.Pop();
	CHECK(st.Get() == 1);
	st.Push(3);
	st.merge(st1);
	CHECK(st.Get()==2);	
}

/*TEST_CASE("Testing Operators") {
}
*/
TEST_CASE("Testing Exceptions") {
	Stack<int> st2;
	CHECK_THROWS_WITH(st2.Pop(), "Stack is empty");
}