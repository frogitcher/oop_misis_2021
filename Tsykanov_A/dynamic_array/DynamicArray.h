#pragma once
#include <initializer_list>
#include <cstdint>
class DynamicArray
{
public:
    //Конструкторы
    DynamicArray() = default;
    DynamicArray(int64_t lenght, int value);
    DynamicArray(const DynamicArray& other);
    DynamicArray(const std::initializer_list<int>& list);
    ~DynamicArray();
    //Методы
    void push_back(int value);
    inline void clear(){size = 0;};
    void pop_back();
    void erase(int64_t index);
    void resize(int64_t new_size, int value);
    void assign(int64_t new_size, int value);
    void insert(int64_t index, int value);
    void swap(DynamicArray& other);
    //указатели
    inline int* begin() const {return data;};
    inline int* end() const {return data + size;};
    // операторы
    DynamicArray& operator=(const DynamicArray& rhs);
    int& operator[](int64_t i) const;
    int& at(int64_t i) const;
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;
    inline int64_t Size() const {return size;};
    inline int64_t Capacity() const{return capacity;};
    inline bool Empty() const { return size == 0;}
    inline int* GetData() const { return data;}
    inline void Reallocate(DynamicArray& _da, int64_t new_size) {
            _da.reallocate(new_size);
        }
private:
    int64_t size = 0;
    int64_t capacity = 0;
    int *data;
    void reallocate(int64_t new_capacity);
};

inline void Reallocate(DynamicArray& _da, int64_t new_size);