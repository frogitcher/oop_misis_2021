#pragma once
#include <initializer_list>

class Stack {
public:
	Stack() = default;
	Stack(const std::initializer_list<int>& list);
	Stack(size_t _size, int value = 0);
	~Stack();
	void Push(const int value);
	void Pop();
	size_t Size() const;
	bool Empty() const;
	int Get() const;
	bool operator==(const Stack& st) const;
	bool operator!=(const Stack& st) const;
	Stack& operator=(const Stack& st);
private:
	size_t size = 0;
	size_t capacity = 0;
	int* data = nullptr;
};
