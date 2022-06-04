#pragma once
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>

template <typename K, typename V>
class Gist {
public:
	Gist();
	Gist(const Gist<K, V>& other);
	//Gist(const std::initializer_list<T>& list);
	~Gist() = default;

	V operator[](const K& key);

	void add(const std::pair<K, V>& _val);
	bool in_gist(const std::pair<K, V>& _val);

private:
	std::vector<std::pair<K, V> >* data;
	size_t size_;
};

template<typename K, typename V>
Gist<K, V>::Gist() {
	data = new std::vector<std::pair<K, V> > ();
	size_ = 0;
}

template<typename K, typename V>
Gist<K, V>::Gist(const Gist<K, V>& other) {
	data = new std::vector<std::pair<K, V> > (other.size_);
	std::copy(other.data, other.data + other.size_, data);
	size_ = other.size_;
}

/*template<typename K, typename V>
Gist<K, V>::~Gist() {
	delete[] data;
}
*/


template<typename K, typename V>
bool Gist<K, V>::in_gist(const std::pair<K, V>& _val) {
	if (size_ == 0)
		return true;
	for (auto i: *data) { 
		if (i.first == _val.first)
			return true;
	}
	return false;
}

template<typename K, typename V>
V Gist<K, V>::operator[](const K& key) {
	for (auto i: *data) { 
		if (i.first == key)
			return i.second;
	}
}

template<typename K, typename V>
void Gist<K, V>::add(const std::pair<K, V>& _val) {
	if (this->in_gist(_val)){
		data->push_back({_val.first, _val.second});
		size_++;
	}
}
