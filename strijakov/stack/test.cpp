#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"
#include "iostream"

TEST_CASE("Testing #1") {

    Stack<int> stack1;
    Stack<int> stack2;
    Stack<int> stack1_1 = stack1;
    Stack<int> stack3{2,4,8,16};
    Stack<int> stack4(stack3);
    stack1.Push(1);
    CHECK(stack1.Get() == 1);
    stack2.Push(2);
    stack2.Pop();
    CHECK(stack2.Empty());
    Stack<int> stack3_1 = stack3;
    CHECK(stack4 == stack3_1);
    stack3_1.Clear();
    CHECK(stack3_1.Empty());
    Stack<int> lh{1,2,3};
    Stack<int> rh{4,5};
    rh.merge(lh);
    CHECK(rh.Get() == 5);

}

TEST_CASE("Testing #2") {
	Stack<int> stack_ex;
	CHECK_THROWS_WITH(stack_ex.Get(), "Stack is empty");
	CHECK_THROWS_WITH(stack_ex.Pop(), "Stack is empty");
}
