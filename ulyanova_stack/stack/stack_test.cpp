#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "stack.h"
#include "doctest.h"

TEST_CASE_TEMPLATE("Constructors, Empty, operator== (!=), Size", T, int, float, double, long long) {
	Stack<T> x;
	CHECK(x.Size() == 0);
	CHECK(GetHead(x) == nullptr);
	CHECK(GetTail(x) == nullptr);
	CHECK_FALSE(x.Size() == 3);

	Stack<T> y(x);
	CHECK((x == y));
	CHECK(y.Size() == 0);
	CHECK(x.Empty());
	CHECK(y.Empty());

	Stack<T> a(std::initializer_list<T>{1, 2, 3, (T) + 1, (T) + 1.0});
	CHECK(a.Size() == 5);
	CHECK(GetTail(a)->value == 1);
	CHECK(GetHead(a)->value == (T) + 1.0);
	CHECK_FALSE(a.Empty());

	Stack<T> b(a);
	CHECK(a.Size() == b.Size());
	CHECK((a == b));
	CHECK_FALSE(b.Empty());

	Stack<T> n(std::initializer_list<T>{(T) + 1, (T) + 1.0, (T)3});
	Stack<T> m(std::initializer_list<T>{(T) + 1, (T) + 1.0, (T)3});
	CHECK((m == n));
	CHECK_FALSE((n == a));
	CHECK((GetTail(n))->value == (T) + 1);
	CHECK((GetHead(n))->value == (T)3);

	Stack<T> s = std::move(n);
	CHECK((s == m));
	CHECK(GetHead(n) == nullptr);
	CHECK(GetTail(n) == nullptr);
	CHECK(n.Size() == 0);
	CHECK_FALSE((s == b));
}

TEST_CASE_TEMPLATE("Push, Pop, Get", T, int, float, double, long long) {
	Stack<T> x(std::initializer_list<T>{1, 2, 3});
	Stack<T> y(std::initializer_list<T>{1, 2, 3, 4});
	size_t s = x.Size();
	CHECK((GetHead(x))->value == 3);
	x.Push(4);
	CHECK(GetHead(x)->value == 4);
	CHECK(x.Size() == s + 1);
	CHECK((x == y));

	y.Pop();
	CHECK(y.Size() == s);
	CHECK(GetHead(y)->value == (GetHead(x)->next)->value);
	x.Pop();
	CHECK((x == y));

	Stack<T> t(std::initializer_list<T>{1});
	t.Pop();     
	CHECK(GetHead(t) == nullptr);   //Pop from 1-element stack
	CHECK(GetTail(t) == nullptr);
	CHECK(t.Size() == 0);
	CHECK_THROWS(t.Pop());

	CHECK(x.Get() == y.Get());
	CHECK(x.Get() == 3);
	CHECK(x.Get() == GetHead(x)->value);
	CHECK_FALSE(y.Get() == 4);
	CHECK_THROWS(t.Get());
}

TEST_CASE_TEMPLATE("Swap, Merge, operator= Testing", T, int, float, double, long long) {
	Stack<T> x(std::initializer_list<T>{1, (T) + 1, (T) + 1000.0, (T)1000});
	Stack<T> t;
	Stack<T> y;
	y = x;
	CHECK((y == x));
	y = t;
	CHECK((y == t));

	x.Swap(y);
	CHECK(x.Empty());
	CHECK((x == t));
	Stack<T> n(std::initializer_list<T>{1, 2, 3, 4});
	Stack<T> n1(std::initializer_list<T>{1, 2, 3, 4});
	Stack<T> m(std::initializer_list<T>{5, 6, 7});
	Stack<T> m1(std::initializer_list<T>{5, 6, 7});
	n.Swap(m);
	CHECK((n == m1));
	CHECK((m == n1));

	n.Merge(m);
	CHECK((n == Stack<T>(std::initializer_list<T>{1, 2, 3, 4, 5, 6, 7})));
	CHECK(GetHead(m) == nullptr);
	CHECK(GetTail(m) == nullptr);
	CHECK(m.Size() == 0);
	x.Merge(t);
	CHECK(x.Empty());
	n.Merge(t);
	CHECK((n == Stack<T>(std::initializer_list<T>{1, 2, 3, 4, 5, 6, 7})));
	x.Merge(n);
	CHECK((x == Stack<T>(std::initializer_list<T>{1, 2, 3, 4, 5, 6, 7})));
}
