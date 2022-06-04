#include "Rectangle.h"


template <typename T>
int Rectangle<T>::Square() {
    return sidex*sidey;
}

template<typename T>
int Rectangle<T>::Perimeter() {
    return 2*(sidex+sidey);
}

template<typename T>
bool Rectangle<T>::Peresechenie(const Rectangle<int>& rectangle) {
    bool xin = false,yin = false;
    if(x1>rectangle.x1){
        if (x1 + sidex<x1){
            xin = true;
        }
    }else if(rectangle.x1 > x1 and rectangle.x1<x2){
        xin = true;}
    else{
        xin = false;
    }
    if(y1>rectangle.y1){
        if (y1 + sidey<y1){
            yin = true;
        }
    }else if(rectangle.y1 > y1 and rectangle.y1<y2){
        yin = true;}
    else{
        yin = false;
    }

    if (xin and yin){
        return true;
    }else{
        return false;
    }
}

template<typename T>
Rectangle<T>::Rectangle(const Rectangle<int> &rectangle) {
    x1 = rectangle.x1;
    x2 = rectangle.x2;
    sidex = rectangle.sidex;

    y1 = rectangle.y1;
    y2 = rectangle.y2;
    sidey = rectangle.sidey;
}

template<typename T>
int Rectangle<T>::SquarePeresechenie(const Rectangle<int> &rectangle) {
    return (x2 -rectangle.x1)*(y2 - rectangle.y1);
}

template<typename T>
Rectangle<T>::Rectangle(int argx1, int argx2, int argy1, int argy2) {
    x1 = argx1;
    y1 = argx2;
    x2 = argy1;
    y2 = argy2;
    sidex = x2-x1;
    sidey = y2 - y1;
}


