#pragma once
#include <initializer_list>

class DynamicArray {
private:
	size_t capacity = 0;
	size_t size = 0;
	int* data = new int[0];
public:
	DynamicArray() = default;
	DynamicArray(size_t lenght, int value = 0);
	DynamicArray(const DynamicArray& other);
	DynamicArray(const std::initializer_list<int>& list);
	~DynamicArray();

	size_t Size() const;
	size_t Capacity() const;

	void push_back(int value);
	void pop_back(); /// кинуть когда пустой
	void clear();
	void erase(size_t index);
	void insert(size_t index, int value);
	void resize(size_t new_size);
	void assign(size_t new_size, int value);
	void swap(DynamicArray& other);

	int* begin();
	int* end();

	int& operator[] (size_t i) const;
	int& at(size_t i) const;

	bool empty() const;
	bool operator== (const DynamicArray& other) const;
	bool operator!= (const DynamicArray& other) const;
	DynamicArray& operator= (const DynamicArray& other);
};
