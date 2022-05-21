#pragma once
#include <vector>

class mySet {
private:
	std::vector<int> data;
public:
	mySet(size_t size = 0);
	~mySet();

	void add(const int value);
	bool empty() const;
	size_t getSize() const;
	void insert(const int value, const int index);
	int find(const int value) const;
	void erase(const int value);
	auto begin() const;
	auto end() const;

	void operator=(const mySet& other);
};