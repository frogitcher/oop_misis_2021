#include "kr.h"

Vector::Vector(int[] idata) : data(idata), size(data.size())
{
}
Vector::Vector(Vector& other){
    for (int i=0,i<size;i++){
        data[i] = rhs.data[i];
    }
    size = other.size;
}
double& Vector::operator[](int i){
    return data[i];
}
double Vector::at(int i){
    return data[i];
}
Vector Vector::operator+(const Vector& rhs){
    int new_data = new double[size];
    for (int i=0,i<size;i++){
        new_data[i] = data[i] + rhs.data[i];
    }
    return Vector(new_data);
}
Vector Vector::operator-(const Vector& rhs){
    int new_data = new double[size];
    for (int i=0,i<size;i++){
        new_data[i] = data[i] - rhs.data[i];
    }
    return Vector(new_data);
}
Vector Vector::operator*(const double rhs){
    int new_data = new double[size];
    for (int i=0,i<size;i++){
        new_data[i] = data[i] * rhs;
    }
    return Vector(new_data);
}

Vector Vector::operator/(const double rhs){
    int new_data = new double[size];
    for (int i=0,i<size;i++){
        new_data[i] = data[i] / rhs;
    }
    return Vector(new_data);
}

Vector& Vector::operator+=(Vector& rhs){
    for (int i=0,i<size;i++){
        data[i] = data[i] + rhs.data[i];
    }
}
Vector& Vector::operator-=(Vector& rhs){
    for (int i=0,i<size;i++){
        data[i] = data[i] - rhs.data[i];
    }
}
Vector& Vector::operator*=(double rhs){
    for (int i=0,i<size;i++){
        data[i] = data[i] * rhs;
    }
}

Vector& Vector::operator/=(double rhs){
    for (int i=0,i<size;i++){
        data[i] = data[i] / rhs;
    }
}

bool Vector::operator==(Vector& rhs){
    for (int i=0,i<size;i++){
        if(data[i] != rhs.data[i]){
            return false;
        }
    }
    return true;
}
bool Vector::operator!=(Vector& rhs){
    return !(*this==rhs);
}

double Vector::Norm(){
    double ans=0;
    for (int i=0,i<size;i++){
        ans += data[i]**2;
    }
    return ans**0.5;
}
double Vector::Scal(Vector& rhs){
    double ans=0;
    for (int i=0,i<size;i++){
        ans += data[i]*rhs.data[i];
    }
    return ans;
}

Vector& Vector::operator=(Vector& rhs){
    int data = new double[size];
    for (int i=0,i<size;i++){
        new_data[i] = rhs.data[i];
    }

}
