#pragma once
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
using std::size_t;
using namespace std;

template <typename T>
class BaseMatrix
{
public:
    BaseMatrix() = default;
    BaseMatrix(size_t row, size_t col);
    virtual void Resize(size_t row, size_t col, const T& val = {}) = 0;
    virtual T& Get(size_t row, size_t col) const = 0;
    virtual T* operator[](size_t row) const = 0;
    virtual ~BaseMatrix() = 0;
protected:
    size_t rows = 0;
    size_t cols = 0;
};

template <typename T>
BaseMatrix<T>::BaseMatrix(size_t row, size_t col) : rows(row), cols(col)
{
    if (row + col > 0 && row * col == 0)
        throw std::logic_error("if one dimention is zero other also should be zero");
}


template <typename T>
BaseMatrix<T>::~BaseMatrix()
{
    rows = 0;
    cols = 0;
}

template <typename T>
class FlatMatrix : public BaseMatrix<T>
{
public:
    FlatMatrix() = default;
    FlatMatrix(size_t row, size_t col, const T& val = {});
    FlatMatrix(const std::initializer_list<std::initializer_list<T>>& matrix);
    FlatMatrix(const FlatMatrix<T>& other);
    ~FlatMatrix();

    void Resize(size_t row, size_t col, const T& val = {});
    size_t Cols() const;
    size_t Rows() const;
    T& Get(size_t row, size_t col) const;
    T* operator[](size_t row) const;

    FlatMatrix<T> operator+(const FlatMatrix<T>& rhs) const;
    FlatMatrix<T> operator-(const FlatMatrix<T>& rhs) const;
    FlatMatrix<T> operator*(const FlatMatrix<T>& rhs) const;
    FlatMatrix<T> operator+(const T& rhs) const;
    FlatMatrix<T> operator-(const T& rhs) const;
    FlatMatrix<T> operator*(const T& rhs) const;

    FlatMatrix<T>& operator+=(const FlatMatrix<T>& rhs);
    FlatMatrix<T>& operator-=(const FlatMatrix<T>& rhs);
    FlatMatrix<T>& operator*=(const FlatMatrix<T>& rhs);
    FlatMatrix<T>& operator+=(const T& rhs);
    FlatMatrix<T>& operator-=(const T& rhs);
    FlatMatrix<T>& operator*=(const T& rhs);

    FlatMatrix<T>& operator=(const FlatMatrix<T>& rhs);
    bool operator==(const FlatMatrix<T>& rhs) const;
    bool operator!=(const FlatMatrix<T>& rhs) const;
private:
    T* data = nullptr;
    using BaseMatrix<T>::rows;
    using BaseMatrix<T>::cols;
    void Rebuild(size_t row, size_t col);
    void Clear();
};


template <typename T>
class TableMatrix : public BaseMatrix<T>
{
public:
    TableMatrix() = default;
    TableMatrix(size_t row, size_t col, const T& val = {});
    TableMatrix(const std::initializer_list<std::initializer_list<T>>& matrix);
    TableMatrix(const TableMatrix<T>& other);
    ~TableMatrix();

    void Resize(size_t row, size_t col, const T& val = {});
    size_t Cols() const;
    size_t Rows() const;
    T& Get(size_t row, size_t col) const;
    T* operator[](size_t index) const;

    TableMatrix<T> operator+(const TableMatrix<T>& rhs) const;
    TableMatrix<T> operator-(const TableMatrix<T>& rhs) const;
    TableMatrix<T> operator*(const TableMatrix<T>& rhs) const;
    TableMatrix<T> operator+(const T& rhs) const;
    TableMatrix<T> operator-(const T& rhs) const;
    TableMatrix<T> operator*(const T& rhs) const;

    TableMatrix<T>& operator+=(const TableMatrix<T>& rhs);
    TableMatrix<T>& operator-=(const TableMatrix<T>& rhs);
    TableMatrix<T>& operator*=(const TableMatrix<T>& rhs);
    TableMatrix<T>& operator+=(const T& rhs);
    TableMatrix<T>& operator-=(const T& rhs);
    TableMatrix<T>& operator*=(const T& rhs);

    TableMatrix<T>& operator=(const TableMatrix<T>& rhs);
    bool operator==(const TableMatrix<T>& rhs) const;
    bool operator!=(const TableMatrix<T>& rhs) const;
private:
    T** data = nullptr;
    using BaseMatrix<T>::cols;
    using BaseMatrix<T>::rows;
    void Rebuild(size_t row, size_t col);
    void Clear();
};

template <typename T>
FlatMatrix<T>::FlatMatrix(size_t row, size_t col, const T& val) : BaseMatrix<T>(row, col)
{
    data = new T[row * col];
    std::fill(data, data + row * col, val);
}

template <typename T>
FlatMatrix<T>::FlatMatrix(const std::initializer_list<std::initializer_list<T>>& matrix)
    : BaseMatrix<T>(matrix.size(), matrix.begin()->size())
{
    data = new T[cols * rows];
    int it = 0;
    for (auto& row : matrix)
    {
        if (row.size() != cols)
        {
            Clear();
            throw std::logic_error("number of elements in each row must be the same");
        }
        std::copy(row.begin(), row.end(), data + cols * it);
        ++it;
    }
}

template <typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T>& other) : BaseMatrix<T>(other.rows, other.cols)
{
    data = new T[cols * rows];
    for (int p = 0; p < other.rows * other.cols; p += other.cols)
    {
        std::copy(other.data + p, other.data + p + other.cols, data + p);
    }
}

template <typename T>
FlatMatrix<T>::~FlatMatrix()
{
    Clear();
}

template <typename T>
void FlatMatrix<T>::Resize(size_t row, size_t col, const  T& val)
{
    Rebuild(row, col);
    for (int r = std::max((int)rows - 1, 0); r < row; r++)
    {
        for (int c = std::max((int)cols - 1, 0); c < col; c++)
        {
            data[r * col + c] = val;
        }
    }
    rows = row;
    cols = col;
}

template <typename T>
size_t FlatMatrix<T>::Rows() const
{
    return rows;
}

template <typename T>
size_t FlatMatrix<T>::Cols() const
{
    return cols;
}

template <typename T>
T& FlatMatrix<T>::Get(size_t row, size_t col) const
{
    if (row < 0 || rows <= row || col < 0 || cols <= col)
        throw std::out_of_range("matrix index out of range");
    return *(data + cols * row + col);
}

template <typename T>
T* FlatMatrix<T>::operator[](size_t row) const
{
    return data + row * cols;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T>& rhs) const
{
    if (cols != rhs.cols || rows != rhs.rows)
        throw std::logic_error("you are not able to sum matrixs with different dimentions");

    FlatMatrix<T> res(*this);
    for (int i = 0; i < rows * cols; i++)
        res.data[i] += rhs.data[i];
    return res;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T>& rhs) const
{
    if (cols != rhs.cols || rows != rhs.rows)
        throw std::logic_error("you are not able to sum matrices with different dimentions");

    FlatMatrix<T> res(*this);
    for (int i = 0; i < rows * cols; i++)
        res.data[i] -= rhs.data[i];
    return res;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& rhs) const
{
    if (cols != rhs.cols)
        throw std::logic_error("you can product this matrices");
    FlatMatrix<T> res(rows, rhs.cols, {});
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rhs.cols; j++)
            for (int k = 0; k < cols; k++)
                res[i][j] += (*this)[i][k] * rhs[k][j];
    return res;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const T& rhs) const
{
    return *this + FlatMatrix(rows, cols, rhs);
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const T& rhs) const
{
    return *this - FlatMatrix(rows, cols, rhs);
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const T& rhs) const
{
    FlatMatrix<T> res(*this);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[i][j] *= rhs;
    return res;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator+=(const FlatMatrix<T>& rhs)
{
    *this = *this + rhs;
    return *this;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator-=(const FlatMatrix<T>& rhs)
{
    *this = *this - rhs;
    return *this;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const FlatMatrix<T>& rhs)
{
    *this = *this * rhs;
    return *this;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator+=(const T& rhs)
{
    *this = *this + rhs;
    return *this;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator-=(const T& rhs)
{
    *this = *this - rhs;
    return *this;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator*=(const T& rhs)
{
    *this = *this * rhs;
    return *this;
}

template <typename T>
FlatMatrix<T>& FlatMatrix<T>::operator=(const FlatMatrix<T>& rhs)
{
    Rebuild(rhs.rows, rhs.cols);
    rows = rhs.rows;
    cols = rhs.cols;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            data[i][j] = rhs.data[i][j];
    return *this;
}

template <typename T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T>& rhs) const
{
    if (rows != rhs.rows || cols != rhs.cols)
        return false;
    return std::equal(data, data + rows * cols, rhs.data);
}

template <typename T>
bool FlatMatrix<T>::operator!=(const FlatMatrix<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
void FlatMatrix<T>::Rebuild(size_t row, size_t col)
{
    if (row + col > 0 && row * col == 0)
        throw std::logic_error("if one dimention is zero other also should be zero");
    T* new_data = new T[row * col];
    for (int r = 0; r < std::min(row, rows); r++)
        std::copy(data + cols * r, data + (cols + 1) * r, new_data + col * r);
    delete[] data;
    data = nullptr;
    data = new_data;
}

template <typename T>
void FlatMatrix<T>::Clear()
{
    delete[] data;
    data = nullptr;
    cols = 0;
    rows = 0;
}

template <typename T>
TableMatrix<T>::TableMatrix(size_t row, size_t col, const T& val) 
: BaseMatrix<T>(row, col)
{
    data = new T * [row];
    for (int r = 0; r < row; r++)
    {
        data[r] = new T[col];
        std::fill(data[r], data[r] + col, val);
    }
}

template <typename T>
TableMatrix<T>::TableMatrix(const std::initializer_list<std::initializer_list<T>>& matrix)
: BaseMatrix<T>(matrix.size(), matrix.begin()->size())
{
    data = new T*[rows];
    for (int i = 0; i < rows; i++)
        data[i] = new T[cols];
    int it = 0;
    for (auto& row : matrix)
    {
        if (row.size() != cols)
        {
            Clear();
            throw std::logic_error("number of elements in each row must be the same");
        }
        std::copy(row.begin(), row.end(), data[it]);
        ++it;
    }
}

template <typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& other)
: BaseMatrix<T>(other.rows, other.cols)
{
    data = new T * [rows];
    for (int r = 0; r < rows; r++)
    {
        data[r] = new T[cols];
        std::copy(other.data[r], other.data[r] + cols, data[r]);
    }
}
template <typename T>
TableMatrix<T>::~TableMatrix()
{
    Clear();
}

template <typename T>
void TableMatrix<T>::Resize(size_t row, size_t col, const T& val)
{
    Rebuild(row, col);
    for (int r = std::max((int)rows - 1, 0); r < row; r++)
    {
        for (int c = std::max((int)cols - 1, 0); c < col; c++)
        {
            data[r][c] = val;
        }
    }
    rows = row;
    cols = col;
}

template <typename T>
size_t TableMatrix<T>::Rows() const
{
    return rows;
}

template <typename T>
size_t TableMatrix<T>::Cols() const
{
    return cols;
}

template <typename T>
T& TableMatrix<T>::Get(size_t row, size_t col) const
{
    if (row < 0 || rows <= row || col < 0 || cols <= col)
        throw std::out_of_range("matrix index out of range");
    return data[row][col];
}

template <typename T>
T* TableMatrix<T>::operator[](size_t row) const
{
    return data[row];
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T>& rhs) const
{
    if (cols != rhs.cols || rows != rhs.rows)
        throw std::logic_error("you are not able to sum matrixs with different dimentions");

    TableMatrix<T> res(*this);
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            res.data[r][c] += rhs.data[r][c];
    return res;
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T>& rhs) const
{
    if (cols != rhs.cols || rows != rhs.rows)
        throw std::logic_error("you are not able to sum matrices with different dimentions");

    TableMatrix<T> res(*this);
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            res.data[r][c] -= rhs.data[r][c];
    return res;
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T>& rhs) const
{
    if (cols != rhs.cols)
        throw std::logic_error("you can product this matrices");
    TableMatrix<T> res(rows, rhs.cols, T{});
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rhs.cols; j++)
            for (int k = 0; k < cols; k++)
                res.data[i][j] += data[i][k] * rhs.data[k][j];
    return res;
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const T& rhs) const
{
    return *this + TableMatrix(rows, cols, rhs);
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const T& rhs) const
{
    return *this - TableMatrix(rows, cols, rhs);
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const T& rhs) const
{
    TableMatrix<T> res(*this);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res.data[i][j] *= rhs;
    return res;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator+=(const TableMatrix<T>& rhs)
{
    *this = *this + rhs;
    return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator-=(const TableMatrix<T>& rhs)
{
    *this = *this - rhs;
    return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator*=(const TableMatrix<T>& rhs)
{
    *this = *this * rhs;
    return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator+=(const T& rhs)
{
    *this = *this + rhs;
    return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator-=(const T& rhs)
{
    *this = *this - rhs;
    return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator*=(const T& rhs)
{
    *this = *this * rhs;
    return *this;
}

template <typename T>
TableMatrix<T>& TableMatrix<T>::operator=(const TableMatrix<T>& rhs)
{
    Rebuild(rhs.rows, rhs.cols);
    rows = rhs.rows;
    cols = rhs.cols;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            data[i][j] = rhs.data[i][j];
    return *this;
}

template <typename T>
bool TableMatrix<T>::operator==(const TableMatrix<T>& rhs) const
{
    if (rows != rhs.rows || cols != rhs.cols)
        return false;
    for (int r = 0; r < rows; r++)
        if (!std::equal(data[r], data[r] + cols, rhs.data[r]))
            return false;
    return true;
}

template <typename T>
bool TableMatrix<T>::operator!=(const TableMatrix<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
void TableMatrix<T>::Rebuild(size_t row, size_t col)
{
    if (row + col > 0 && row * col == 0)
        throw std::logic_error("if one dimention is zero other also should be zero");
    T** new_data = new T*[row];
    for (int r = 0; r < row; r++)
        new_data[r] = new T[col]{};
    for (int r = 0; r < std::min(row,rows); r++)
        std::copy(data[r], data[r] + std::min(col,cols), new_data[r]);

    for (int r = 0; r < rows; r++)
    {
        delete[] data[r];
        data[r] = nullptr;
    }
    delete[] data;
    data = new_data;
}


template <typename T>
void TableMatrix<T>::Clear()
{
    for (int r = 0; r < rows; r++)
    {
        delete[] data[r];
        data[r] = nullptr;
    }
    rows = 0;
    cols = 0;
}
