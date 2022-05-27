#pragma once
#include <cstdint>
#include <initializer_list>

template <typename T>
class BaseMatrix {
    public:
    BaseMatrix(int64_t r = 0, int64_t c = 0):
    num_cols(c),
    num_rows(r){
    }
    virtual void Resize(int64_t r, int64_t c, T value = (T)0) = 0;
    void Clear();
    virtual T& Get(int64_t r, int64_t c) const = 0;
    virtual ~BaseMatrix() = default;
    int64_t Get_Number_Rows() const;
    int64_t Get_Number_Cols() const;
    bool Square() const;
    bool Empty() const;

    protected:

    int64_t num_rows = 0;
    int64_t num_cols = 0;

    private:

};
    template <typename T>
    void BaseMatrix<T>::Clear()
    {
        Resize(0,0);
    }
    template <typename T>
    int64_t BaseMatrix<T>::Get_Number_Rows() const
    {
        return num_rows;
    }
    template <typename T>
    int64_t BaseMatrix<T>::Get_Number_Cols() const
    {
        return num_cols;
    }
    template <typename T>
    bool BaseMatrix<T>::Square() const
    {
        return num_cols == num_rows;
    }
    template <typename T>
    bool BaseMatrix<T>::Empty() const
    {
        return (num_rows == 0 && num_cols == 0);
    }