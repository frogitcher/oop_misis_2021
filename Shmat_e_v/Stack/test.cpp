
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Stack constructors and operators", T, int, float, double, long long)
{
	Stack<T> s({ 1, 2, 3 });
	Stack<T> s1({ 1, 2, 3 });
	CHECK(s == s1);

	Stack<T> s2;
	Stack<T> s3;
	CHECK(s2 == s3);

	Stack<T> s4 = { 4, 5, 6 };
	Stack<T> s5 = { 4, 5, 6 };
	CHECK(s4 == s5);

	Stack<T> s6 = Stack<T> ({ 7, 8, 9 });
	Stack<T> s7 = Stack<T> ({ 7, 8, 9 });
	CHECK(s6 == s7);

	Stack<T> s8({ 10, 11, 12 });
	Stack<T> s9(s8);
	Stack<T> s10(s9);
	CHECK(s8 == s9);
	CHECK(s9 == s10);
	CHECK(s8.Size() == s9.Size());
	CHECK(s9.Size() == s10.Size());

	CHECK(s1 != s2);
	CHECK(s3 != s4);
}

TEST_CASE_TEMPLATE("Testing Push, Pop", T, int, float, double, long long)
{
	Stack<T> a;
	a.push(1);
	a.push(2);
	CHECK(a == Stack<T> ({ 1, 2 }));
	a.pop();
	CHECK(a == Stack<T> ({ 1 }));
	CHECK(a.get() == 1);
	a.pop();
	CHECK(a.Size() == 0);
	CHECK_THROWS_WITH(a.pop(), "Stack is empty");

	Stack<T> c;
	CHECK(c.Size() == 0);
	CHECK(c.empty());

	for (T i = 0; i < 10; i++)
	{
		c.push(i);
		CHECK(c.get() == i);
		CHECK(c.Size() == (int)(i + 1));
	}
	for (T i = c.Size(); i <= 0; i--)
	{
		CHECK(c.Size() == i);
		CHECK(c.get() == i);
		c.pop();
	}
}

TEST_CASE_TEMPLATE("Testing Swap", T, int, float, double, long long)
{
	Stack<T> a = Stack<T> ({ 1, 2, 3 });
	Stack<T> b = Stack<T> ({ 4, 5, 6, 7 });

	a.swap(b);
	CHECK(a == Stack<T> ({ 4, 5, 6, 7 }));
	CHECK(b == Stack<T> ({ 1, 2, 3 }));

	a.clear();
	b.clear();

	a.swap(b);
	CHECK(a == b);
	CHECK(a.Size() == 0);
	CHECK(b.empty() == true);
}

TEST_CASE_TEMPLATE("Testing merge", T, int, float, double, long long)
{
	Stack<T> a = Stack<T> ({ 1, 2, 3 });
	Stack<T> b = Stack<T> ({ 4, 5, 6, 7 });

	a.merge(b);
	CHECK(a.Size() == 7);
	CHECK(b.Size() == 0);
}
