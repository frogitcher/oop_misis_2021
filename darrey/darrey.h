#pragma once
#include <initializer_list>
#include <stddef.h>

class darrey {
public:
	
	darrey(size_t lenght = 0, int value = 0); // checked
	darrey(const darrey& other); // checked
	darrey(const std::initializer_list<int>& list); // checked
	darrey& operator=(const darrey& other); // checked
	~darrey();

	int& operator[](const size_t i) const; // checked
	int& at(const size_t i) const;// checked

	int* begin() const; // checked
	int* end() const; // checked

	void push_back(const int value); // checked
	void pop_back(); // checked
	void clear(); // checked
	void erase(size_t i); // checked
	void resize(const size_t new_size); // checked
	void assign(const size_t new_size, const int value); // checked
	void swap(darrey& other); // checked
	void insert(const size_t i, const int value); // checked

	

	bool operator==(const darrey& other) const; // checked
	bool operator!=(const darrey& other) const; // checked


	size_t getsize() const; // checked
	size_t getcapacity() const; // checked
	bool empty() const; // checked
private:
	size_t capacity = 0; // fiz razmer
	size_t size = 0; // logich razmer
	int* data;
	void reallocate(size_t new_capacity = 0);
	
};