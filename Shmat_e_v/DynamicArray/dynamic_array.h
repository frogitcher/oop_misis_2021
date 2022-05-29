#pragma once

#include <initializer_list>
#include <iostream>

class DynamicArray {
 public:
  DynamicArray(int64_t _size = 0, int _value = 0);
  DynamicArray(const DynamicArray &rhs);
  DynamicArray(const std::initializer_list<int> &list);
  ~DynamicArray();

  DynamicArray &operator=(const DynamicArray &rhs);

  int *begin() const;
  int *end() const;

  int64_t Size() const;
  int64_t Capacity() const;

  bool Empty() const;

  int &operator[](const int64_t index);
  int &at(int64_t index) const;

  void push_back(int push_value);
  void pop_back();
  void clear();
  void erase(int64_t index);
  void insert(int64_t index, int insert_value);
  void resize(int64_t new_size, int value = 0);
  void assign(int64_t new_size, int value = 0);
  void swap(DynamicArray &other);

  bool operator==(const DynamicArray &other) const;
  bool operator!=(const DynamicArray &other) const;

  inline int *GetData() const {
    return data;
  }

 private:
  int64_t capacity = 0;
  int64_t size = 0;
  int *data;

  void reallocate(int64_t new_size);
};
