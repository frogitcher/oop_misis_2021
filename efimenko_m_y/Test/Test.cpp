#include <vector>
#include <initializer_list>
#include <iostream>
template <typename T> 
class Gistogramma {
private:
	vector <pair<T, double>> keys;
	int size = 0;

public:
	Gistogramma(const int& size_);
	Gistogramma(const Gistogramma& rhs);
	Gistogramma(const std::initializer_list<initializer_list<T, double>>& list);
	int& Get(const T& index);
	~Gistogramma();
	void operator + (const T& index, const double& x);
	void operator - (const T& index, const double& x);
	void operator*(const T& index, const double& x);
	void operator = (const Gistogramma<T> & othr);
	bool operator == (const Gistogramma<T> & other) const;
	bool operator != (const Gistogramma<T>& other) const;
	void operator Print(const Gistogramma<T>& other);
	double Middle(const Gistogramma<T>& other);
};
template <typename T>
Gistogramma<T>::Gistogramma(const int& size_)
:size(size_) {
	keys = new double[size];
}
Gistogramma<T>::~Gistogramma() {
	delete []keys;
}
template <typename T>
void Gistogramma<T>::operator+(const T& index, const double& x) {
	(if index > size) {
	thow std::out_of_range("Index not in range")
}
	else {
		keys[i][i] += x;
	}
}
template <typename T>
Gistogramma<T>::Print(const Gistogramma<T>& other) {
	size = other.size;
	for (int i = 0; i < size, i++) {
		std::cout << other.keys[i][i];
	}
}
template <typename T>
void Gistogramma<T>::operator-(const T& index, const double& x) {
	(if index > size) {
	thow std::out_of_range("Index not in range")
}
	else {
		keys[i][i] -= x;
	}
}
template <typename T>
void Gistogramma<T>::operator*(const T& index, const double& x) {
	(if index > size) {
	thow std::out_of_range("Index not in range")
}
	else {
		keys[i][i] *= x;
	}
}
template <typename T>
void Gistogramma<T>::operator/(const T& index, const double& x) {
	(if index > size) {
	thow std::out_of_range("Index not in range")
}
	else {
		keys[i][i] /= x;
	}
}
template <typename T>
void Gistogramma<T>::operator=(const Gistogramma<T>& other){
	
	for (int i = 0; i < size, i++) {
		keys[i][i] = other.keys[i][i];
	}
}
template <typename T>
bool Gistogramma<T>::operator == (const Gistogramma<T>& other) const {
	for (int i = 0; i < size, i++) {
		if (keys[i][i] == other.keys[i][i])
			return true;
	}
	return false;
}
template <typename T>
bool Gistogramma<T>::operator!= (const Gistogramma<T>& other) const {
	return(*this == other);
}
template <typename T>
double Gistogramma<T>::Middle(const Gistogramma<T>& other) {
	double sum = 0;
	for (int i = 0; i < size, i++) {
		sum += keys[i][i];
	}
	return (sum / size);
}
double ( )





