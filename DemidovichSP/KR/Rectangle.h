#pragma once
#include <initializer_list>
template <typename T>
//in clioc i can't create float f cause it was appended in 20c++ version
class Rectangle {
public:
    Rectangle() = default;

    Rectangle(Rectangle<int> rectangle);

    ~Rectangle() = default;

    explicit Rectangle(const Rectangle<int> &rectangle);
    Rectangle(int argx1,int argx2,int argy1,int argy2);

    int Square();
    int Perimeter();

    int SquarePeresechenie(const Rectangle<int>& rectangle);
    bool Peresechenie(const Rectangle<int> &rectangle);

private:
    int x1,y1,x2,y2;
//    left corner (x1,y1)
//    right corner (x2,y2)
    int sidex,sidey;
};

