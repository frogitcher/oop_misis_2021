#include "kr.h"
template <typename T>
bool gist<T>::operator== (const gist& other) const {
	for (int i = 0; i < para.size(); i++) {
		for (int j = 0; j < 2; j++) {
			if (para[i][j] != other.para[i][j]) {
				return false;
			}
		}
	}
	return true;
}
template <typename T>
bool gist<T>::operator!= (const gist& other) const {
	return !(*this == other);
}
template <typename T>
void gist<T>::operator= (const gist& other) {
	delete para;
	for (int i = 0; i < para.size(); i++) {
		for (int j = 0; j < 2; j++) {
			para[i][j] = other.para[i][j];
		}
	}
}
template <typename T>
gist<T>::~gist() {
	delete para;
}
template <typename T>
gist<T>::gist(const gist& other) {
	for (int i = 0; i < para.size(); i++) {
		for (int j = 0; j < 2; j++) {
			para[i][j] = other.para[i][j];
		}
	}
}
template <typename T>
gist<T>::gist(std::initializer_list<std::initializer_list<T>>& list) {
	int k = 0;
	for (i auto : list) {
		int kk = 0;
		for (j auto : i) {
			data[k][kk] == j;
			kk += 1;
		}
		k += 1;
	}
}
template <typename T>
T& gist<T>::get(const T& key) {
	for (int i = 0; i < para.size(); i++) {
		if (para[i][0] == key) {
			return para[i][1];
		}
	}
	throw "No this elen";
}
template <typename T>
void gist<T>::add(T key, double num) {
	for (int i = 0; i < para.size(); i++) {
		for (int j = 0; j < 2; j++) {
			if (para[i][j] == key) {
				num *= 2;
				return;
			}
		}
	}
	para[0].push_back(key);
	para[1].push_back(num);
}
template <typename T>
void gist<T>::minus(T key, double x) {
	for (int i = 0; i < para.size(); i++) {
		if (para[i][0] == key) {
			para[i][1] -= x;
		}
	}
}
template <typename T>
void gist<T>::plus(T key, double x) {
	for (int i = 0; i < para.size(); i++) {
		if (para[i][0] == key) {
			para[i][1] += x;
		}
	}
}
template <typename T>
double  gist<T>::med() {
	double sum = 0;
	for (int i = 0; i < para.size(); i++) {
		sum += para[i][1];
	}
	return sum / para.size();
}
template <typename T>
void gist<T>::print() {
	for (int i = 0; i < para.size(); i++) {
		for (int j = 0; j < 2; j++) {
			if (para[i][j] == key) {
				std::cout << para[i][j] << " ";
			}
		}
		std::cout << "\n";
	}
}
template <typename T>
size_t gist<T>::Count() const {
	return para.size();
}