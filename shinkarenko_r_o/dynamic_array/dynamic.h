#pragma once
#include <initializer_list>
#include <cstdint>

class DynamicArray {
public:
	DynamicArray();
	DynamicArray(size_t length, int value = 0);
	DynamicArray(const DynamicArray& other);
	DynamicArray(const std::initializer_list<int>& list);
	
	~DynamicArray();

	size_t Size() const;
	size_t Capacity() const;
	bool Empty() const;
	
	int& operator[](size_t i) const;
	int& at(size_t i) const;

	void push_back(int value);
	void pop_back();
	void clear();
	void erase(size_t index);
	void insert(size_t idx, int value);
	void resize(int new_size, int value);
	int* begin() const;
	int* end() const;

	void swap(DynamicArray& other);
	bool operator==(const DynamicArray& other) const;
	DynamicArray& operator=(const DynamicArray& other);
	bool operator!=(const DynamicArray& other) const;
private:
	size_t capacity = 0;
	size_t size = 0;
	int* data;
	void realloc(size_t new_size);
};