#pragma once

class Rectangular {
public:
	Rectangular() = default;

	Rectangular(int x1, int y1, int x2, int y2);
	Rectangular(const Rectangular& _other);

	int Perimetr() const;
	int Ploshad() const;
	int Ploshad_of_both(const Rectangular& first, const Rectangular& second) const;

	Rectangular& operator=(const Rectangular& other);
	Rectangular& operator+=(const Rectangular& other);
	Rectangular& operator-=(const Rectangular& other);

	Rectangular operator+(const Rectangular& other);
	Rectangular operator-(const Rectangular& other);
	
	bool operator==(const Rectangular& other);
	bool operator!=(const Rectangular& other);

private:
	int koord_x1 = 0;
	int koord_y1 = 0;
	int koord_x2 = 0;
	int koord_y2 = 0;
};