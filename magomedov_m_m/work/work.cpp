#pragma once
#include <stdexcept>
#include "work.h"
#include <vector>

Tample::Tample(size_t new_size,double value) :
	vector_size(new_size)
	 {
	for(int i=0;i<new_size;i++){
		data.push_back(value);
}
}
Tample::Tample(const std::initializer_list<double>& input_list) : vector_size(input_list.size())
{
	std::copy(input_list.begin(), input_list.end(),data);
}
Tample::Tample(const Tample& other): vector_size(other.Size()){
	std::copy(other.data.begin(), other.data.end(), data);
}
size_t Tample::Size() const {
	return vector_size;
}
double& Tample::at(size_t i)  {
	if (i >= vector_size) {
		throw std::invalid_argument("Incorrect index");
	}
	else {
		return data[i];
	}
}
double& Tample::operator[](size_t i) {
	at(i);
}
bool Tample::operator==(const Tample& other) const{
	if (vector_size == other.vector_size) {
		for (int i = 0;i < vector_size;i++) {
			if (data[i] != other.data[i]) {
				return false;
			}
			return true;
		}
	} 
	return false;
}
void Tample::operator=(const Tample& other) {
	std::vector<double> data;
	data = other.data;
}