#include <iostream>
#include <algorithm>
#include <initializer_list>
template <typename T>
class Rectangle{
    public:
        Rectangle() = default;
        Rectangle(const Rectangle<T>& other);
        Rectangle(const initializer_list<T>& list_x, const initializer_list<T>& list_y);
        T perimetr(const Rectangle& rhs);
        int* begin_x() const;
        int* end_x() const;
        int* begin_y() const;
        int* end_y() const;
    private:
        T* x = new T[4];
        T* y = new T[4];
};

template <typename T>
Rectangle<T>::Rectangle(const Rectangle<T>& other) {
    std::copy(other.x, other.x + 4 * sizeof(T), x);
    std::copy(other.y, other.y + 4 * sizeof(T), y);
}

template <typename T>
Rectangle<T>::Rectangle(const initializer_list<T>& list_x, const initializer_list<T>& list_y) {
    std::copy(list_x.begin_x(), list_x.end_x(), x);
    std::copy(list_y.begin_y(), list_y.end_y(), y);
}

template<typename T> 
int* Rectangle<T>::begin_x() const{
    return x;
}

template<typename T>
int* Rectangle<T>::begin_y() const {
    return y;
}

template<typename T> 
int* Rectangle<T>::end_x() const{
    return (x + 4 * sizeof(T));
}

template<typename T> 
int* Rectangle<T>::end_y() const{
    return (x + 4 * sizeof(T));
}

template<typename T> 
T Rectangle<T>::perimetr(const Rectangle& rhs) {
    T a = x[1];
    T b = y[1];
    T dif_x = 0;
    T dif_y = 0;
    for (int i = 0; i < 4, ++i) {
        if (rhs.x[i] > a) {
            dif_x = (rhs.x[i] - a);
        }
        if (ths.y[i] > b) {
            dif_y = (rhs.y[i] - b);
        }
    }
    return (2 * dif_x + 2 * dif_y);
}
