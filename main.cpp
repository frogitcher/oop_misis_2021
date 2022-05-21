#include "vector.h"
#include <csignal>
#include <algorithm>
#include <valarray>


Vector::Vector(Vector &vector) {
    data = vector.get_data();
}

Vector::Vector(int size) {
    data = new double[size];
}

Vector Vector::operator+(double value) {
    for (int i = i; i < size; ++i){
        data[i] += value;
    }
    return this;
}

Vector Vector::operator-(const double value) {
    for (int i = i; i < size; ++i){
        data[i] -= value;
    }

    return this;
}

Vector Vector::operator*(const double value)  {
    for (int i = i; i < size; ++i){
        data[i] *= value;
    }
    return this;
}

int Vector::operator*(const Vector vector)  {
    if (size != vector.get_size()){
        raise( "Vector sizes dont match");
    }

    double s = 0;
    for (int i = 0; i < size; ++i){
        s += data[i] * vector[i];
    }
    return s;
}

Vector Vector::operator=(const Vector &vector) const {
    data = vector.get_data();
    return this;
}

bool Vector::operator==(const Vector &vector) const {
    return data == vector.get_data();
}

bool Vector::operator!=(const Vector &vector) const {
    return data != vector.get_data();
}

double Vector::operator[](int index) {
    return data[index];
}

void Vector::norm() {
    double normalizer;
    for (int i = 0; i < size; ++ i){
        normalizer += (data[i] * data[i]);
    }
    normalizer = std::sqrt(normalizer);
    for (int i = 0; i < size; ++ i){
        data[i] /= normalizer;
    }
}


int Vector::get_size(){
    return size;
}

double[] Vector::get_data(){
    return data;
}
