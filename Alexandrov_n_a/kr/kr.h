#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
template <typename T>
class gist {
public:
	gist() = default;
	gist(const gist& other);
	gist(std::initializer_list<std::initializer_list<T>>& list);
	~gist();
	T& get(const T& key);
	size_t Count() const;
	void add(T key, double num);
	void minus(T key, double x);
	void plus (T key, double x);
	void print();
	double med();
	bool operator== (const gist& other) const;
	bool operator!= (const gist& other) const;
	void operator=  (const gist& other) ;
private:
	std::vector<std::vector<T>> para;
};
