#pragma once
#include <cstdint>
#include <initializer_list>

class DynamicArray
{
public:
	DynamicArray(int length = 0, int value = 0);
	DynamicArray(const DynamicArray& other);
	DynamicArray(const std::initializer_list<int>& list);
	~DynamicArray();
	int Size() const;
	int Capacity() const;
	bool Empty() const;
	bool operator==(const DynamicArray& other) const;
	bool operator!=(const DynamicArray& other) const;
	int& operator[](int i) const;
	int& at(int i) const; 
	void push_back(int value);
	void pop_back();
	void clear();
	void erase(int i); 
	void resize(int nwsize);
	void assign(int nwsize, int value);
	void insert(int i, int value); 
	int* begin() const;
	int* end() const;
	void swap(DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& other);
private:
	int capacity = 0;
	int size = 0;
	int* data;
	void ResizeArray(int nwcapacity);
};
