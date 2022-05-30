//
// Created by Егор Тарасов on 5/28/22.
//

#ifndef OOP_MISIS_2022_STACK_H
#define OOP_MISIS_2022_STACK_H
#include <initializer_list>
#include <stdexcept>

template <typename T>
class stack {
 public:
  struct node {
    T value;
    node *next;
    node(T value, node *next) {
      value = value;
      next = next;
    }
  };
  stack();
  stack(const stack<T> &other);
  stack(stack<T> &&other);
  stack(const std::initializer_list<T> &list);
  ~stack();

  void push(const T &value);
  T pop();
  T &get() const;
  bool empty() const { return this->size == 0; };
  size_t Size() const { return this->size; };
  void swap(stack<T> &other);
  void merge(stack<T> &other);
  void clear();

  stack<T> &operator=(const stack<T> &rhs);
  stack<T> &operator=(stack<T> &&rhs);

  bool operator==(stack<T> &rhs) const;
  bool operator!=(stack<T> &rhs) const;

  node *get_head() { return this->head; };
  node *get_tail() { return this->tai; };

 private:
  node *head;
  node *tail;
  size_t size;
};

template <typename T>
stack<T>::stack() {
  tail = nullptr;
  head = nullptr;
  size = 0;
}

template <typename T>
stack<T>::stack(const stack<T> &other) {
  *this = other;
}

template <typename T>
stack<T>::stack(stack<T> &&other) {
  head = other.head;
  tail = other.tail;
  size = other.size;
  other.head = nullptr;
  other.tail = nullptr;
  other.size = 0;
}

template <typename T>
stack<T>::~stack() {
  this->clear();
}

template <typename T>
void stack<T>::clear() {
  while (!this->empty()) {
    this->pop();
  }
}

template <typename T>
void stack<T>::push(const T &value) {
  node *n = new node(value, head);
  head = n;
  size += 1;
}

template <typename T>
T stack<T>::pop() {
  if (this->empty()) throw std::length_error("stack is empty");
  node *cur = head;
  T value = head->value;
  head = cur->next;
  delete cur;
  if (head == nullptr) tail = nullptr;
  size--;
  return value;
}

template <typename T>
T &stack<T>::get() const {
  if (head == nullptr) throw std::length_error("Stack is empty!");
  return head->value;
}

template <typename T>
void stack<T>::swap(stack<T> &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
}

template <typename T>
void stack<T>::merge(stack<T> &other) {
  tail->next = other.head;
  tail = other.tail;
  size += other.size;
  other.head = nullptr;
  other.tail = nullptr;
  other.size = 0;
}

template <typename T>
stack<T> &stack<T>::operator=(stack<T> &&rhs) {
  head = rhs.head;
  tail = rhs.tail;
  size = rhs.size;
  rhs.head = nullptr;
  rhs.tail = nullptr;
  rhs.size = 0;
  return *this;
}

template <typename T>
stack<T> &stack<T>::operator=(const stack<T> &rhs) {
  this->clear();
  if (rhs.size != 0) {
    head = new node(rhs.head->value, nullptr);
    node *cur = rhs.head->next;
    node *prev = head;
    while (cur != nullptr) {
      prev->next = new node(cur->value, nullptr);
      prev = prev->next;
      cur = cur->next;
    }
    tail = prev;
  }
  size = rhs.size;
  return *this;
}

#endif  // OOP_MISIS_2022_STACK_H