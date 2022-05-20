#include <initializer_list>
#include <stdexcept>
#include <algorithm>

template <class T>
class BaseMatrix{

public:
    BaseMatrix(size_t row_, size_t col_, T value = 0);
    BaseMatrix(std::initializer_list<std::initializer_list<T>> matrix);
    BaseMatrix(const BaseMatrix<T>& matrix);
    virtual ~BaseMatrix() = 0;

    virtual void Resize(size_t rows, size_t cols) = 0;
    virtual T& Get(size_t row, size_t col) const = 0;
    virtual T* operator[](size_t index) const = 0;

    size_t Row() const;
    size_t Col() const;

protected:
    size_t num_rows = 0;
    size_t num_cols = 0;
};


template <class T>
class FlatMatrix
    : public BaseMatrix<T>{

public:
    FlatMatrix(size_t row_, size_t col_, T value = 0);
    FlatMatrix(std::initializer_list<std::initializer_list<T>> matrix);
    FlatMatrix(const FlatMatrix<T>& matrix);
    ~FlatMatrix();

    void Resize(size_t row, size_t col);
    T& Get(size_t row, size_t col) const;
    T* operator[](size_t index) const;
    FlatMatrix<T> operator+(const FlatMatrix<T>& rhs) const;
    FlatMatrix<T> operator+(const T& rhs) const;
    FlatMatrix<T> operator-(const FlatMatrix<T>& rhs) const;
    FlatMatrix<T> operator-(const T& rhs) const;
    FlatMatrix<T> operator*(const FlatMatrix<T>& rhs) const;
    FlatMatrix<T> operator*(const T& rhs) const;
    void operator=(const FlatMatrix<T>& rhs);
    bool operator==(const FlatMatrix<T>& matrix) const;
    bool operator!=(const FlatMatrix<T>& matrix) const;

private:
    void Relocation(size_t row, size_t col);
    T* data = nullptr;
};

template <typename T>
FlatMatrix<T> operator+(const T& lhs, const FlatMatrix<T>& rhs);

template <typename T>
FlatMatrix<T> operator-(const T& lhs, const FlatMatrix<T>& rhs);

template <typename T>
FlatMatrix<T> operator*(const T& lhs, const FlatMatrix<T>& rhs);

template <class T>
class TableMatrix
    : public BaseMatrix<T>{

public:
    TableMatrix(size_t row_, size_t col_, T value = 0);
    TableMatrix(std::initializer_list<std::initializer_list<T>> matrix);
    TableMatrix(const TableMatrix<T>& matrix);
    ~TableMatrix();

    void Resize(size_t row, size_t col);
    T& Get(size_t row, size_t col) const;
    T* operator[](size_t index) const;
    TableMatrix<T> operator+(const TableMatrix<T>& rhs) const;
    TableMatrix<T> operator+(const T& rhs) const;
    TableMatrix<T> operator-(const TableMatrix<T>& rhs) const;
    TableMatrix<T> operator-(const T& rhs) const;
    TableMatrix<T> operator*(const TableMatrix<T>& rhs) const;
    TableMatrix<T> operator*(const T& rhs) const;
    void operator=(const TableMatrix<T>& rhs);
    bool operator==(const TableMatrix<T>& matrix) const;
    bool operator!=(const TableMatrix<T>& matrix) const;

private:
    void Relocation (size_t row, size_t col);
    T** data = nullptr;
};

template <typename T>
TableMatrix<T> operator+(const T& lhs, const TableMatrix<T>& rhs);

template <typename T>
TableMatrix<T> operator-(const T& lhs, const TableMatrix<T>& rhs);

template <typename T>
TableMatrix<T> operator*(const T& lhs, const TableMatrix<T>& rhs);

//-----------------------------------------------------------------------------------------------------------------------------

template <typename T>
BaseMatrix<T>::BaseMatrix(size_t row_, size_t col_, T value)
    : num_rows(row_)
    , num_cols(col_){
}

template <typename T>
BaseMatrix<T>::BaseMatrix(std::initializer_list<std::initializer_list<T>> matrix)
    : num_rows(matrix.size())
    , num_cols(matrix.begin()->size()){
        for (auto i : matrix){
            if (i.size() != num_cols){
                throw std::invalid_argument("impossible to create a matrix");
                num_rows = 0;
                num_cols = 0;
                break;
            }
        }
}

template <typename T>
BaseMatrix<T>::BaseMatrix(const BaseMatrix<T>& matrix)
    : num_rows(matrix.num_rows)
    , num_cols(matrix.num_cols){
}

template <typename T>
BaseMatrix<T>::~BaseMatrix(){ //ЧВ деструктор, так реализ.?
    num_rows = 0;
    num_cols = 0;
}

template <typename T>
size_t BaseMatrix<T>::Row() const{
    return num_rows;
}

template <typename T>
size_t BaseMatrix<T>::Col() const{
    return num_cols;
}

//-----------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
FlatMatrix<T>::FlatMatrix(size_t row_, size_t col_, T value)
    : BaseMatrix<T>(row_, col_){
          data = new T[row_ * col_];
          std::fill(data, data + row_ * col_, value);
}

template <typename T>
FlatMatrix<T>::FlatMatrix(std::initializer_list<std::initializer_list<T>> matrix)
    : BaseMatrix<T>(matrix){
        data = new T[this -> num_cols * this -> num_cols];
        size_t index = 0;
        for (auto i : matrix){
            for (auto j : i){
                data[index] = j;
                ++index;
            }
        }
}

template <typename T>
FlatMatrix<T>::FlatMatrix(const FlatMatrix<T>& matrix)
    : BaseMatrix<T>(matrix){
        data = new T[this -> num_rows * this -> num_cols];
        for (int i=0; i < this -> num_rows * this -> num_cols; ++i){
            data[i] = matrix.data[i];
        }
}

template <typename T>
FlatMatrix<T>::~FlatMatrix(){
    delete[]data;
}

template <typename T>
void FlatMatrix<T>::Relocation(size_t row, size_t col){
    T* new_data = new T[row * col];
    for (int i=0; i < std::min(this -> num_rows, row); ++i){
        for (int j=0; j < this -> num_cols; ++j){
            new_data[i * col + j] = data[i * this -> num_cols + j];
        }
    }
    delete[]data;
    data = new_data;
}

template <typename T>
void FlatMatrix<T>::Resize(size_t row, size_t col){
    if (col > this -> num_cols || row > this -> num_rows){
        Relocation(row, col);
    }
    BaseMatrix<T>::num_rows = row;
    BaseMatrix<T>::num_cols = col;
}

template <typename T>
T& FlatMatrix<T>::Get(size_t row, size_t col) const{
    if (row > (this -> num_rows - 1) || col > (this -> num_cols - 1)){
        throw std::invalid_argument("invalid index");
    } else{
        return data[(this -> num_cols * row + col)];
    }
}

template <typename T>
T* FlatMatrix<T>::operator[](size_t index) const{
    if (index > (this -> num_rows - 1)){
        throw std::invalid_argument("invalid index");
    } else{
        return data + (this -> num_cols * index);
    }
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const FlatMatrix<T>& rhs) const{
    if (rhs.num_rows != this -> num_rows || rhs.num_cols != this -> num_cols){
        throw std::invalid_argument("invalid argument");
    } else{
        FlatMatrix<T> rhs_copy(rhs);
        for (int i=0; i < this -> num_rows * this -> num_cols; ++i){
            rhs_copy.data[i] += data[i];
        }
        return rhs_copy;
    }
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator+(const T& rhs) const{
    if (this -> num_rows != this -> num_cols){
        throw std::invalid_argument("num_rows must be equal to num_cols");
    } else{
        FlatMatrix<T> this_copy(*this);
        for (int i=0; i < this -> num_rows * this -> num_cols; i += (this -> num_cols + 1)){
            this_copy.data[i] += rhs;
        }
        return this_copy;
    }
}

template <typename T>
FlatMatrix<T> operator+(const T& lhs, const FlatMatrix<T>& rhs){
    return rhs + lhs;
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const FlatMatrix<T>& rhs) const{
    return *this + rhs * (-1);
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator-(const T& rhs) const{
    return *this + rhs * (-1);
}

template <typename T>
FlatMatrix<T> operator-(const T& lhs, const FlatMatrix<T>& rhs){
    return rhs + lhs * (-1);
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const FlatMatrix<T>& rhs) const{
    if (this -> num_cols != rhs.num_rows){
        throw std::invalid_argument("impossible to multiply");
    } else{
        FlatMatrix<T> answer(this -> num_rows, rhs.num_cols);
        size_t number_row = 0;
        size_t number_col = 0;
        for (size_t i=0; i < this -> num_rows * rhs.num_cols; ++i){
            number_col = i % (rhs.num_cols);
            number_row = i / (rhs.num_cols);
            T value = 0;
            size_t index_lhs = (this -> num_cols) * number_row;
            size_t index_rhs = number_col;
            for (int j=0; j < this -> num_cols; ++j){
                value += data[index_lhs] * rhs.data[index_rhs];
                ++index_lhs;
                index_rhs += rhs.num_cols;
            }
            answer.data[i] = value;
        }
        return answer;
    }
}

template <typename T>
FlatMatrix<T> FlatMatrix<T>::operator*(const T& rhs) const{
    FlatMatrix<T> this_copy(*this);
    for (int i=0; i < this -> num_rows * this -> num_cols; ++i){
        this_copy.data[i] *= rhs;
    }
    return this_copy;
}

template <typename T>
FlatMatrix<T> operator*(const T& lhs, const FlatMatrix<T>& rhs){
    return rhs * lhs;
}

template <typename T>
void FlatMatrix<T>::operator=(const FlatMatrix<T>& rhs){
    Resize(rhs.num_rows, rhs.num_cols);
    for (int i=0; i < (this -> num_rows) * (this -> num_cols); ++i){
        data[i] = rhs.data[i];
    }
}

template <typename T>
bool FlatMatrix<T>::operator==(const FlatMatrix<T>& matrix) const{
    if (this -> num_rows == matrix.num_rows && this -> num_cols == matrix.num_cols){
        for (int i=0; i < this -> num_rows * this -> num_cols; ++i){
            if (data[i] != matrix.data[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool FlatMatrix<T>::operator!=(const FlatMatrix<T>& matrix) const{
    return !(*this == matrix);
}

//-------------------------------------------------------------------------------------------------------------------------------------------


template <typename T>
TableMatrix<T>::TableMatrix(size_t row_, size_t col_, T value)
    : BaseMatrix<T>(row_, col_){
        data = new T*[row_];
        for (int i=0; i < row_; ++i){
            data[i] = new T[col_];
            std::fill(data[i], data[i] + col_, value);
        }
}

template <typename T>
TableMatrix<T>::TableMatrix(std::initializer_list<std::initializer_list<T>> matrix)
    : BaseMatrix<T>(matrix){
        data = new T*[this -> num_rows];
        size_t count_row = 0;
        size_t count_col = 0;
        for (auto i : matrix){
            data[count_row] = new T[this -> num_cols];
            for (auto j : i){
                data[count_row][count_col] = j;
                ++count_col;
            }
            ++count_row;
            count_col = 0;
        }
}

template <typename T>
TableMatrix<T>::TableMatrix(const TableMatrix<T>& matrix)
    : BaseMatrix<T>(matrix){
        data = new T*[this -> num_rows];
        for (int i=0; i < this -> num_rows; ++i){
            data[i] = new T[this -> num_cols];
            for (int j=0; j < this -> num_cols; ++j){
                data[i][j] = matrix.data[i][j];
            }
        }
}

template <typename T>
TableMatrix<T>::~TableMatrix(){
    for (int i=0; i < this -> num_rows; ++i){
        delete[]data[i];
    }
    delete[]data;
    this -> num_rows = 0;
    this -> num_cols = 0;
}

template <typename T>
void TableMatrix<T>::Relocation(size_t row, size_t col){
    T** new_data = new T*[row];
    for (int i=0; i < row; ++i){
        new_data[i] = new T[col];
    }
    for (int i=0; i < std::min(this -> num_rows, row); ++i){
        for (int j=0; j < std::min(this -> num_cols, col); ++j){
            new_data[i][j] = data[i][j];
        }
    }
    for (int i=0; i < this -> num_rows; ++i){
        delete[]data[i];
    }
    delete[]data;
    data = new_data;
}

template <typename T>
void TableMatrix<T>::Resize(size_t row, size_t col){
    if (row > this -> num_rows || col > this -> num_cols){
        Relocation(row, col);
    }
    this -> num_rows = row;
    this -> num_cols = col;
}

template <typename T>
T& TableMatrix<T>::Get(size_t row, size_t col) const{
    if (row > (this -> num_rows - 1) || col > (this -> num_cols - 1)){
        throw std::invalid_argument("invalid index");
    } else{
        return data[row][col];
    }
}

template <typename T>
T* TableMatrix<T>::operator[](size_t index) const{
    if (index > (this -> num_rows - 1)){
        throw std::invalid_argument("invalid index");
    } else{
        return data[index];
    }
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const TableMatrix<T>& rhs) const{
    if (rhs.num_rows != this -> num_rows || rhs.num_cols != this -> num_cols){
        throw std::invalid_argument("invalid argument");
    } else{
        TableMatrix<T> rhs_copy(rhs);
        for (int i=0; i < this -> num_rows; ++i){
            for (int j=0; j < this -> num_cols; ++j){
                rhs_copy.data[i][j] += data[i][j];
            }
        }
        return rhs_copy;
    }
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator+(const T& rhs) const{
    if (this -> num_cols != this -> num_rows){
        throw std::invalid_argument("num_rows must be equal to num_cols");
    } else{
        TableMatrix<T> this_copy(*this);
        for (int i=0; i < this -> num_rows; ++i){
            this_copy.data[i][i] += rhs;
        }
        return this_copy;
    }
}

template <typename T>
TableMatrix<T> operator+(const T& lhs, const TableMatrix<T>& rhs){
    return rhs + lhs;
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const TableMatrix<T>& rhs) const{
    return *this + rhs * (-1);
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator-(const T& rhs) const{
    return *this + rhs * (-1);
}

template <typename T>
TableMatrix<T> operator-(const T& lhs, const TableMatrix<T>& rhs){
    return rhs + lhs * (-1);
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const TableMatrix<T>& rhs) const{
    if (this -> num_cols != rhs.num_rows){
        throw std::invalid_argument("impossible to multiply");
    } else{
        TableMatrix<T> answer(this -> num_rows, rhs.num_cols);
        for (int i=0; i < answer.num_rows; ++i){
            for (int j=0; j < answer.num_cols; ++j){
                size_t index = 0;
                while (index < this -> num_cols){
                    answer[i][j] += (data[i][index] * rhs.data[index][j]);
                    ++index;
                }
            }
        }
        return answer;
    }
}

template <typename T>
TableMatrix<T> TableMatrix<T>::operator*(const T& rhs) const{
    TableMatrix<T> this_copy(*this);
    for (int i=0; i < this -> num_rows; ++i){
        for (int j=0; j < this -> num_cols; ++j){
            this_copy.data[i][j] *= rhs;
        }
    }
    return this_copy;
}

template <typename T>
TableMatrix<T> operator*(const T& lhs, const TableMatrix<T>& rhs){
    return rhs * lhs;
}

template <typename T>
void TableMatrix<T>::operator=(const TableMatrix<T>& rhs){
    Resize(rhs.num_rows, rhs.num_cols);
    for (int i=0; i < this -> num_rows; ++i){
        for (int j=0; j < this -> num_cols; ++j){
            data[i][j] = rhs.data[i][j];
        }
    }
}

template <typename T>
bool TableMatrix<T>::operator==(const TableMatrix<T>& matrix) const{
    if (this -> num_rows == matrix.num_rows && this -> num_cols == matrix.num_cols){
        for (int i=0; i < this -> num_rows; ++i){
            for (int j=0; j < this -> num_cols; ++j){
                if (data[i][j] != matrix.data[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool TableMatrix<T>::operator!=(const TableMatrix<T>& matrix) const{
    return !(*this == matrix);
}





