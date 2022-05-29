#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stack.h"

TEST_CASE_TEMPLATE("Testing constructors and bool func", T, int, float, double, long long, unsigned long long, char, unsigned int, size_t, int16_t, int8_t) {
	Stack<T> stack1;
	CHECK(stack1.Size() == 0);
	CHECK_FALSE(stack1.Size() == 15);
	CHECK(Get_Head(stack1) == nullptr);
	CHECK(Get_Tail(stack1) == nullptr);
	//---------------------------------------
	Stack<T> stack2(stack1);
	CHECK(stack2.Size() == stack1.Size());
	CHECK_FALSE(stack2 != stack1);
	//---------------------------------------
	Stack<T> stack3(std::initializer_list<T>{ (T)14.5f, (T)-228.1337, 3});
	CHECK(stack3 != stack1);
	CHECK_FALSE(stack3 == stack2);
}

TEST_CASE_TEMPLATE("Testing methods", T, int, float, double, long long, unsigned long long, char, unsigned int, size_t, int16_t, int8_t) {
	Stack<T> stack0(std::initializer_list<T>{ 1, 2, 3, 4, 5, 6, 7});
	Stack<T> stack0_move = std::move(stack0);
	CHECK_FALSE(stack0.Size() != 0);
	CHECK(stack0_move.Size() == 7);
	CHECK(Get_Head(stack0) == nullptr);
	CHECK(Get_Tail(stack0) == nullptr);
	CHECK(stack0_move.Get() == 7);
	//---------------------------------------
	Stack<T> stack1(std::initializer_list<T>{ 1, 2, 3, (T)4.5 });
	Stack<T> stack1_c(stack1);
	stack1.Push((T)-9.3);
	CHECK(stack1 != stack1_c);
	CHECK_FALSE(stack1 == stack1_c);
	CHECK(stack1.Size() == stack1_c.Size() + 1);
	CHECK(stack1.Get() == (T)-9.3);
	CHECK(Get_Head(stack1)->value == (T)-9.3);
	CHECK(Get_Head(stack1)->next->value == Get_Head(stack1_c)->value);
	//---------------------------------------
	Stack<T> stack2(std::initializer_list<T>{ (T)-5, 2, (T)133.9 });
	Stack<T> stack2_c(stack2);
	stack2.Pop();
	CHECK_FALSE(stack2 == stack2_c);
	CHECK(stack2.Size() == stack2_c.Size() - 1);
	CHECK(stack2.Get() == 2);
	CHECK(Get_Head(stack2)->value == 2);
	CHECK(Get_Head(stack2)->value == Get_Head(stack2_c)->next->value);
	//---------------------------------------
	stack1 = stack1_c;
	stack2 = stack2_c;
	CHECK_FALSE(stack1 != stack1_c);
	CHECK(stack2 == stack2_c);
	//---------------------------------------
	stack1.Swap(stack2);
	CHECK(stack1 == stack2_c);
	CHECK(stack2 == stack1_c);
	//---------------------------------------
	stack1.Merge(stack2);
	CHECK(stack1 == Stack<T>(std::initializer_list<T>{ 1, 2, 3, (T)4.5, (T)-5, 2, (T)133.9 }));
	CHECK_FALSE(stack1.Size() == 228);
	CHECK(stack1.Get() == (T)133.9);
	CHECK_FALSE(Get_Head(stack1)->value != Get_Head(stack2_c)->value);
	CHECK(Get_Tail(stack1)->value == Get_Tail(stack1_c)->value);
	//---------------------------------------
	Stack<T> stack3(std::initializer_list<T>{ 1, 2, 3, 4 });
	Stack<T> stack3_move(std::move(stack3));
	CHECK(stack3.Size() == 0);
	CHECK(stack3_move.Size() == 4);
	CHECK(Get_Head(stack3) == nullptr);
	CHECK(Get_Tail(stack3) == nullptr);
	CHECK(stack3_move.Get() == 4);
	//---------------------------------------
	stack3_move.Clear();
	CHECK(stack3_move.Size() == 0);
	CHECK(stack3_move == Stack<T>());
	CHECK_THROWS_WITH(stack3_move.Get(), "Stack empty!");
	CHECK_THROWS_WITH(stack3_move.Pop(), "Stack empty!");
}