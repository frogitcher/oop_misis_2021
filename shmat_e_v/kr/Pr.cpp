#include "Pr.h"

template<typename T>
Pr<T>::Pr() {
  x = 0;
  y = 0;
  x_len = 0;
  y_len = 0;
}

template<typename T>
Pr<T>::Pr(const Pr<T> &other) {
  x = other.x;
  y = other.y;
  x_len = other.x_len;
  y = other.y_len;
}

template<typename T>
Pr<T>::Pr(const T _x, const T _y, const T _x_len, const T _y_len) {
  x = _x;
  y = _y;
  x_len = _x_len;
  y_len = _y_len;
}

template<typename T>
Pr<T>::Pr<typename T>(const T _x1, const T _y1, const T _x2, const T _y2) {
  x = _x1;
  y = _y1;
  x_len = std::abs(_x1 - _x2);
  y_len = std::abs(_y1 - _y2);
}

template<typename T>
T Pr<T>::Perimetr() const {
  return 2 * x_len * y_len;
}

template<typename T>
T Pr<T>::Area() const {
  return x_len * y_len;
}

template<typename T>
Pr<T> &Pr<T>::Intersection(const Pr<T> &other) const {
  if(other.x <= x - x_len || other.x + other.x_len <= x || other.y <= y - y_len || other.y + other.y_len <= y) {
    throw std::length_error("Prs does not intersect");
  }
  T new_x = std::max(x, other.x);
  T new_y = std::min(y, other.y);
  T new_x_len = std::abs(x - other.x);
  T new_y_len = std::abs(y - other.y);

  Pr newPr(new_x, new_y, new_x_len, new_y_len);

  return newPr;
}

template<typename T>
T Pr<T>::IntersectionArea(const Pr<T> &other) const {
  Pr newPr = Intersection(other);
  return newPr.Area();
}

template<typename T>
T Pr<T>::IntersectionPerimetr(const Pr<T> &other) const {
  Pr newPr = Intersection(other);
  return newPr.Perimetr();
}

template<typename T>
Point Pr<T>::Center() const {
  Point p(x/2, y/2);
  return Point;
}

template<typename T>
Pr<T> &Pr<T>::ReflectX(T _x) {
  if (_x < x) {
    T d = x - _x;
    T new_x = x - 2 * d - x_len;
    Pr newPr(new_x, y, x_len, y_len);
    return Pr;
  } else if(_x == x) {
    return *this;
  } else (_x >= x + x_len) {
    T d = _x - x - x_len;
    T new_x = x + x_len + 2 * d;
    Pr newPr(new_x, y, x_len, y_len);
    return Pr;
  } else {
    T d = _x - x;
    T new_x = x + 2 * d;
    Pr newPr(new_x, y, x_len, y_len);
    return Pr;
  }
}

template<typename T>
Pr<T> &Pr<T>::ReflectY(T _y) {
  if (_y < y) {
    T d = y - _y;
    T new_y = y - 2 * d - y_len;
    Pr newPr(x, new_y, x_len, y_len);
    return Pr;
  } else if(_y == y) {
    return *this;
  } else (_y >= y + y_len) {
    T d = _y - y - y_len;
    T new_y = y + y_len + 2 * d;
    Pr newPr(x, new_y, x_len, y_len);
    return Pr;
  } else {
    T d = _y - y;
    T new_y = y + 2 * d;
    Pr newPr(x, new_y, x_len, y_len);
    return Pr;
  }
}

template<typename T>
void Pr<T>::Move(T _x, T _y) {
  x += _x;
  _y += y;
}