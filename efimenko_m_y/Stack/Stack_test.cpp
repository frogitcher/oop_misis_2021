#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Testing constuctors", T, int, double, float, long long, unsigned long long) {
	Stack<T> st;
	CHECK(st.Size() == 0);
	CHECK(GetHead(st) == nullptr);
	CHECK(GetTail(st) == nullptr);

	Stack<T> sta(st);
	CHECK(sta == st);
	CHECK(sta.Size() == st.Size());
	CHECK_FALSE(sta != st);
	Stack<T> st1{ T('M'), 2, 3, 4, 5 };
	Stack<T> c(std::initializer_list<T>{ 115, (T)-12, 0, (T)7.2f, (T)87.64 });
	CHECK(c.Size() == 5);
	CHECK(c.Get() == (T)87.64);

	Stack<T> same;
	same = c;
	CHECK(same.Size() == c.Size());
	CHECK(same.Get() == c.Get());
	for (int i = 0; i < c.Size(); i++) {
		CHECK(GetTail(c)->value == GetTail(same)->value);
	}
}

TEST_CASE_TEMPLATE("Testing methods", T, int, double, float, long long, unsigned long long) {
	Stack<T> first(std::initializer_list<T>{12, (T)-3, (T)32.1, 0});
	Stack<T> second(first);
	first.Push((T)-98.12);
	CHECK(first.Size() != second.Size());
	CHECK(first != second);
	CHECK_FALSE(first == second);
	CHECK(first.Size() == second.Size() + 1);
	CHECK(first.Get() == (T)-98.12);
	CHECK(GetHead(first)->value == (T)-98.12);
	CHECK(GetTail(first)->value == 12);
	for (int i = 0; i < second.Size(); i++) {
		CHECK(GetTail(first)->value == GetTail(second)->value);
	}
	CHECK(GetHead(first)->value != GetHead(second)->value);

	first.Pop();
	CHECK(first.Size() == second.Size());
	CHECK(first.Get() == 0);
	first.Pop();
	CHECK(first.Get() == (T)32.1);
	for (int i = 0; i < first.Size(); i++) {
		CHECK(GetTail(first)->value == GetTail(second)->value);
	}
	CHECK_FALSE(GetHead(first)->value == GetHead(second)->value);
	second.Pop();
	CHECK(GetHead(first)->value == GetHead(second)->value);
	CHECK(second.Get() == (T)32.1);

	Stack<T> empty;
	CHECK(empty.Empty() == true);
	CHECK_THROWS_WITH(empty.Pop(), "Invalid size");

	CHECK(first.Size() == 3);
	CHECK_FALSE(empty.Size() == 1);
}

TEST_CASE_TEMPLATE("Testing swap", T, int, double, float, long long, unsigned long long) {
	Stack<T> first(std::initializer_list<T> {12, (T)63.1, (T)-11, (T)-23.5});
	Stack<T> second(std::initializer_list<T> {14, (T)-5, (T)12.3f, (T)-99.5});
	Stack<T> third(first);
	Stack<T> fourth(second);
	
	first.Swap(second);
	CHECK(first.Size() == second.Size());
	CHECK(first.Get() == (T)-99.5);
	CHECK(second.Get() == (T)-23.5);
	CHECK(GetTail(first)->value == 14);
	CHECK(GetTail(second)->value == 12);
	CHECK_FALSE(GetHead(first)->value == GetHead(second)->value);

	Stack<T> fifth(std::initializer_list<T> {12, (T)63.1, (T)-11, (T)-23.5, 113, (T)-205});
	first.Swap(fifth);
	CHECK(first.Size() == 6);
	CHECK(first.Get() == (T)-205);
}

TEST_CASE_TEMPLATE("Testing swap", T, int, double, float, long long, unsigned long long) {
	Stack<T> first(std::initializer_list<T> {12, (T)63.1, (T)-11, (T)-23.5});
	Stack<T> second(std::initializer_list<T> {14, (T)-5, (T)12.3f});
	Stack<T> third(first);

	first.Merge(second);
	CHECK(first.Size() == 7);
	CHECK(first.Get() == (T)12.3f);
	for (int i = 0; i < third.Size(); i++) {
		CHECK(GetTail(first)->value == GetTail(third)->value);
	}
	for (int i = third.Size() + 1; i < third.Size() + second.Size(); i++) {
		CHECK(GetTail(first)->value == GetTail(second)->value);
	}
}

