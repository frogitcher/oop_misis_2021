#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Stack.h"
#include <string>

TEST_CASE_TEMPLATE("Test stack", T, int, float, double, long long) {
	Stack<T> a;
	CHECK_THROWS(a.Pop());
	CHECK_THROWS(a.Get());
	CHECK(a.Size() == 0);
	CHECK(a.Empty());
	for (T i = 6; i < 11; ++i) {
		a.Push(i);
	}
	CHECK(a == Stack<T>({ 6, 7, 8, 9, 10 }));
	CHECK(a.Get() == 10);
	CHECK(a.Size() == 5);
	CHECK(!a.Empty());
	a.Pop();
	CHECK(a.Get() == 9);
	CHECK(a.Size() == 4);
	
	Stack<T> b({ 1, 2, 3, 4, 5 });
	CHECK(b.Size() == 5);
	CHECK(b.Get() == 5);
	for (size_t i = 0; i < 5; ++i) {
		b.Pop();
	}
	CHECK(b.Size() == 0);
	CHECK(b.Empty());
	CHECK(a != b);

	Stack<T> c(a);
	CHECK(c.Size() == a.Size());
	CHECK(c == a);
	c.Merge(a);
	CHECK(c == Stack<T>({ 6, 7, 8, 9, 6, 7, 8, 9 }));
	CHECK(c.Size() == 8);
	for (T i = 1; i < 11; ++i) {
		a.Push(i);
	}
	c.Swap(a);
	CHECK(c.Size() == 10);
	CHECK(a.Size() == 8);
	CHECK(a == Stack<T>({ 6, 7, 8, 9, 6, 7, 8, 9 }));
	CHECK(c == Stack<T>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
	c = b;
	CHECK(c.Empty());
	CHECK(c == b);

	Stack<T> d(std::move(a));
	CHECK(d == Stack<T>({ 6, 7, 8, 9, 6, 7, 8, 9 }));
	CHECK(a.Size() == 0);
}

TEST_CASE("Test stack") {
	Stack<std::string> a({ "1", "2", "3", "4", "5" });
	CHECK(a.Size() == 5);
	CHECK(a.Get() == "5");
	a.Pop();
	CHECK(a == Stack<std::string>({ "1", "2", "3", "4" }));
	a.Push("543");
	CHECK(a == Stack<std::string>({ "1", "2", "3", "4", "543" }));
	CHECK(!a.Empty());

	Stack<std::string> b(a);
	CHECK(b == Stack<std::string>({ "1", "2", "3", "4", "543" }));
	a.Merge(b);
	CHECK(a.Size() == 10);
	CHECK(a == Stack<std::string>({ "1", "2", "3", "4", "543", "1", "2", "3", "4", "543" }));

	Stack<std::string> c;
	CHECK_THROWS(c.Pop());
	CHECK_THROWS(c.Get());
	CHECK(a != c);
	c = a;
	CHECK(c == Stack<std::string>({ "1", "2", "3", "4", "543", "1", "2", "3", "4", "543" }));

}