#pragma once
#include <initializer_list>
#include <stddef.h>
#include <stdexcept>
class DynamicArray {
public:
	~DynamicArray();//checked
	DynamicArray(size_t _size = 0, int value = 0);//checked
	DynamicArray(const DynamicArray& other);//checked
	DynamicArray(const std::initializer_list<int>& list);//checked
	DynamicArray& operator=(const DynamicArray& other);//checked

	size_t Size() const;//checked
	size_t Capacity() const;//checked
	bool Empty() const;//checked
	int& operator[](size_t i) const;//checked
	int& at(size_t i) const;//checked


	void push_back(int value);//checked
	void pop_back();//checked
	void erase(size_t i);//checked
	void insert(size_t i, int value);//checked
	void clear();//checked
	void assign(int lenght = 0, int value = 0);//checked
	void resize(size_t new_size);//checked
	void swap(DynamicArray& other);//checked

	int* begin() const;//checked
	int* end() const;//checked

	bool operator==(const DynamicArray& other) const;//checked
	bool operator!=(const DynamicArray& other) const;//checked



private:
	size_t size = 0;
	size_t capacity = 0;
	int* data;
	void reallocate(size_t new_capacity);
};