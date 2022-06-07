#pragma once
#include <vector>
class Tample {
public:
	Tample();
	~Tample()=default;
	Tample(size_t length, double value);
	Tample(const Tample& other);
	Tample(const std::initializer_list<double>& input_list);

	size_t Size() const;
	double& operator[](size_t index) ;
	double& at(size_t i) ;

	bool operator==(const Tample& other) const;
	bool operator!=(const Tample& other) const;
	bool operator>=(const Tample& other) const;
	bool operator<=(const Tample& other) const;
	bool operator>(const Tample& other) const;
	bool operator<(const Tample& other) const;

	void operator=(const Tample& other);
private:
	size_t vector_size = 0;
	std::vector<double> data;
};