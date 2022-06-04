#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "math.h"

using std::abs;
using std::sqrt;
using std::min;
using std::max;

const double eps = 1e-7;

/*
    2-----3
    |     |
    1-----4
*/

template <typename T>
class Pr
{
public:
    Pr() = default;
    Pr(T x1_, T y1_, T x2_, T y2_, T x3_, T y3_, T x4_, T y4_);
    Pr(const Pr& rhs);
    ~Pr() = default;

    T Weith() const;
    T Height() const;
    T Area() const;
    T Perim() const;
    T Area_intersect(const Pr& rhs) const;
    T Area_merge(const Pr& rhs) const;
    T Len_diagonal(const Pr& rhs) const;

    Pr<T>& operator=(const Pr& rhs) const;
    bool operator==(const Pr& rhs) const;
    bool operator!=(const Pr& rhs) const;
    bool IsSquare() const;
    bool IsIntersect(const Pr& rhs) const;
private:
    T x1, y1, x2, y2, x3, y3, x4, y4;
    T sqr(const T& val) const;
};

template <typename T>
Pr<T>::Pr(T x1_, T y1_, T x2_, T y2_, T x3_, T y3_, T x4_, T y4_) : x1(x1_), x2(x2_), x3(x3), y3(y3_), x4(x4_), y4(y4_)
{
}

template <typename T>
Pr<T>::Pr(const Pr<T>& rhs)
{
    *this = rhs;
}

template <typename T>
T Pr<T>::Weith() const
{
    return x4 - x1;
}

template <typename T>
T Pr<T>::Height() const
{
    return y2 - y1;
}

template <typename T>
T Pr<T>::Area() const
{
    return Weith() * Height();
}

template <typename T>
T Pr<T>::Perim() const
{
    return Weith() *2 + Height() * 2;
}


template <typename T>
T Pr<T>::Area_intersect(const Pr& rhs) const
{
    if (!IsIntersect(rhs))
        return false;
    T v1 = Weith() * Height(); 
    T v2 = abs(x1- rhs.x4) * abs(y1 - rhs.y4);
    T v3 = abs(x4 - rhs.x1) * abs(y4 - rhs.y1);
    T v4 = abs(x2 - rhs.x1) * abs(y2 - rhs.y1);
    return v1 - v2 - v3 - v4;
}

// inter and merge

template <typename T>
T Pr<T>::Len_diagonal(const Pr& rhs) const
{
    return sqrt(sqr(y1 - y2) + sqr(x1 - x4));
}



template <typename T>
Pr<T>& Pr<T>::operator=(const Pr& rhs) const
{
    x1 = rhs.x1; x2 = rhs.x2;
    x3 = rhs.x3; x4 = rhs.x4;
    y1 = rhs.y1; y2 = rhs.y2;
    y3 = rhs.y3; y4 = rhs.y4;
}

template <typename T>
bool Pr<T>::operator==(const Pr& rhs) const
{
    return abs(Weith() - rhs.Weith()) < eps && abs(Height() - rhs.Weith()) < eps;
}

template <typename T>
bool Pr<T>::operator!=(const Pr& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
bool Pr<T>::IsSquare() const
{
    return abs(Weith() - Height()) < eps;
}

template <typename T>
bool Pr<T>::IsIntersect(const Pr<T>& rhs) const
{
    if (x4 <= rhs.x1 || y3 <= rhs.y1)
        return false;
    return true;
}
template <typename T>
T Pr<T>::sqr(const T& val) const
{
    return val * val;
}
