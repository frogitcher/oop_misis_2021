#include "mySet.h"
#include <stdexcept>
#include <cmath>

mySet::mySet(size_t size) {
	data = std::vector<int>(size);
}
mySet::~mySet() {
	data.clear();
}

void mySet::add(const int value) {
	if (find(value) != -1) {
		data.push_back(value);
	}
}

bool mySet::empty() const {
	if (data.size() == 0) {
		return true;
	}
	return false;
}
size_t mySet::getSize() const {
	return data.size();
}
void mySet::insert(const int value, const int index) {
	if (index < data.size()) {
		if (find(value) != -1) {
			data[index] = value;
		}
	}
	else {
		throw std::invalid_argument("Выход за пределы");
	}
}
int mySet::find(int value) const {
	for (int i = 0; i < data.size(); i++) {
		if (value == data[i]) {
			return i;
		}
	}
	return -1;
}
void mySet::erase(int value) {
	int id = find(value);
	if (id >= 0) {
		for (int i = id; i < data.size() - 1; i++) {
			data[i] = data[i + 1];
		}
		data.pop_back();
	}
}
auto mySet::begin() const{
	return data.begin();
}
auto mySet::end() const{
	return data.end();
}

void mySet::operator=(const mySet& other) {
	data.clear();
	data = other.data;
}
