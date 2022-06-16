#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class prior_queue
{
  public:
    prior_queue()= default;
    prior_queue(std::vector<T> values, std::vector<int> prior);
    ~prior_queue();
  
    void print() const;
    void push(const T& value, const int priority);
    void pop(); //pop the element with the biggest priority
    void clear();
    T& get() const; //get the element with the biggest priority
    size_t size();
    
    bool operator ==(const prior_queue<T>& other) const;
    bool operator !=(const prior_queue<T>& other) const;
    //prior_queue<T> operator =(const prior_queue<T>& other);

  private:
    size_t _size = 0;
    std::vector<T> _values;
    std::vector<int> _prior;
    void sort_by_prior();
};

template<typename T>
inline prior_queue<T>::prior_queue(std::vector<T> values, std::vector<int> prior)
{
  if (_values.size() != _prior.size())
  {
    throw std::invalid_argument("Vectors of values and vectors of priorities must have the same size!");
  }
  _size = values.size();
  _values = values;
  _prior = prior;
  sort_by_prior();
}

template<typename T>
inline prior_queue<T>::~prior_queue()
{
  clear();
}

template<typename T>
inline void prior_queue<T>::print() const
{
  for (int i = 0; i < _values.size(); ++i)
  {
    std::cout << _values[i] << ' ' << _prior[i] << std::endl;
  }
}

template<typename T>
inline void prior_queue<T>::push(const T& value, const int priority)
{
  _size++;
  _values.push_back(value);
  _prior.push_back(priority);
  sort_by_prior();
}

template<typename T>
inline void prior_queue<T>::pop()
{
  _size--;
  _values.pop_back();
  _prior.pop_back();
}

template<typename T>
inline void prior_queue<T>::clear()
{
  for (int i = 0; i < _values.size(); ++i)
  {
    pop();
  }
}

template<typename T>
inline T& prior_queue<T>::get() const
{
  return _values[_values.size()-1];
}

template<typename T>
inline size_t prior_queue<T>::size()
{
  return _size;
}

template<typename T>
inline bool prior_queue<T>::operator==(const prior_queue<T>& other) const
{
  bool flag = true;
  for (int i=0; i<_values.size(); ++i)
  {
    if ((_values[i] != other._values[i]) || (_prior[i] != other._prior[i]))
    {
      flag = false;
    }
  }
  return flag;
}

template<typename T>
inline bool prior_queue<T>::operator!=(const prior_queue<T>& other) const
{
  return !(*this == other);
}

//template<typename T>
//inline prior_queue<T> prior_queue<T>::operator=(const prior_queue<T>& other)
//{
//  return prior_queue<T>();
//}

template<typename T>
inline void prior_queue<T>::sort_by_prior()
{
  for (int i = 0; i < _prior.size(); ++i)
  {
    for (int j = i + 1; j < _prior.size() - 1; ++j)
    {
      if (i > j)
      { 
        std::swap(_prior[i], _prior[j]);
        std::swap(_values[i], _values[j]);
      }
    }
  }
  std::reverse(_prior.begin(), _prior.end());
  std::reverse(_values.begin(), _values.end());
}
