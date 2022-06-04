#pragma once
#include <ostream>
#include <stdexcept>
#include <algorithm>
template<typename T>
class Rectangle {
public:


    Rectangle(const T& a, const T& b, const T& c, const T& d);
    Rectangle(const Rectangle<T>& other);
    ~Rectangle() { }

    inline T& Perimeter(const T& x1, const T& x2, const T& y1, const T& y2)
    {
        return { 2 * ((std::abs(x2 - x1)) + (std::abs(y2 - y1))); }
    }
    inline T& Square(const T& x1, const T& x2, const T& y1, const T& y2)
    {
        return { (std::abs(x2 - x1)) * (std::abs(y2 - y1)); }
    }
    Rectangle<T>& Cross_Square(const Rectangle<T>& rhs);
    Rectangle<T>& Union_Square(const Rectangle<T>& rhs);
private:
    T x1, x2, y1, y2;

};
template<typename T>
Rectangle<T>::Rectangle(const T& a, const T& b, const T& c, const T& d) {
    this->x1 = a;
    this->x2 = b;
    this->x2 = c;
    this->x2 = d;

}
template<typename T>
Rectangle<T>::Rectangle(const Rectangle<T>& other) {
    *this = other;
}
template <typename T>
Rectangle<T>& Rectangle<T>::Ñross_Square() { const Rectangle<T>& rhs }
{
    T x3 = rhs.x1;
    T x4 = rhs.x2;
    T y3 = rhs.y1;
    T y4 = rhs.y2;
    T A[4] = { this->x1, this->x2,x3,x4 };
    T B[4] = { this->y1, this->y2,y3,y4 };
    T x_min = this->x1;
    T x_max = this->x1;
    T y_min = this->y1;
    T y_max = this->y1;
    T x1_sred, x2_sred, y1_sred, y2_sred;
    for (int i = 0; i < 4; i++)
    {
        if (x_max < A[i])
        {
            x_max = A[i];
        }
        if (y_max < B[i])
        {
            y_max = B[i];
        }
        if (x_min > A[i])
        {
            x_min = A[i];
        }
        if (y_min > B[i])
        {
            y_min = B[i];
        }
    }


    for (int i = 0; i < 4; i++)
    {
        if ((A[i] != x_max) && (A[i] != x_min))
        {
            x1_sred = A[i];
            break;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if ((A[i] != x_max) && (A[i] != x_min) && (A[i] != x1_sred))
        {
            x2_sred = A[i];
            break;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if ((B[i] != y_max) && (B[i] != y_min))
        {
            y1_sred = B[i];
            break;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if ((B[i] != y_max) && (B[i] != y_min) && (B[i] != y1_sred))
        {
            y2_sred = B[i];
            break;
        }
    }
    return (std::abs(x2_sred - x1_sred)) * (std::abs(y2_sred - y1_sred));

}
template <typename T>
Rectangle<T>& Rectangle<T>::Union_Square() { const Rectangle<T>& rhs }
{
    T x3 = rhs.x1;
    T x4 = rhs.x2;
    T y3 = rhs.y1;
    T y4 = rhs.y2;
    T A[4] = { this->x1, this->x2,x3,x4 };
    T B[4] = { this->y1, this->y2,y3,y4 };
    T x_min = this->x1;
    T x_max = this->x1;
    T y_min = this->y1;
    T y_max = this->y1;
    T x1_sred, x2_sred, y1_sred, y2_sred;
    for (int i = 0; i < 4; i++)
    {
        if (x_max < A[i])
        {
            x_max = A[i];
        }
        if (y_max < B[i])
        {
            y_max = B[i];
        }
        if (x_min > A[i])
        {
            x_min = A[i];
        }
        if (y_min > B[i])
        {
            y_min = B[i];
        }
    }


    for (int i = 0; i < 4; i++)
    {
        if ((A[i] != x_max) && (A[i] != x_min))
        {
            x1_sred = A[i];
            break;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if ((A[i] != x_max) && (A[i] != x_min) && (A[i] != x1_sred))
        {
            x2_sred = A[i];
            break;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if ((B[i] != y_max) && (B[i] != y_min))
        {
            y1_sred = B[i];
            break;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if ((B[i] != y_max) && (B[i] != y_min) && (B[i] != y1_sred))
        {
            y2_sred = B[i];
            break;
        }
    }
    return (std::abs(this->x1 - this->x2)) * (std::abs(this->y1 - this->y2)) + (std::abs(x3 - x4)) * (std::abs(y3 - y4)) - (std::abs((x2_sred - x1_sred)) * (std::abs(y2_sred - y1_sred));

}


