#pragma once
#include <initializer_list>
#include <cstdint>
class Dynamic_Array {
public:

	//Array Creation
	Dynamic_Array();
	~Dynamic_Array();
	Dynamic_Array(size_t length, int value = 0);
	Dynamic_Array(const Dynamic_Array& other);
	Dynamic_Array(const std::initializer_list<int>& list);

	//Array Fillability
	const size_t Size() const;
	const size_t Capacity() const;
	bool Empty() const;
	int* Get_Data() const;

	//Actions with arrays
	void push_back(int value);
	void pop_back();
	void clear();
	void erase(size_t index);
	void insert(size_t index, int value);
	void resize(size_t new_size);
	void assign(size_t new_size, int value);
	void swap(Dynamic_Array& other);

	//Pointers
	int* begin();
	int* end();

	//Logical functions
	bool operator==(const Dynamic_Array& other) const;
	bool operator!=(const Dynamic_Array& other) const;

	//Assignment
	Dynamic_Array& operator=(const Dynamic_Array other);

	//Indexing and referencing
	int& operator[](size_t i) const;
	int& at(size_t el) const;

private:
	size_t size = 0;
	size_t capacity = 0;
	int* data;
	void reallocate(size_t new_capacity);
	void create_data(size_t new_size);

};