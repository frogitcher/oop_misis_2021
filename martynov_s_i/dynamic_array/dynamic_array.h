#pragma once
#include <initializer_list>

class DynamicArray {
private:
	size_t capacity = 0;
	size_t size = 0;
	int* data = nullptr;
	void Create(size_t size, size_t capacity, int* oth_data);
public:
	DynamicArray(size_t lenght = 0, int value = 0);
	DynamicArray(const DynamicArray& other);
	DynamicArray(const std::initializer_list<int>& list);
	~DynamicArray();

	size_t Size() const;
	size_t Capacity() const;

	void push_back(int value);
	void pop_back();
	void clear();
	void erase(size_t index);
	void insert(size_t index, int value);
	void resize(size_t new_size);
	void assign(size_t new_size, int value);
	void swap(DynamicArray& other);

	int* begin() const;
	int* end() const;

	int& operator[] (size_t i) const;
	int& at(size_t i) const;

	bool empty() const;
	bool operator== (const DynamicArray& other) const;
	bool operator!= (const DynamicArray& other) const;
	DynamicArray& operator= (const DynamicArray& other);
};
