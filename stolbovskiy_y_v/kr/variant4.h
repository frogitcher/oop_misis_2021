#pragma once

class myset {
public:
	myset() default;
	~myset();
	myset(myset& other const);

	void reallocate(size_t new_cap);

	bool Empty() const;
	size_t Size() const;
	void Insert(int v);
	int* Find(int v) const;
	void Erase(int v);

	int* Begin() const;
	int* End() const;

	myset operator=(myset& other const);
private:
	int* data;
	size_t size;
	size_t cap;
};