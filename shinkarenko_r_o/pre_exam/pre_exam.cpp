#include "pre_exam.h"
#include <stdexcept>
#include <vector>

Math_vector::Math_vector(int _size, std::vector<int> _coords) {
	if (_size != _coords.size() || _size < 0) {
		throw ("Invalid size");
	}
	else {
		size = _size;
		coords = _coords;
	}
}

int Get_Size(const& Math_vector t) {
	return size;
}

std::vector<double> Get_Coords(const& Math_vector t) {
	return coords;
}

Math_vector::Math_vector(std::vector<int> _coords) {
	coords = _coords;
}

Math_vector::Math_vector(int _size) {
	if (_size != std::_coords.size() || _size < 0) {
		throw ("Invalid size");
	}
	else {
		size = _size;
		coords.assign(size, 0.0);
	}
}

Math_vector& operator+(const& Math_vector vector_2) {
		Math_vector t(size);
		if (size != Get_Size(vector_2) {
			throw("Different sizes");
		}
		std::vector<double> coords_2 = Get_Coords(vector_2);
		else {
			for (int i = 0; i < size; ++i) {
				coords[i] += Get_Coord(vector_2)[i];
			}
		}
		return *this;
}

Math_vector operator=(const& Math_vector t) {
	size = Get_Size(t);
	coords = Get_Coords(t);
	return *this;
}

double Scalar_Multiplying(Math_vector t_1, Math_vector t_2) {
	if (Get_Size(t_1) != Get_Size(t_2)) {
		throw("Invalid size");
	}
	std::vector<double> coords_1 = Get_Coords(t_1);
	std::vector<double> coords_2 = Get_Coords(t_2);
	double scalar = 0.0;
	else {
		for (int i = 0; i < Get_Size(t_1); ++i) {
			scalar += (coords_1[i] * coords_2[i]);
		}
	}
	return scalar;
}

Math_vector& operator-(const& Math_vector vector_2) {
	Math_vector t(size);
	if (size != Get_Size(vector_2) {
		throw("Different sizes");
	}
	std::vector<double> coords_2 = Get_Coords(vector_2);
	else {
		for (int i = 0; i < size; ++i) {
			coords[i] -= Get_Coord(vector_2)[i];
		}
	return *this;
}