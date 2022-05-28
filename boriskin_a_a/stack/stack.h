#pragma once
#include <initializer_list>
#include <stdexcept>
#include <iostream>

template <typename T>
class Stack
{
  struct Node
  {
    T _value;
    Node* _next = nullptr;
  };

  public:
    Stack() = default; 
    Stack(const std::initializer_list<T>& list);
    Stack(const Stack<T>& other);
    ~Stack();

    void Push(const T& value);
    void Pop();
    T& Get();  
    size_t Size() const;
    bool Empty() const;
    void Swap(Stack<T>& other);
    void Merge(Stack<T>& other);
    void Clear();
    void Print();

    bool operator ==(const Stack<T>& other) const;
    bool operator !=(const Stack<T>& other) const;
    Stack<T>& operator =(const Stack<T>& other);

  private:
    size_t _size = 0;
    Node* _head = nullptr;
};

template <typename T>
void Stack<T>::Print()
{
  auto h = _head;
  while (h != nullptr)
  {
    std::cout << h->_value << std::endl;
    h = h->_next;
  }
}



template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& list)
{
  for (auto i : list)
  {
    Push(i);
  }
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other)
{
  Stack<T> h;
  auto ptr = other._head;
  while (ptr != nullptr)
  {
    h.Push(ptr->_value);
    ptr = ptr->_next;
  }
  Merge(h); 
}


template <typename T>
Stack<T>::~Stack()
{
  while (_head != nullptr)
  {
    auto h = _head;
    _head = _head->_next;
    delete h;
  }
}

template <typename T>
void Stack<T>::Push(const T& value)
{
  _head = new Node({value, _head});
  ++_size;
}
template <typename T>
void Stack<T>::Pop()
{
  if (_size == 0)
  {
    throw std::exception("Stack is empty. Can not pop the last element");
  }
  --_size;
  auto h = _head;
  _head = h->_next;
  delete h;
}

template <typename T>
T& Stack<T>::Get()
{
  if (Empty())
  {
    throw std::exception("Stack is empty");
  }
  return _head->_value;
}

template <typename T>
size_t Stack<T>::Size() const
{
  return _size;
}

template <typename T>
bool Stack<T>::Empty() const
{
  return (_head==nullptr);
}

template <typename T>
void Stack<T>::Swap(Stack<T>& other)
{
  std::swap(_size, other._size);
  std::swap(_head, other._head);
}

template <typename T>
void Stack<T>::Merge(Stack<T>& other) 
{
  while (!other.Empty())
  {
    Push(other.Get());
    other.Pop();
  }
}

template <typename T>
void Stack<T>::Clear()
{
  for (;!Empty();)
  {
    Pop();
  }
}

template <typename T>
bool Stack<T>::operator ==(const Stack<T>& other) const
{
  if (_size != other._size)
  {
    return false;
  }
  auto h1 = _head;
  auto h2 = other._head;
  while (h1 != nullptr)
  {
    if (h1->_value != h2->_value)
    {
      return false;
    }
    h1 = h1->_next;
    h2 = h2->_next;
  }
  return true;
}

template <typename T>
bool Stack<T>::operator !=(const Stack<T>& other) const
{
  return !(*this==other);
}

template <typename T>
Stack<T>& Stack<T>::operator =(const Stack<T>& other)
{
  if (this == &other)
  {
    return *this; 
  }
  Stack<T> h;
  auto ptr = other._head;
  while (ptr != nullptr)
  {
    h.Push(ptr->_value);
    ptr = ptr->_next;
  }
  Clear();
  Merge(h);
  return *this;
}
