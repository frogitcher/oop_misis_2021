#pragma once
#include <initializer_list>
#include <stdexcept>
#include <ostream>

template<typename T>
class Stack {
 public:
  struct Node {
    T value;
    Node *next;
  };

  Stack();
  ~Stack();
  Stack(const Stack<T> &other);
  Stack(Stack<T> &&other);
  Stack(const std::initializer_list<T> &list);

  void push(const T &value);
  void pop();
  void swap(Stack<T> &other);
  void merge(Stack<T> &other);
  void clear();
  T &get() const;

  bool empty() const;
  size_t Size() const;

  bool operator==(const Stack<T> &other) const;
  bool operator!=(const Stack<T> &other) const;

  Stack<T> &operator=(const Stack<T> &other);
  Stack<T> &operator=(Stack<T> &&other);
 private:
  Node *head = nullptr;
  Node *tail = nullptr;
  size_t size = 0;

  void NewNode(T value, Node *old_head);
};

template<typename T>
Stack<T>::Stack() = default;

template<typename T>
Stack<T>::~Stack() {
  clear();
}

template<typename T>
Stack<T>::Stack(const Stack<T> &other) {
  *this = other;
}

template<typename T>
Stack<T>::Stack(Stack<T> &&other) {
  tail = other.tail;
  head = other.head;
  size = other.size;

  other.head = nullptr;
  other.tail = nullptr;
  other.size = 0;
}

template<typename T>
Stack<T>::Stack(const std::initializer_list<T> &list) {
  for (T item: list) {
    push(item);
  }
}

template<typename T>
void Stack<T>::push(const T &value) {
  NewNode(value, head);

  if (size == 0) {
    tail = head;
  }
}

template<typename T>
void Stack<T>::pop() {
  if (size == 0) {
    throw std::length_error("Stack is empty");
  }

  if (size == 1) {
    tail = nullptr;
  }

  Node *temp = head->next;
  delete head;
  head = temp;
  --size;
}
template<typename T>

void Stack<T>::NewNode(T value, Stack::Node *old_head) {
  head = new Node{value, old_head};
  ++size;
}

template<typename T>
void Stack<T>::swap(Stack<T> &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
}

template<typename T>
void Stack<T>::merge(Stack<T> &other) {
  if (other.size != 0) {
    tail->next = other.head;
    tail = other.tail;
    size = size + other.Size();
    other.tail = nullptr;
    other.head = nullptr;
    other.size = 0;
  }
}

template<typename T>
T &Stack<T>::get() const {
  if (size == 0) {
    throw std::length_error("Stack is empty");
  }
  return head->value;
}

template<typename T>
bool Stack<T>::empty() const {
  return size == 0;
}

template<typename T>
size_t Stack<T>::Size() const {
  return size;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T> &other) const {
  if (size != other.size) {
    return false;
  }

  Node *left = head;
  Node *right = other.head;

  for (int i = 0; i < size; ++i) {
    if (left->value != right->value) {
      return false;
    }

    left = left->next;
    right = right->next;
  }

  return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T> &other) const {
  return !(*this == other);
}

template<typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&other) {
  clear();

  head = other.head;
  tail = other.tail;
  size = other.size;
  other.head = nullptr;
  other.tail = nullptr;
  other.size = 0;

  return *this;
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other) {
  clear();
  if (other.size != 0) {
    head = new Node{other.head->value, nullptr};
    Node *a = other.head->next;
    Node *b = head;
    while (a != nullptr) {
      b->next = new Node{a->value, nullptr};
      b = b->next;
      a = a->next;
    }
    tail = b;
  }
  size = other.size;
  return *this;
}

template<typename T>
void Stack<T>::clear() {
  while (size != 0) {
    pop();
  }
}
