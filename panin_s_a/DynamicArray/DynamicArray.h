#pragma once
#include <initializer_list>

class DynamicArray {
public:
    DynamicArray();
    DynamicArray(int length, int value);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<int>& list);
    ~DynamicArray();

    int Size() const; 
    int Capacity() const;
    bool Empty() const;
    int& operator[](int i);
    int& At(int i) const;
    void Push_back(int value);
    void Pop_back();
    void Clear();
    void Erase(int index);
    void Insert(int index, int val);
    void Assign(int new_size, int val = 0);
    void Resize(int new_size, int val = 0);
    int* Begin() const;
    int* End() const;
    void Swap(DynamicArray& other);
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;
    DynamicArray& operator=(const DynamicArray& other);
    int* Get_data() const;
private:
    int capacity = 0;
    int size = 0;
    int* data;
};
