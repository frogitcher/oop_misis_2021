#pragma once
#include <cstdint>
#include <initializer_list>

class DynamicArray
{


public:
	DynamicArray(size_t length = 0, int value = 0);
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
	void erase(size_t i); 
	void resize(size_t new_size);
	void assign(size_t new_size, int value);
	int* begin() const;
	int* end() const;
	void swap(DynamicArray& other);

	DynamicArray& operator=(const DynamicArray& other);
	bool operator==(const DynamicArray& other) const;
	bool operator!=(const DynamicArray& other) const;
	

private:
	size_t capacity = 0;
	size_t size = 0;
	int* data;
	void change_capacity(size_t new_capacity);
};