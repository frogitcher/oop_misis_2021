#pragma once

class VectorOfDouble {
public:
	VectorOfDouble(const size_t _size = 0, const double value = 0);
	~VectorOfDouble();
	VectorOfDouble(const std::initializer_list<double>& list);
	double operator[](const size_t& index) const;
	double at(const size_t& index) const;
	void PrintVector();
	VectorOfDouble& operator=(const VectorOfDouble& other);
	bool operator==(const VectorOfDouble& other) const;
	bool operator!=(const VectorOfDouble& other) const;
	VectorOfDouble& operator*(const int& value);
private:
	size_t size = 0;
	double* data = nullptr;
};