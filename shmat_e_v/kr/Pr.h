#pragma once
#include <iostream>
#include <cmath>



template<typename T>
class Pr {
 public:
  struct Point {
    T x;
    T y;
  };

  Pr();
  ~Pr() = default;
  Pr(const T _x,const T _y,const T _x_len, const T _y_len); //  по 1 точке и длинам сторон (верхняя левая точка)
  Pr(const Pr<T> &other);

  T Perimetr() const;
  T Area() const;
  T IntersectionArea(const Pr<T> &other) const;
  T IntersectionPerimetr(const Pr<T> &other) const;
  Pr<T> &Intersection(const Pr<T> &other);
  Point Center() const;
  Pr<T> &ReflectX(T _x); // отражение относительно прямой x=_x
  Pr<T> &ReflectY(T _y); // отражение относительно прямой x=_y

 private:
  T x;
  T y;
  T x_len;
  T y_len;
};

