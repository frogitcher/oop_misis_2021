#pragma once
#include <initializer_list>

class dynamicarray
{
public:

	dynamicarray(size_t _size = 0, int value = 0);
	dynamicarray(const dynamicarray& other);
	dynamicarray(const std::initializer_list<int>& list);
	~dynamicarray();

	void reallocate(size_t new_capacity);

	size_t Size() const;
	size_t Capacity() const;
	bool empty() const;

	int& operator[](size_t index) const;
	int& at (size_t index) const;
	void push_back(int value);
	void pop_back();
	void clear();
	void erase(size_t index);
	void assign(size_t _size, int value = 0);
	void resize(size_t new_size);
	void swap(dynamicarray& other);
	void insert(size_t index, int value);

	int* begin() const;
	int* end() const;

	bool operator==(const dynamicarray& other) const;
	bool operator!=(const dynamicarray& other) const;

	dynamicarray& operator=(const dynamicarray& other);
private:
	size_t capacity = 0;
	size_t size = 0;
	int* data;
};
