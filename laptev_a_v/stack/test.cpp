#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Testing constructors and boolean operators", T, int, double, float, long long, unsigned long long) {
	Stack<T> s;
	Stack<T> st(s);
	CHECK(s.Size() == 0);
	CHECK(Get_Head(s) == nullptr);
	CHECK(Get_Tail(s) == nullptr);
	Stack<T> st(s);
	CHECK(s == st);
	CHECK(st.Size() == s.Size());
	Stack<T> x(std::initializer_list<T>{(T)7.45, 3, (T)-1.3f, 0 });
	CHECK(x != s);
	CHECK(!(x == st));
}

TEST_CASE_TEMPLATE("Testing methods", T, int, double, float, long long, unsigned long long) {
	Stack<T> x(std::initializer_list<T>{ 1, 2, 3, 4, 5 });
	Stack<T> x_copy(x);
	x.Push((T)7.7);
	CHECK(x != x_copy);
	CHECK_FALSE(x == x_copy);
	CHECK(x.Size() == x_copy.Size() + 1);
	CHECK(x.Get() == (T)7.7);
	CHECK(Get_Head(x)->value == (T)7.7);
	CHECK(Get_Head(x)->next->value == Get_Head(x_copy)->value);
	Stack<T> y(std::initializer_list<T>{ 1, 2, 3 });
	Stack<T> y_copy(y);
	y.Pop();
	CHECK(y != y_copy);
	CHECK_FALSE(y == y_copy);
	CHECK(y.Size() == y_copy.Size() - 1);
	CHECK(y.Get() == 2);
	CHECK(Get_Head(y)->value == 2);
	CHECK(Get_Head(y)->value == Get_Head(y_copy)->next->value);
	x = x_copy;
	y = y_copy;
	CHECK(x == x_copy);
	CHECK(y == y_copy);
	x.Swap(y);
	CHECK(x == y_copy);
	CHECK(y == x_copy);
	Stack<T> x(std::initializer_list<T>{ 1, 2, 3, 4, 5 });
	Stack<T> y(std::initializer_list<T>{ 6, 7});
	y.Merge(x);
	CHECK(y == Stack<T>(std::initializer_list<T>{ 1, 2, 3, 4, 5, 6, 7}));
	CHECK(x.Size() == 7);
	CHECK(x.Get() == 7)
	Stack<T> z(std::initializer_list<T>{ 1, 2, 3});
	Stack<T> z_move(std::move(z));
	CHECK(z.Size() == 0);
	CHECK(z_move.Size() == 3);
	CHECK(Get_Head(z) == nullptr);
	CHECK(Get_Tail(z) == nullptr);
	CHECK(z_move.Get() == 3);
	z_move.Clear();
	CHECK(z_move.Size() == 0);
	CHECK(z_move == Stack<T>());
	CHECK_THROWS_WITH(z_move.Pop(), "stack is empty!");
	CHECK_THROWS_WITH(z_move.Get(), "stack is empty!");

	Stack<T> z(std::initializer_list<T>{ 1, 2, 3});
	Stack<T> z_move = std::move(z);
	CHECK(z.Size() == 0);
	CHECK(z_move.Size() == 3);
	CHECK(Get_Head(z) == nullptr);
	CHECK(Get_Tail(z) == nullptr);
	CHECK(z_move.Get() == 3);
}
