#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Stack.h"
#include <iostream>
#include "Stack.h"
#include <initializer_list>

TEST_CASE_TEMPLATE("Test template initialization", type, int, long, long long, char, unsigned int) {
	Stack<type> st;
	CHECK(st.Size() == 0);
	CHECK(st.Empty() == true);
	Stack<type> st1{type('M'), 2, 3, 4, 5};
	CHECK(st1.get_front() == 5);
	CHECK(st1.get_back() == 'M');
	Stack<type> st2 = st1;
	CHECK(st2 == st1);
	CHECK(st2.get_back() == st1.get_back());
	CHECK(st2.Size() == st1.Size());
	Stack<type> st3(st1);
	CHECK(st3.get_back() == 'M');
}

TEST_CASE("Test logic operation") {
	Stack<int> st{ 1,2,3,4,5 };
	Stack<int> st1 = st;
	CHECK(st == st1);
	st1.pop();
	CHECK(st != st1);
}


TEST_CASE("Test push, pop, empty function") {
	Stack<int> st{ 1,2,3,4,5 };
	CHECK(st.Size() == 5);
	st.pop();
	CHECK(st.Size() == 4);
	st.push(6);
	CHECK(st.Size() == 5);
	CHECK(st.get_front() == 6);
	CHECK(st.Empty() == false);
}

TEST_CASE("Test merge") {
	Stack<int> st{ 5,4,3,2,1 };
	Stack<int> st1{ 8,7,6 };
	st.merge(st1);
	CHECK(st.get_front() == 1);
	CHECK(st.get_back() == 8);
	CHECK(st.Size() == 8);
}

TEST_CASE("Test swap") {
	Stack<int> st{ 1,2,3,4,5 };
	Stack<int> st1{ 6,3,11 };
	st.swap(st1);
	CHECK(st.Size() == 3);
	CHECK(st1.Size() == 5);
	CHECK(st.get_front() == 11);
	CHECK(st1.get_front() == 5);
}

TEST_CASE("Test clear") {
	Stack<int> st{ 1,2,3,4,5 };
	st.clear();
	CHECK(st.Size() == 0);
}
