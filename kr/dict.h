#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

// template <typename T>
// struct node {
//   T key;
//   double value;
// };

template <typename T>
class dict {
 public:
  dict();
  ~dict() = default;
  void add(std::pair<T, double> &new_pair);  // добавления пары
  void remove(T key);
  double get(T key) const;

  void sum(T key, double value);       // прибавление по ключу
  void decrease(T key, double value);  // вычитание по ключу

  double avg() const;
  void print() const;

 private:
  std::vector<std::pair<T, double> > data;
};

template <typename T>
dict<T>::dict() {
  this->data = std::vector<std::pair<T, double> >(0);
}

template <typename T>
void dict<T>::add(std::pair<T, double> &new_pair) {
  if (this->data.size() != 0) {
    for (auto p : this->data) {
      if (p.first == new_pair.first) {
        return;
      }
    }
  }
  this->data.push_back(new_pair);
}

template <typename T>
void dict<T>::remove(T key) {
  if (this->data.size() != 0) {
    for (size_t i; i < this->data.size(); ++i) {
      if (this->data[i].first == key) {
        this->data.erase(this->data.begin() + i);
      }
    }
  }
}

template <typename T>
double dict<T>::get(T key) const {
  if (this->data.size() != 0) {
    for (auto p : this->data) {
      if (p.first == key) {
        return p.second;
      }
    }
  }
  throw std::invalid_argument("key is not found)");
}

template <typename T>
void dict<T>::print() const {
  for (auto p : this->data) {
    std::cout << p.first << " : " << p.second << "\n";
  }
}

template <typename T>
double dict<T>::avg() const {
  double avg = 0.0;
  for (auto p : this->data) {
    avg += p.second;
  }
  avg = avg / this->data.size();
  return avg;
}

template <typename T>
void dict<T>::sum(T key, double value) {
  for (auto p : this->data) {
    if (p.first == key) {
      p.second += value;
      return;
    }
  }
}

template <typename T>
void dict<T>::decrease(T key, double value) {
  for (auto p : this->data) {
    if (p.first == key) {
      p.second -= value;
      return;
    }
  }
}