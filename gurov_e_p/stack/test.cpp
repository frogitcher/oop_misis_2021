#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Testing constructors and ==", T, int, double, float, long long, unsigned long long) {
	Stack<T> a;
	CHECK(a.Size() == 0);
	CHECK(Get_Head(a) == nullptr);
	CHECK(Get_Tail(a) == nullptr);

	Stack<T> b(a);
	CHECK(b.Size() == a.Size());
	CHECK(b == a);

	Stack<T> c(std::initializer_list<T>{ (T)6.4f, (T)-87.001, 3, 0 });
	CHECK(c != b);
	CHECK_FALSE(c == a);
}

TEST_CASE_TEMPLATE("Testing stack methods", T, int, double, float, long long, unsigned long long) {
	Stack<T> a(std::initializer_list<T>{ 1, 2, 3, (T)4.5 });
	Stack<T> a_copy(a);
	a.Push((T)-9.3);
	CHECK(a != a_copy);
	CHECK_FALSE(a == a_copy);
	CHECK(a.Size() == a_copy.Size() + 1);
	CHECK(a.Get() == (T)-9.3);
	CHECK(Get_Head(a)->value == (T)-9.3);
	CHECK(Get_Head(a)->next->value == Get_Head(a_copy)->value);

	Stack<T> b(std::initializer_list<T>{ (T)-5, 2, (T)133.9 });
	Stack<T> b_copy(b);
	b.Pop();
	CHECK(b != b_copy);
	CHECK_FALSE(b == b_copy);
	CHECK(b.Size() == b_copy.Size() - 1);
	CHECK(b.Get() == 2);
	CHECK(Get_Head(b)->value == 2);
	CHECK(Get_Head(b)->value == Get_Head(b_copy)->next->value);

	a = a_copy;
	b = b_copy;
	CHECK(a == a_copy);
	CHECK(b == b_copy);

	a.Swap(b);
	CHECK(a == b_copy);
	CHECK(b == a_copy);

	// a = {(T)-5, 2, (T)133.9}, b = {1, 2, 3, (T)4.5}
	a.Merge(b);
	CHECK(a == Stack<T>(std::initializer_list<T>{ 1, 2, 3, (T)4.5, (T)-5, 2, (T)133.9 }));
	CHECK(a.Size() == 7);
	CHECK(a.Get() == (T)133.9);
	CHECK(Get_Head(a)->value == Get_Head(b_copy)->value);
	CHECK(Get_Tail(a)->value == Get_Tail(a_copy)->value); // tail a совпадает с tail a_copy = {1, 2, 3, (T)4.5}

	Stack<T> c(std::initializer_list<T>{ 1, 2, 3, 4 });
	Stack<T> c_move(std::move(c));
	CHECK(c.Size() == 0);
	CHECK(c_move.Size() == 4);
	CHECK(Get_Head(c) == nullptr);
	CHECK(Get_Tail(c) == nullptr);
	CHECK(c_move.Get() == 4);

	c_move.Clear();
	CHECK(c_move.Size() == 0);
	CHECK(c_move == Stack<T>());
	CHECK_THROWS_WITH(c_move.Pop(), "Stack is empty!");
	CHECK_THROWS_WITH(c_move.Get(), "Stack is empty!");

	Stack<T> d(std::initializer_list<T>{ 1, 2, 3, 4 });
	Stack<T> d_move = std::move(d);
	CHECK(d.Size() == 0);
	CHECK(d_move.Size() == 4);
	CHECK(Get_Head(d) == nullptr);
	CHECK(Get_Tail(d) == nullptr);
	CHECK(d_move.Get() == 4);
}
