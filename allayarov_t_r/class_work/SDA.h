#pragma once
#ifndef SDA_H
#define SDA_H

#include <iostream>

class SDA
{
public:
  SDA();
  SDA(const size_t size, const int &value = 0);
  SDA(const SDA &other);
  ~SDA();

  SDA &operator=(const SDA &rhs);
  bool operator==(const SDA &rhs) const;
  bool operator!=(const SDA &rhs) const;

  size_t Size() const;
  bool Empty() const;
  int Get() const;

  void Push(const int &value);
  void Pop();
  void Swap(SDA &rhs);

  int *Begin() const;
  int *End() const;

private:
  size_t capacity_{0};
  size_t size_{0};

  int *data_{nullptr};
};
#endif /* SDA_H */
