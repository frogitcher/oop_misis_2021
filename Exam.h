#pragma once
#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

template <typename T>
class Pram { //pryamougolnik
public:
	struct oct { //ugol
		T x, y;
		oct(x, y) {
			this.x = x;
			this.y = y;
		}
	};

	Pram(oct a, oct c); //po uglam
	Pram(T x1, T y1, T x2, T y2); //po uglam
	Pram(T x, T y, T h, T w); //po uglu i vysote i shirine
	Pram(const Pram& other); //po drugomu
	~Pram() = default;

	std::pair<T, T> getA() const;
	std::pair<T, T> getB() const;
	std::pair<T, T> getC() const;
	std::pair<T, T> getD() const;

	T getHight() const; //poluchit' wysotu
	T getWeith() const; //poluchit' shirinu
	T getDiag() const; //poluchit' dlinu diagonali

	void setA(T x1, T x2) const;
	void setB(T x1, T x2) const;
	void setC(T x1, T x2) const;
	void setD(T x1, T x2) const;

	void setHight(T value) const;
	void setWeith(T value) const;

	double Perim() const; //perimetr
	double AmPerim() const; //obshiy vneshniy perimetr
	double Area() const; //ploshad'
	double AmArea(const Pram& other) const; //obshaya ploshad'
	double CrossArea(const Pram& other) const; //ploshad' peresecheniya
	std::pair<std::pair<T, T>, std::pair<T, T>> CrossPoints(const Pram& other) const; //tochki peresecheniya

private:
	oct a, b, c, d;
	/*
	a(x1,y1)_____________b
		   |             |
		 h |             |
	 d(x,y)|_____________|c(x2,y2)
				  w
	*/
};

template <typename T>
Pram<T>::Pram(oct a, oct c){
	this->a = a;
	this->c = c;
	this->b.x = c.x;
	this->b.y = a.y;
	this->d.x = a.x;
	this->d.y = c.y;
}
template <typename T>
Pram<T>::Pram(T x1, T y1, T x2, T y2) {
	a.x = x1;
	a.y = y1;
	c.x = x2;
	c.y = y2;
	this->b.x = c.x;
	this->b.y = a.y;
	this->d.x = a.x;
	this->d.y = c.y;
}
template <typename T>
Pram<T>::Pram(T x, T y, T h, T w) {
	d.x = x;
	d.y = y;
	a.x = d.x;
	a.y = d.y + h;
	b.x = d.x + w;
	b.y = a.y;
	c.x = d.x + w;
	c.y = d.y;
}
template <typename T>
Pram<T>::Pram(const Pram& other) {
	this->a = other.a;
	this->b = other.b;
	this->c = other.c;
	this->d = other.d;
}

template <typename T>
std::pair<T, T> Pram<T>::getA() const {
	return std::make_pair(a.x, a.y);
}
template <typename T>
std::pair<T, T> Pram<T>::getB() const {
	return std::make_pair(b.x, b.y);
}
template <typename T>
std::pair<T, T> Pram<T>::getC() const {
	return std::make_pair(c.x, c.y);
}
template <typename T>
std::pair<T, T> Pram<T>::getD() const {
	return std::make_pair(d.x, d.y);
}

template <typename T>
T Pram<T>::getHight() const{
	return a.y - d.y;
}
template <typename T>
T Pram<T>::getWeith() const{
	return a.x - b.x;
}
template <typename T>
T Pram<T>::getDiag() const {
	return sqrt(getHight() * getHight + getWeith() * getWeith());
}

template <typename T>
void Pram<T>::setA(T x1, T x2) const {
	a.x = x1;
	a.y = x2;
	b.y = x2;
	d.x = x1;
}
template <typename T>
void Pram<T>::setB(T x1, T x2) const {
	b.x = x1;
	b.y = x2;
	a.y = x2;
	c.x = x1;
}
template <typename T>
void Pram<T>::setC(T x1, T x2) const {
	c.x = x1;
	c.y = x2;
	d.y = x2;
	b.x = x1;
}
template <typename T>
void Pram<T>::setD(T x1, T x2) const {
	d.x = x1;
	d.y = x2;
	c.y = x2;
	a.x = x1;
}

template <typename T>
void Pram<T>::setHight(T value) const {
	a.y += value / 2;
	b.y += value / 2;
	c.x += value / 2;
	d.x += value / 2;
}
template <typename T>
void Pram<T>::setWeith(T value) const {
	b.y += value / 2;
	c.y += value / 2;
	a.y -= value / 2;
	d.y -= value / 2;
}

template <typename T>
double Pram<T>::Perim() const {
	return getHight * 2 + getWeith * 2;
}

template <typename T>
double Pram<T>::Area() const {
	return getHight() * getWeith();
}

template <typename T>
std::pair<std::pair<T, T>, std::pair<T, T>> Pram<T>::CrossPoints(const Pram& other) const {
	std::pair<T, T> a1, a2;
	//...
}