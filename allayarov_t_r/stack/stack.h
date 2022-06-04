#pragma once

#include <iostream>
#include <initializer_list>

template <typename T>
class Stack
{
public:
  Stack() = default;
  Stack(const Stack<T> &stack);
  Stack(Stack<T> &&stack);
  Stack(const std::initializer_list<T> &init_list);
  ~Stack();

  Stack<T> &operator=(const Stack<T> &rhs);
  bool operator==(const Stack<T> &rhs) const;
  bool operator!=(const Stack<T> &rhs) const;

  size_t size() const;
  bool empty() const;

  void push(const T &value);
  void pop();
  T &get() const;

  void swap(Stack<T> &rhs);
  void merge(Stack<T> &rhs);
  void clear();

public:
  struct Node
  {
    T value_;
    Node *next_{nullptr};
  };

private:
  size_t size_{0};
  Node *head_{nullptr};
  Node *tail_{nullptr};
};

template <typename T>
Stack<T>::Stack(const Stack<T> &stack)
{
  if (!stack.empty())
  {
    head_ = new Node{stack.head_->value_, nullptr};
    Node *current_node = stack.head_->next_;
    Node *previous_node = head_;
    for (int i = 0; i < stack.size_ - 1; ++i)
    {
      Node *new_node = new Node{current_node->value_, nullptr};
      previous_node->next_ = new_node;
      current_node = current_node->next_;
      previous_node = new_node;
    }
    tail_ = previous_node;
    size_ = stack.size_;
  }
}

template <typename T>
Stack<T>::Stack(Stack<T> &&stack)
    : size_(stack.size_),
      head_(stack.head_),
      tail_(stack.tail_)
{
  stack.size_ = 0;
  stack.head_ = stack.tail_ = nullptr;
}

template <typename T>
Stack<T>::Stack(const std::initializer_list<T> &init_list)
{
  for (auto item : init_list)
    push(item);
}

template <typename T>
Stack<T>::~Stack()
{
  clear();
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &rhs)
{
  Stack<T> temp(std::move(rhs));
  swap(temp);
  return *this;
}

template <typename T>
bool Stack<T>::operator==(const Stack<T> &rhs) const
{
  if (size_ != rhs.size_)
    return false;

  Node *current = head_;
  Node *rhs_current = rhs.head_;

  for (int i = 0; i < size_; ++i)
  {
    if (current->value_ != rhs_current->value_)
      return false;

    current = current->next_;
    rhs_current = rhs_current->next_;
  }

  return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack<T> &rhs) const
{
  return !operator==(rhs);
}

template <typename T>
size_t Stack<T>::size() const
{
  return size_;
}

template <typename T>
bool Stack<T>::empty() const
{
  return size_ == 0;
}

template <typename T>
void Stack<T>::push(const T &value)
{
  head_ = new Node{value, head_};
  if (empty())
    tail_ = head_;
  ++size_;
}

template <typename T>
void Stack<T>::pop()
{
  if (empty())
    throw std::length_error("Stack is empty");
  Node *temp = head_->next_;
  delete head_;
  head_ = temp;
  --size_;
}

template <typename T>
T &Stack<T>::get() const
{
  if (empty())
    throw std::length_error("Stack is empty");
  return head_->value_;
}

template <typename T>
void Stack<T>::swap(Stack<T> &rhs)
{
  std::swap(size_, rhs.size_);
  std::swap(head_, rhs.head_);
  std::swap(tail_, rhs.tail_);
}

template <typename T>
void Stack<T>::merge(Stack<T> &rhs)
{
  if (empty())
  {
    swap(rhs);
  }
  else if (!rhs.empty())
  {
    tail_->next_ = rhs.head_;
    tail_ = rhs.tail_;
    size_ += rhs.size_;
    rhs.size_ = 0;
    rhs.head_ = rhs.tail_ = nullptr;
  }
}

template <typename T>
void Stack<T>::clear()
{
  while (!empty())
    pop();
}
