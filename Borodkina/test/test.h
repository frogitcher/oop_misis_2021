#pragma once
#include <cstdint>
#include <initializer_list>

class Stack
{
	public:
	Stack(int size_, int value);
	Stack(Stack& other);
	~Stack();	
	void Push(int value);
	Stack &operator=(const Stack& other);
	bool operator==(const Stack& other);
	bool operator!=(const Stack& other);
	void Pop();
	int Get();
	int Size();
	void Clear();
	bool Empty();
	private:
	int* data=0;
	int capacity=0;
	int size = 0;
	void Reallocate(int new_capacity);

};