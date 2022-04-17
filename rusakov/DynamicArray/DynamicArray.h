#pragma once

class DynamicArray {
private:
	size_t size = 0;
	int* data;
	size_t capacity = 0;
public:
	DynamicArray();  
	~DynamicArray();
	DynamicArray(size_t length, int value = 0);
	DynamicArray(const DynamicArray& other);
	DynamicArray(const std::initializer_list<int>& list); 
	size_t Size() const; 
	size_t Capacity() const;
	bool Empty() const; 
	int& operator[](size_t i) const;
	int& at(size_t i)const;
	void push_back(int value); 
	void pop_back(); 
	void clear();
	void erase(size_t index); 
	void resize(size_t new_size);
	int* begin();
	int* end();
	void swap(DynamicArray& other);
	void assign(size_t new_size, int value); 
	bool operator==(const DynamicArray& other) const;
	bool operator!=(const DynamicArray& other) const;
	DynamicArray& operator=(const DynamicArray& other);
};