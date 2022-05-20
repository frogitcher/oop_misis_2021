#pragma once
#include <initializer_list>
#include <cstdint>

class DynamicArray {
private:
	int64_t capacity = 0;
	int64_t size = 0;
	int* data = new int[0];
	void reallocate(int64_t new_capacity);

public:

	DynamicArray() = default;
	DynamicArray(int64_t _size);
	DynamicArray(int64_t _size, int value);
	DynamicArray(const DynamicArray& other);
	DynamicArray(const std::initializer_list<int>& list);
	~DynamicArray();

	int64_t Size() const;
	int64_t Capacity() const;
	int* begin() const;
	int* end() const;

	int& operator[](int64_t i) const;
	int& at(int64_t i) const;

	bool empty() const;
	void clear();

	void erase(int64_t i);
	void pop_back();
	void insert(int64_t i, int value);
	void push_back(int value);
	void resize(int64_t new_size);
	void assign(int64_t new_size, int value);

	DynamicArray& operator=(const DynamicArray& other);

	void swap(DynamicArray& other);

	bool operator==(const DynamicArray& other) const;
	bool operator!=(const DynamicArray& other) const;



};
