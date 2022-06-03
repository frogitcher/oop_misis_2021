#pragma once
#include <vector>

class vec {
private:
	unsigned _int64 size;
	std::vector <double> data;
public:
	//template 
	vec(unsigned _int64 size);
	vec(unsigned _int64 size, std::vector<double>& data);
	~vec();

	double& operator[](const unsigned _int64 rhs);

	vec operator+(const vec& rhs) const;
	vec operator-(const vec& rhs) const;
	vec operator*(const _int64& rhs) const;
	vec operator*(const vec& rhs) const;
	vec normal();

	vec operator=(const vec& other);
};