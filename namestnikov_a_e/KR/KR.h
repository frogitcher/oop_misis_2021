#pragma once
#include <stdexcept>

template <T>
Square <T> {
public:
    Square() = default;
    ~Square() = default;
    Square(<T> x0, <T> y0, <T> x1, <T> y1);

    template<T>
    double Square<T>::Perimeter();
    template<T>
    double Square<T>::Plosh();
    template<T>
    double Square<T::PloshInter(Square<T>& rhs);
    bool Square<T>::IfInter(Square<T>& rhs);
private:
    <T> x0;
    <T> y0;
    <T> x1;
    <T> y1;
};

template <T>
Square<T>::Square<T>(<T> _x0, <T> _y0, <T> _x1, <T> _y1){
    if (_x0 > _x1 && _y0 > _y1)
{
this.x0 = _x1;
this.y0 = _y1;
this.x1 = _x0;
this.y1 = _y0;
}
    else if (_x0 > _x1 && _y0 < _y1)
{
this.x0 = _x1;
this.y0 = _y0;
this.x1 = _x0;
this.y1 = _y1;
}
    else if (_x0 < _x1 && _y0 > _y1)
{
this.x0 = _x0;
this.y0 = _y1;
this.x1 = _x1;
this.y1 = _y0;
}
    else
    {
this.x0 = _x0;
this.y0 = _y0;
this.x1 = _x1;
this.y1 = _y1;
    }

}

template <T>
double Square<T>::Perimeter(){
    return (abs(x1-x0)+abs(y1-y0))*2;
}
template <T>
double Square<T>::Plosh(){
    return (abs(x1-x0)*abs(y1-y0));
}
template <T>
double  Square<T>::PloshInter(Square<T>& rhs){
    if (IfInter(rhs))
    {
        if ((x0 < rhs.x0 < x1 && x0 < rhs.x1 < x1) && (x0 < ))
        {
            //Я не успел, тупо
        }
    }
    else
    {
        throw std::invalid_argument("There is no intersection");
    }
}
template <T>
bool Square<T>::IfInter(Square<T>& rhs){
    if (x0 < rhs.x0 < x1 || x0 < rhs.x1 < x1)
    {
return true;
    }
    else if (y0 < rhs.y0 < y1 || y0 < rhs.y1 < y1)
    {
        return true;
    }
    else if (rhs.x0 < x0 < rhs.x1 || rhs.x0 < x1 < rhs.x1)
    {
        return true;
    }
    else if (rhs.y0 < y0 < rhs.y1 || rhs.y0 < y1 < rhs.y1)
    {
        return true;
    }
    else
    {
        return false;
    }
}