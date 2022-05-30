#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

/*Stack<int> a;
Stack<int> b = a;
Stack<int> c = a;
Stack<int> a_copy(a);
Stack<int> d{ 29,36,84 ,76 };
Stack<double> e{ 88,65.23,25.63,45.418 };*/
TEST_CASE_TEMPLATE("Testing constructors and ==", Val, int, double, float, long long, unsigned long long) {
	Stack<Val> a;
	CHECK(a.Size() == 0);
	CHECK(Get_Head(a) == nullptr);
	CHECK(Get_Tail(a) == nullptr);

	Stack<Val> b(a);
	CHECK(b.Size() == a.Size());
	CHECK(b == a);

	Stack<Val> c(a);
	CHECK(c.Size() == b.Size());
	CHECK(c == b);

	Stack<Val> d(std::initializer_list<Val>{ 28, 36, 84, 76 });
	CHECK(d != b);
	CHECK_FALSE(d == a);
	CHECK(d.Size() != a.Size());
}

TEST_CASE_TEMPLATE("Testing stack methods", Val, int, double, float, long long, unsigned long long) {
	Stack<Val> e(std::initializer_list<Val>{ 88, (Val)65.23, (Val)25.63, (Val)45.418  });
	Stack<Val> e_copy(e);
	e.Push((Val)-129.3);
	CHECK(e != e_copy);
	CHECK_FALSE(e == e_copy);
	CHECK(e.Size() == e_copy.Size() + 1);
	CHECK(e.Get() == (Val)-129.3);
	CHECK(Get_Head(e)->value == (Val)-129.3);
	CHECK(Get_Head(e)->next->value == Get_Head(e_copy)->value);
	e.Pop();
	e.Pop();
	CHECK(e.Size() == 3);

	Stack<Val> d(std::initializer_list<Val>{ 28, 36, 84, 76 });
	Stack<Val> d_copy(d);
	e = e_copy;
	d = d_copy;
	CHECK(e == e_copy);
	CHECK(d == d_copy);
	e.Swap(d);
	CHECK(e == d_copy);
	CHECK(d == e_copy);
	d.Swap(e);
	 
	e.Merge(d);
	CHECK(e == Stack<Val>(std::initializer_list<Val>{ 28, 36, 84, 76, 88, (Val)65.23, (Val)25.63, (Val)45.418 }));
	CHECK(e.Size() == e_copy.Size() + d_copy.Size());
	CHECK(e.Get() == (Val)45.418);
	CHECK(Get_Head(e)->value == Get_Head(e_copy)->value);
	CHECK(Get_Tail(e)->value == Get_Tail(d_copy)->value);

	Stack<Val> f(std::initializer_list<Val>{ 13, 98, 133, 421 });
	Stack<Val> f_copy(std::move(f));
	CHECK(f.Size() == 0);
	CHECK(f_copy.Size() == 4);
	CHECK(Get_Head(f) == nullptr);
	CHECK(Get_Tail(f) == nullptr);
	CHECK(f_copy.Get() == 421);

	f_copy.Clear();
	CHECK(f_copy.Size() == 0);
	CHECK(f_copy == Stack<Val>());
	CHECK_THROWS_WITH(f_copy.Pop(), "Stack is empty!");
	CHECK_THROWS_WITH(f_copy.Get(), "Thare are no elements in stack!");

	Stack<Val> g(std::initializer_list<Val>{ 198, 258, 323, 594 });
	Stack<Val> g_copy = std::move(g);
	CHECK(g.Size() == 0);
	CHECK(g_copy.Size() == 4);
	CHECK(Get_Head(g) == nullptr);
	CHECK(Get_Tail(g) == nullptr);
	CHECK(g_copy.Get() == 594);
	CHECK_THROWS_WITH(g.Pop(), "Stack is empty!");
}