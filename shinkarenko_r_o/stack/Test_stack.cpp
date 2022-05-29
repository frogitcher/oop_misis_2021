#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "stack.h"
#include "doctest.h"

TEST_CASE("Testing constructors") {
	Stack<int> stack_1;
	CHECK(stack_1.Size() == 0);
	CHECK(stack_1.Empty());
	
	Stack<int> stack_2({ 1, 2, 3, 4, 0 });
	CHECK(stack_2.Size() == 5);
	CHECK(stack_2.Get() == 0);

	Stack<int> stack_3(stack_2);
	CHECK(stack_2.Size() == stack_3.Size());
	CHECK(stack_2.Get() == stack_3.Get());
}

TEST_CASE("Testing Pop, Push and Get") {
	Stack<int> stack_1;
	stack_1.Push(123);
	CHECK(stack_1.Size() == 1);
	CHECK(stack_1.Get() == 123);
	stack_1.Push(321);
	CHECK(stack_1.Size() == 2);
	CHECK(stack_1.Get() == 321);
	stack_1.Pop();
	CHECK(stack_1.Get() == 123);
	CHECK(stack_1.Size() == 1);
	stack_1.Pop();
	CHECK(stack_1.Size() == 0);

	CHECK_THROWS_WITH(stack_1.Pop(), "Pop on empty stack");
	CHECK_THROWS_WITH(stack_1.Get(), "Trying to get value of an empty stack");
}

TEST_CASE("Testing other functions") {
	Stack<int> stack_1({ 1, 2 });
	stack_1.Clear();
	CHECK(Stack<int>({ 1, 1, 1 }) == Stack<int>({ 1, 1, 1 }));
	CHECK(stack_1.Size() == 0);

	Stack<int> stack_2({ 2, 3 });
	stack_1 = stack_2;
	CHECK(stack_1.Size() == stack_2.Size());
	CHECK(stack_1.Get() == stack_2.Get());
	Stack<int> stack_3({ 3, 3, 3 });
	stack_3.swap(stack_1);
	CHECK(stack_3 == Stack<int>({ 2, 3 }));
	CHECK(stack_1 == Stack<int>({ 3, 3, 3 }));
	CHECK(stack_1 != stack_3);
	stack_1.Merge(stack_2);
	CHECK(stack_1.Size() == 5);
	CHECK(stack_1 == Stack<int>({ 2, 3, 3, 3, 3 }));
}