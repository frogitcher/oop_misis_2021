#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Stack.h"

TEST_CASE_TEMPLATE("Testing stack class", T, int, double, float, long long, unsigned long long) {
    Stack<T> a;
    CHECK(a.Empty());
    a.Push((T)-125.5);
    CHECK(a.Get() == (T)-125.5);
    a.Pop();
    CHECK(a.Empty());

    Stack<T> s (std::initializer_list<T>{1, 2, (T)3.5f, (T)4.7834, 5});
    CHECK(s.Get() == 5);
    CHECK(s.Size() == 5);

    Stack<T> b(std::initializer_list<T>{ (T)-5, 2, (T)133.9 });
	Stack<T> b_copy(b);
	b.Pop();
	CHECK(b != b_copy);
	CHECK_FALSE(b == b_copy);
	CHECK(b.Size() == b_copy.Size() - 1);
	CHECK(b.Get() == 2);
	CHECK(Get_Head(b)->value == 2);
	CHECK(Get_Head(b)->value == Get_Head(b_copy)->next->value);

    Stack<T> a_copy(a);
	a = a_copy;
	b = b_copy;
	CHECK(a == a_copy);
	CHECK(b == b_copy);

	a.Swap(b);
	CHECK(a == b_copy);
	CHECK(b == a_copy);

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

	c_move.Clean_up();
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