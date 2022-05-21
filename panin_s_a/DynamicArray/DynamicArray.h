#pragma once
#include <initializer_list>

class DynamicArray {
public:
    DynamicArray();
    DynamicArray(std::size_t length, int value);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<int>& list);
    ~DynamicArray();

    std::size_t Size() const; 
    std::size_t Capacity() const;
    bool Empty() const;
    int& operator[](int i) const;
    int& At(int i) const;
    void Push_back(int value);
    void Pop_back();
    void Clear();
    void Erase(std::size_t index);
    void Insert(std::size_t index, int val);
    void Assign(std::size_t new_size, int val = 0);
    void Resize(std::size_t new_size, int val = 0);
    int* Begin() const;
    int* End() const;
    void Swap(DynamicArray& other);
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;
    DynamicArray& operator=(const DynamicArray& other);
    int* Get_data() const;
private:
    std::size_t capacity = 0;
    std::size_t size = 0;
    int* data;
};
