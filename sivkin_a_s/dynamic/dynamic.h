#pragma once
#include <initializer_list>
#include <stdexcept>

class DynamicArray {
	public:
	DynamicArray() = default;
	DynamicArray(int64_t length, int value=0);
	DynamicArray(const DynamicArray &other);
	DynamicArray(const std::initializer_list <int> &list);
	~DynamicArray();

	int64_t Size() const;
	int64_t Capacity() const;

	void Reallocate(int64_t new_capacity);
	bool Empty() const;

	int& operator[](int64_t i);
	int& at(int64_t i) const;
	void push_back(int value);
	void pop_back(); 
	void clear();
	void erase(int64_t index);
	void resize(int64_t newsize);
	int* begin() const;
	int* end() const;
	void swap(DynamicArray& other);
	void assign(int64_t new_size, int value);
	bool operator==(const DynamicArray& other) const;
	bool operator!=(const DynamicArray& other) const;

	DynamicArray& operator=(const DynamicArray& other);
	void insert(int64_t index, int value);
	
	private:
	int64_t capacity=0;
	int64_t size=0;
	int* data = 0;
};
