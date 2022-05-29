#pragma once
#include <cstdint>
#include <initializer_list>

class DynamicArray {
    public:
        DynamicArray(int64_t size = 0, int value = 0);
        DynamicArray(const DynamicArray& other);
        DynamicArray(const std::initializer_list<int>& list);
        ~DynamicArray();

        int64_t Size() const;
        int64_t Capacity() const;
        int* GetData() const;
        void Reallocate(int64_t new_capacity);

        bool Empty() const;
        
        int& operator[](int64_t i) const;
        int& at(int64_t i) const;

        void push_back(int value);
        void pop_back(); 
        void clear();
        void erase(int64_t index);
        void resize(int64_t new_size);
        void reallocate(int64_t new_capacity);
        void assign(int64_t new_size, int value);
        void insert(int64_t index, int value);
        void swap(DynamicArray& other);

        int* begin();
        int* end();

        DynamicArray& operator=(const DynamicArray& other);
        bool operator==(const DynamicArray& other) const;
        bool operator!=(const DynamicArray& other) const;
    private:
        int64_t size = 0;
        int64_t capacity = 0;
        int* data = 0;
};

