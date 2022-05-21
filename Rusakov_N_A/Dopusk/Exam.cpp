#include <initializer_list>
#include <iostream>
#include "Exam.h"

int main()
{
    VectorOfDouble test(5, 1.2);
    test.PrintVector();//success 
    std::cout << std::endl;
    VectorOfDouble test1{ 1.2, 1.4, 1.7, 1.8 };
    test1.PrintVector();//success

    std::cout <<std::endl << test1[0] << " " << test1[3];
    std::cout << std::endl;
    VectorOfDouble test2;
    test2 = test1;
    test2.PrintVector();
    std::cout << std::endl << (test2 == test1);
    std::cout << std::endl << !(test2 != test1);

    std::cout << std::endl;
    VectorOfDouble test4;
    test4 = test1 * 10;
    test4.PrintVector();
    return 0;
}

VectorOfDouble::VectorOfDouble(const size_t _size, const double value)
{
    size = _size;
    data = new double[size];
    for (int i = 0; i < size; i++) {
        data[i] = value;
    }
}


VectorOfDouble::~VectorOfDouble()
{
    delete[] data;
}

VectorOfDouble::VectorOfDouble(const std::initializer_list<double>& list)
{
    size = list.size();
    data = new double[size];
    std::copy(list.begin(), list.end(), data);

}

double VectorOfDouble::operator[](const size_t& index) const
{
    return *(data + index);
}

double VectorOfDouble::at(const size_t& index) const
{
    if (index >= size) {
        throw std::invalid_argument("Index was out of range");
    }
    else {
        return *(data + index);
    }
}

void VectorOfDouble::PrintVector() {
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
}

VectorOfDouble& VectorOfDouble::operator=(const VectorOfDouble& other)
{
    size = other.size;
    if (data != nullptr) {
        delete[] data;
    }
    data = new double[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
    return *this;
}


bool VectorOfDouble::operator==(const VectorOfDouble& other) const
{
    if (size != other.size) {
        return 0;
    }
    for (int i = 0; i < size; i++) {
        if (data[i] != other.data[i]) {
            return 0;
        }
    }
    return 1;
}

bool VectorOfDouble::operator!=(const VectorOfDouble& other) const
{
    return !(*this == other);
}

VectorOfDouble& VectorOfDouble::operator*(const int& value) {
    double temp = double(value);
    for (int i = 0; i < size; i++) {
        data[i] *= value;
    }
    return *this;
}
