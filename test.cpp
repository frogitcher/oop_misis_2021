#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "stack.h"
#include <string>

TEST_CASE("testing rac class") {
	Stack<int>a;
	a.push(1);
	a.push(2);
	a.push(3);
	CHECK(a.Size() == 3);
	CHECK(a.get() == 3);
	a.pop();
	CHECK(a.Size() == 2);
	CHECK(a.get() == 2);
	a.pop();
	CHECK(a.get() == 1);
	CHECK(a.Size() == 1);
	a.pop();
	CHECK(a.Empty());
	Stack<int>b;
	b.push(3);
	b.push(2);
	a.swap(b);
	CHECK(a.get() == 2);
	CHECK(b.Empty());
	
	Stack<string>aa;
	aa.push("1");
	aa.push("2");
	aa.push("3");
	CHECK(aa.Size() == 3);
	CHECK(aa.get() == "3");
	aa.pop();
	CHECK(aa.Size() == 2);
	CHECK(aa.get() == "2");
	aa.pop();
	CHECK(aa.get() == "1");
	CHECK(aa.Size() == 1);
	aa.pop();
	CHECK(aa.Empty());
	Stack<string>bb;
	bb.push("3");
	bb.push("2");
	//aa.swap(bb);
	//CHECK(aa.get() == "2");
	//CHECK(bb.Empty());	
}
