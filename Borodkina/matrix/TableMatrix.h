#pragma once
#include <cstdint>
#include <initializer_list>
#include "BaseMatrix.h"

template <typename T>
class TableMatrix: public BaseMatrix<T>  {
    public:
    TableMatrix(int64_t r = 0, int64_t c = 0, T value = (T)0);
    TableMatrix(const TableMatrix<T>& other);
    TableMatrix(std::initializer_list<std::initializer_list<T>> list);
    ~TableMatrix();
    void Resize(int64_t r, int64_t c, T value = (T)0) override;
    T& Get(int64_t r, int64_t c) const override;
    T* operator[](int64_t r) const;
    TableMatrix<T> &operator+=(const TableMatrix<T>& other);
    TableMatrix<T> &operator-=(const TableMatrix<T>& other);
    TableMatrix<T> &operator*=(const TableMatrix<T>& other);
    TableMatrix<T> operator*(const TableMatrix<T>& other) const;
    TableMatrix<T> operator+(const TableMatrix<T>& other) const;
    TableMatrix<T> operator-(const TableMatrix<T>& other) const;
    TableMatrix<T>& operator=(const TableMatrix<T>& other);
    bool operator==(const TableMatrix<T>& other) const;
    bool operator!=(const TableMatrix<T>& other) const;

    private:
    T** data = nullptr;   
};
template <typename T>
TableMatrix<T>::TableMatrix(int64_t r, int64_t c, T value): BaseMatrix <T>(r, c)
{ 
    if (r < 0){
    throw "the number of rows of the matrix must be non-negative";
    }
    if (c < 0 ){
        throw "the number of columns of the matrix must be non-negative";
    }
    data = new T * [r];
   for (int i = 0; i < r; i++){
        data[i] = new T[c];
        std:: fill(data[i], data[i]+c, value);
   }
}
template <typename T>
TableMatrix<T>::TableMatrix(std::initializer_list<std::initializer_list<T>> list): BaseMatrix<T>(list.size(), list.begin()->size()) {
    for (int i = 0; i < this->num_rows; i++) {
        if ((list.begin() + i)->size() != this->num_cols) {
            throw ("such a matrix cannot be created");
        }
    }
    data = new T*[this->num_rows];
    for (int i = 0; i < this->num_rows; i++) {
        data[i] = new T[this->num_cols];
        std::copy((list.begin() + i)->begin(), (list.begin() + i)->end(), data[i]);
    }
}
template <typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& other):BaseMatrix <T>(other.num_rows, other.num_cols)
{ 
    delete[] data;
    *this = other;
}
template <typename T>
TableMatrix<T>::~TableMatrix(){
    for (int i = 0; i < this->num_rows; i++){
        delete[] data[i];
    }
    delete[] data;
}
template <typename T>
void TableMatrix<T>::Resize(int64_t r, int64_t c, T value){
if (r < 0 || c < 0){
    throw "the size of the matrix must be non negative";
}
    T** new_data = new T*[r];   
    for (int i = 0; i < r; i++){
    new_data[i] = new T[c];
    std:: fill(new_data[i], new_data[i]+c, value);
    }
delete[] data;
data = new_data;
this->num_cols = c;
this->num_rows = r;

}
template <typename T>
T& TableMatrix<T>::Get(int64_t r, int64_t c) const 
{
    if (r < 0 || r >= this->num_rows || c < 0 || c >= this->num_cols)
    {
        throw "pointer does not match with the size";
    }
        return data[r][c];
}
    template <typename T>
T* TableMatrix<T>::operator[](int64_t r) const 
{
    return data[r];
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator+=(const TableMatrix<T>& other) 
{
    if (this->num_rows != other.num_rows || this->num_cols != other.num_cols)
    {
        throw "addition cannot be performed";
    }
    for (int i = 0; i < this->num_rows; i++)
    {
        for (int j = 0; j < this->num_cols; j++)
        {
            data[i][j] += other.data[i][j];
        }
    }
    return *this;
}
    template <typename T>
TableMatrix<T>& TableMatrix<T>::operator-=(const TableMatrix<T>& other)  
{
    if (this->num_cols != other.num_cols || this->num_rows != other.num_rows)
    {
        throw "subtraction cannot be performed";
    }
    for (int i = 0; i < this->num_rows; i++)
    {
        for (int j = 0; j < this->num_cols; j++)
        {
            data[i][j] -= other.data[i][j];
        }
    }
    return *this;   
}
    template <typename T>
TableMatrix<T>& TableMatrix<T>::operator*=(const TableMatrix<T>& other) 
{
    if (this->num_cols != other.num_rows)
    {
        throw "multiplication cannot be performed";
    }
        T** new_data = new T*[this->num_rows];    
        for (int i = 0; i < this->num_rows; i++){
        new_data[i] = new T[other.num_cols];
        std:: fill(new_data[i], new_data[i]+other.num_cols, 0);
        }
    for (int i = 0; i < this->num_rows; i++)
    {
        for (int j = 0; j < other.num_cols; j++)
        {
            for (int k = 0; k < other.num_rows; k++){
            new_data[i][j] += data[i][k] * other.data[k][j];
            } 
        }
        delete[] data[i];
    }
    delete[] data;
    data = new_data;
    this->num_cols = other.num_cols;
    return *this;
}
	/*TableMatrix<T>& operator*=(const TableMatrix<T>& rhs) {
		if (col_ == rhs.row_) {
			TableMatrix temp(*this);
			resize(row_, rhs.col_);
			int r = 0;
			for (int i = 0; i < row_; i++) {
				for (int j = 0; j < col_; j++) {
					for (int k = 0; k < rhs.row_; k++) {
						data[i][j] += temp.data[i][k] * rhs.data[k][j];
					}
				}
			}
		}*/
template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T>& other) const
{
    return TableMatrix(*this) *= other;
}
    template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T>& other) const
{
    return TableMatrix(*this) += other;
}
    template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T>& other) const
{
    return TableMatrix(*this) -= other;
}
template <typename T>
TableMatrix<T>& TableMatrix<T>::operator=(const TableMatrix<T>& other)
{
Resize(other.num_rows, other.num_cols, (T)0);
for (int i = 0; i < other.num_rows; i++)
{
    std:: copy(other.data[i], other.data[i]+other.num_cols, data[i]);
}
return *this;
}
template <typename T>
bool TableMatrix<T>::operator==(const TableMatrix<T>& other) const{
    if (this->num_cols != other.num_cols || this->num_rows != other.num_rows) return false;
    for (int i = 0; i < this->num_rows; i++){
    if(! std::equal(data[i], data[i]+this->num_cols, other.data[i], other.data[i]+other.num_cols)){
        return false;
    }
}
    return true;
}
template <typename T>
bool TableMatrix<T>::operator!=(const TableMatrix<T>& other) const{
return (!(*this==other));
}

