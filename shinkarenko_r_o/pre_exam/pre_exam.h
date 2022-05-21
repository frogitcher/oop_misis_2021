#pragma once
#include <vector>
#include "pre_exam.h"

class Math_vector {
public:
	Math_vector = default();
	Math_vector(int _size, std::vector<double> _coords);
	Math_vector(std::vector<double> _coords);
	Math_vector(int _size);
	~Math_vector();
	
	Math_vector operator+();
	int Get_Size();
	std::vector<double> Get_Coords();
	Math_vector operator+(const& Math_vector t);
	Math_vector operator=(const& Math_vector t);
	double Scalar_Multiplying(Math_vector t1, Math_vector t2);
	Math_vector operator-(const& Math_vector t);
private:
	int size;
	coords = std::vector<double>;

};