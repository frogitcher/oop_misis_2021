#pragma once
#include <initializer_list>

class DynamicArray {
private:
	size_t capacity = 0;
	size_t size = 0;
	int* data;
public:
	DynamicArray();
	DynamicArray(size_t _size, int value = 0);
	DynamicArray(const DynamicArray& other);
	DynamicArray(const std::initializer_list<int>& list);
	~DynamicArray();

	size_t getSize() const;
	size_t getCapacity() const;

	bool empty() const;

	int& operator[](size_t i) const;
	bool operator==(const DynamicArray& other) const;
	int& at(size_t i) const;

	void push_back(int value);
	void pop_back();
	void clear();
	void erase(size_t index);
	void insert(size_t index, int value);

	void resize(size_t new_size);
	void assign(size_t new_size, int value);

	int* begin();
	int* end();

	void swap(DynamicArray& other);

	void operator=(const DynamicArray& other);
};