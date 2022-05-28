#pragma once
#include <iostream>

class DynamicArray{
private:
    size_t capacity = 0;
    size_t size = 0;
    int* data = nullptr;
public:
    DynamicArray();//
    DynamicArray(size_t sz, const int& value = 0);//
    DynamicArray(const DynamicArray& other);//
    DynamicArray(const std::initializer_list<int>& lst);//

    ~DynamicArray();

    size_t Size() const;//
    size_t Capacity() const;//
    bool Empty() const;//
    int& operator[] (size_t i) const;//
    int& at (size_t i) const;//--
    bool operator== (const DynamicArray& other) const;
    void operator= (const DynamicArray& other);

    void Push_back(const int& value);//
    void Pop_back();//throw exception //
    void Clear();//
    void Erase(size_t index);//
    void Resize(size_t newsize);//
    void Swap(DynamicArray& other);//
    void Assign(int new_size, int value);
    void Insert(int index, int value);
    int& At(int i) const;


    int* begin() const;//
    int* end() const;//
    void Sort(const int& b, const int& e);//


    //tests
    void view();




};
