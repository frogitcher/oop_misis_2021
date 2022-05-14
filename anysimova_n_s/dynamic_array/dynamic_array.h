#pragma once
#include <initializer_list>
#include <cstdint>

class DynamicArray {
    public:
        DynamicArray(int64_t size = 0, int value = 0);
        DynamicArray(const std::initializer_list<int>& list);
        DynamicArray(const DynamicArray& other);
        ~DynamicArray();

        int64_t Size() const;
        int64_t Capacity() const;
        bool empty() const; 

        void push_back(int value); 
        void pop_back(); 
        void clear(); 
        void erase(int64_t index);
        void resize(int64_t new_size); 
        void assign(int64_t new_size, int value); 
        void insert(int64_t index, const int value); 
        void swap(DynamicArray& other); 

        int* begin();
        int* end();

        int& at(int64_t i) const; 
        int& operator[](int64_t i) const; 

        DynamicArray& operator=(const DynamicArray& rhs); 

        bool operator==(const DynamicArray& rhs) const;
        bool operator!=(const DynamicArray& rhs) const;
    private:
        int64_t size = 0;
        int64_t capacity = 0;
        int* data;
};