#pragma once
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <initializer_list>

class DynamicArray
{
public:
  DynamicArray();
  DynamicArray(const size_t size, const int value = 0);
  DynamicArray(const DynamicArray &array);
  DynamicArray(const std::initializer_list<int> &init_list);
  ~DynamicArray();

  int &operator[](const size_t idx);
  bool operator==(const DynamicArray &rhs) const;
  bool operator!=(const DynamicArray &rhs) const;
  DynamicArray &operator=(const DynamicArray &rhs);

  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  void resize(const size_t new_size, const int value = 0);
  void reserve(const size_t new_capacity);
  void shrink_to_fit();

  void push_back(const int value);
  void pop_back();
  void clear();
  void swap(DynamicArray &array);
  void erase(const size_t idx);
  void insert(const size_t idx, const int value);
  void assign(const size_t size, const int value);
  void assign(const std::initializer_list<int> &init_list);

  int &at(const size_t idx);
  int *begin();
  int *end();

private:
  void _relocate();

private:
  size_t capacity_{0};
  size_t size_{0};
  int *data_;
};

#endif /* DYNAMIC_ARRAY_H */