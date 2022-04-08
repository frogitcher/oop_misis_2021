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
        bool Empty() const;
        int* GetData() const;

        void push_back(int value);
        void pop_back();
        void clear();
        void erase(int64_t index);
        void resize(int64_t new_size, int value = 0);
        void assign(int64_t new_size, int value = 0);
        void insert(int64_t index, int value);
        void swap(DynamicArray& other);
        void reallocate(int64_t new_capacity);

        int* begin();
        int* end();

        int& operator[](int64_t i) const;
        int& at(int64_t i) const;

        DynamicArray& operator=(const DynamicArray& rhs);

        bool operator==(const DynamicArray& rhs) const;
        bool operator!=(const DynamicArray& rhs) const;

    private:
        int64_t size = 0;
        int64_t capacity = 0;
        int* data;
};
