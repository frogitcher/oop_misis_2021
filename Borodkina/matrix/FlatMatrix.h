#pragma once
#include <cstdint>
#include <initializer_list>
#include "BaseMatrix.h"

template <typename T>
class FlatMatrix: public BaseMatrix<T> {
    public:
    FlatMatrix(int64_t r = 0, int64_t c = 0, T value = (T)0);
    FlatMatrix(const FlatMatrix<T>& other);
    FlatMatrix(std::initializer_list<std::initializer_list<T>> list);
    ~FlatMatrix();
    void Resize(int64_t r, int64_t c, T value = (T)0) override;
    T& Get(int64_t r, int64_t c) const override;
    T* operator[](int64_t r);
    FlatMatrix<T> &operator+=(const FlatMatrix<T>& other);
    FlatMatrix<T> &operator-=(const FlatMatrix<T>& other);
    FlatMatrix<T> &operator*=(const FlatMatrix<T>& other);
    FlatMatrix<T> operator-(const FlatMatrix<T>& other) const;
    FlatMatrix<T> operator+(const FlatMatrix<T>& other) const;
    FlatMatrix<T> operator*(const FlatMatrix<T>& other) const;
    FlatMatrix<T>& operator=(const FlatMatrix<T>& other);
    bool operator==(const FlatMatrix<T>& other) const;
    bool operator!=(const FlatMatrix<T>& other) const;
    private:
    T* data = nullptr;
};
template <typename T>
FlatMatrix<T>::FlatMatrix(int64_t r, int64_t c, T value): BaseMatrix <T>(r, c)
{
    if (r < 0)
    {
        throw "the number of rows of the matrix must be non-negative";
    }
    if (c < 0 ){
        throw "the number of columns of the matrix must be non-negative";
    }
    data = new T[r * c];
    std::fill(data, data + (r * c), value);
}
template <typename T>
FlatMatrix<T>::FlatMatrix(std::initializer_list<std::initializer_list<T>> list)
		: BaseMatrix<T>(list.size(), list.begin()->size()) {
		data = new T[this->num_rows * this->num_cols];
		for (int i = 0; i < this->num_rows; i++) {
			if ((list.begin() + i)->size() != this->num_cols) {
			    throw ("such a matrix cannot be created");
			}
        }
        for (int i = 0; i < this->num_rows; i++) {
            std::copy((list.begin() + i)->begin(), (list.begin() + i)->begin() + this->num_cols, data + (i * this->num_cols));
        }
}
template <typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T>& other)
{
    delete[] data;
    *this = other;
}
template <typename T>
FlatMatrix<T>::~FlatMatrix(){
    delete[] data;
}
template <typename T>
void FlatMatrix<T>::Resize(int64_t r, int64_t c, T value){
    if (r < 0 || c < 0){
        throw "the size of the matrix must be non negative";
    }
    T* new_data = new T[r * c];
    std::fill(new_data, new_data + r * c, value);
    delete[] data;
    data = new_data;
    this->num_cols = c;
    this->num_rows = r;
}
    template <typename T>
T& FlatMatrix<T>::Get(int64_t r, int64_t c) const {
    if (r < 0 || r >= this->num_rows || c < 0 || c >= this->num_cols){
        throw "pointer does not match with the size";
    }
    return *(data + this->num_cols * r + c);
}
template <typename T>
T* FlatMatrix<T>::operator[](int64_t r) {
    return data + this->num_cols * r;
}
template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator+=(const FlatMatrix<T>& other) {
    if (this->num_cols != other.num_cols || this->num_rows != other.num_rows){
        throw "addition cannot be performed";
    }
    for (int i = 0; i < this->num_rows * this->num_cols; i++){{
        data[i] += other.data[i];
        }
    }
    return *this;   
}
template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator-=(const FlatMatrix<T>& other) {
    if (this->num_cols != other.num_cols || this->num_rows != other.num_rows){
        throw "subtraction cannot be performed";
    }
    for (int i = 0; i < this->num_rows * this->num_cols; i++){{
        data[i] -= other.data[i];
        }
    }
    return *this;   
}
template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const FlatMatrix<T>& other) {
    if (this->num_cols != other.num_rows)
    {
        throw "multiplication cannot be performed";
    }
    T* new_data = new T[this->num_rows*this->num_cols];  
    std::fill(new_data, new_data+ this->num_rows * other.num_cols, T(0));  
    for (int i = 0; i < this->num_rows; i++)
    {
        for (int j = 0; j < other.num_cols; j++)
        {
            for (int k = 0; k < this->num_cols; k++){
            new_data[i*other.num_cols+j] += data[i*this->num_cols+k] * other.data[k*other.num_cols+j];
            } 
        }
    }
    delete[] data;
    data = new_data;
    this->num_cols = other.num_cols;
    return *this;
}
template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T>& other) const{
    return FlatMatrix(*this) -= other;
}
template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T>& other) const{
    return FlatMatrix(*this) += other;
}
template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& other) const{
    return FlatMatrix(*this) *= other;
}
template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator=(const FlatMatrix<T>& other)
{
    Resize(other.num_rows, other.num_cols);
    std::copy(other.data, other.data + other.num_cols * other.num_rows, data);
    this->num_cols = other.num_cols;
    this->num_rows = other.num_rows;
    return *this;
}
template <typename T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T>& other) const{
        if (this->num_cols != other.num_cols || this->num_rows != other.num_rows || 
        !(std::equal(data, data+this->num_cols*this->num_rows, other.data, other.data+other.num_cols*other.num_rows))){
        return false;
    }
    return true;
}
template <typename T>
bool FlatMatrix<T>::operator!=(const FlatMatrix<T>& other) const{
    return (!(*this==other));
}