#pragma once

class stack {
public:
	// assuming the array is always initialized as empty
	stack(int64_t _size = 0, int value);
	stack& operator=(const stack &rhs);
	~stack();
	stack& stack(const stack &another);

	void Push(int val);
	void Pop();
	bool Empty() const { return size - start == 0; }
	int64_t Size() const { return size - start; }
	int Get();
private:
	int64_t size = 0;
	int64_t capacity = 0;
	int64_t start = 0;
	int* data;
	void realloc(int64_t new_cap);
};

