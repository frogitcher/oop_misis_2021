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
	inline const size_t Size() const
	{
		return size;
	}
	inline const size_t Capacity() const
	{
		return capacity;
	}
	inline bool Empty() const
	{
		return size == 0;
	}
	inline int* Get_Data() const
	{
		return data;
	}

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
	inline int* begin() const
	{
		return data;
	}
	inline int* end() const
	{
		return  data + size;
	}

	//Logical functions
	bool operator==(const Dynamic_Array& other) const;
	bool operator!=(const Dynamic_Array& other) const;

	//Assignment
	Dynamic_Array& operator=(const Dynamic_Array& other);

	//Indexing and referencing
	inline int& operator[](size_t i) const
	{
		return *(data + i);
	}
	int& at(size_t el) const;

private:
	int64_t size = 0;
	size_t capacity = 0;
	int* data;
	void reallocate(size_t new_capacity);
	void create_data(size_t new_size);

};