#pragma once
#include <initializer_list>
#include <cstdint>
Class Stack {
public:
	Stack(std::initializer_list<int> list);
	Stack(Stack& other);
	~Stack();
	
	void reallocate(int64_t new_size);
	
	int* begin() const;
	int* end() const;
	
	void Push(int value);
	void Pop();
	int64_t Size() const;
	bool Empty() const;
	int Get() const;
	
	bool operator==(Stack& other const) const;
	bool operator!=(Stack& other const) const;
	
	Stack& operator=(Stack& other const);
private:
	int64_t size;
	int64_t capacity;
	int* data;
};