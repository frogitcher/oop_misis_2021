#include <iostream>
#include "kr.h"

Rectangular:: Rectangular(int x1, int y1, int x2, int y2) {
	koord_x1 = x1;
	koord_y1 = y1;
	koord_x2 = x2;
	koord_y2 = y2;
}

Rectangular::Rectangular(const Rectangular& other) {
	koord_x1 = other.koord_x1;
	koord_y1 = other.koord_y1;
	koord_x2 = other.koord_x2;
	koord_y2 = other.koord_y2;
}


int Rectangular::Perimetr() const{
	return 2 * abs(koord_x2 - koord_x1) + 2 * abs(koord_y2 - koord_y1);
}

int Rectangular::Ploshad() const {
	return abs(koord_x2 - koord_x1) * abs(koord_y2 - koord_y1);
}

int Rectangular::Ploshad_of_both(const Rectangular& first, const Rectangular& second) const{
	if (first.koord_x1 <= second.koord_x1 < first.koord_x2) {
		if (first.koord_y1 <= second.koord_y1 <= first.koord_y2) {
			return abs(first.koord_x2 - second.koord_x1) * abs(first.koord_y2 - second.koord_y1);
		}
	}
	else if (second.koord_x1 <= first.koord_x1 < second.koord_x2) {
		if (second.koord_y1 <= first.koord_y1 < second.koord_y2) {
			return abs(second.koord_x2 - first.koord_x1) * abs(second.koord_y2 - first.koord_y1);
		}
	}
}



Rectangular Rectangular:: operator+(const Rectangular& other) {
	return *this += other;
}

Rectangular Rectangular:: operator-(const Rectangular& other) {
	return *this -= other;
}


Rectangular& Rectangular:: operator=(const Rectangular& other) {
	koord_x1 = other.koord_x1;
	koord_x1 = other.koord_y1;
	koord_x1 = other.koord_x2;
	koord_x1 = other.koord_y2;

	return *this;
}

Rectangular& Rectangular:: operator+=(const Rectangular& other) {
	koord_x1 = koord_x1 + other.koord_x1;
	koord_x1 = koord_x1 + other.koord_x1;
	koord_x1 = koord_x1 + other.koord_x1;
	koord_x1 = koord_x1 + other.koord_x1;

	return *this;
}

Rectangular& Rectangular:: operator-=(const Rectangular& other) {
	koord_x1 = koord_x1 + other.koord_x1;
	koord_x1 = koord_x1 + other.koord_x1;
	koord_x1 = koord_x1 + other.koord_x1;
	koord_x1 = koord_x1 + other.koord_x1;
	
	return *this;
}


bool Rectangular:: operator==(const Rectangular& other) {
	return (*this).Ploshad() == other.Ploshad();
}

bool Rectangular:: operator!=(const Rectangular& other) {
	return (*this).Perimetr() != other.Perimetr();
}
