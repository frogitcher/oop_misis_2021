/*
    made by Omar Zoloev
*/

#include <iostream>

template <typename T>
struct Point{
    T x;
    T y;
    Point(T x1, T y1): x(x1), y(y1) {}

    operator = (const Point rhs) {
        x = rhs.x;
        y = rhs.y;
    }

    operator == (const Point rhs) {
        if(x == rhs.x && y == rhs.y)
            return true;
        else
            return false;

    }
};

template <typename T>
class Pramoy{

private:
    Point<float> A;
    Point<float> B;
    Point<float> C;
    Point<float> D;

public:
    Pramoy(const Point<float>& A,
           const Point<float>& B,
           const Point<float>& C,
           const Point<float>& D): A(A), B(B), C(C), D(D)
    {}

    ~Pramoy() = default;

    T Square() {
        T dlina = (D.x - A.x);
        T shirina = (B.y - A.y);
        return dlina * shirina;
    }

    T Perim() {
        T dlina = (D.x - A.x);
        T shirina = (B.y - A.y);
        return 2 * (dlina + shirina);
    }

    bool Peresek(const Pramoy& rhs) {
        if ( A.x <=  rhs.D.x && A.x >= rhs.A.x && A.y <=  rhs.D.y && A.y >= rhs.A.y
          || B.x <=  rhs.D.x && B.x >= rhs.A.x && B.y <=  rhs.D.y && B.y >= rhs.A.y
          || D.x <=  rhs.D.x && D.x >= rhs.A.x && D.y <=  rhs.D.y && D.y >= rhs.A.y
          || C.x <=  rhs.D.x && C.x >= rhs.A.x && C.y <=  rhs.D.y && C.y >= rhs.A.y )
            return true;
        else
            return false;
    }

    bool PeresekSquare(const Pramoy& rhs) {
        if ( A.x <=  rhs.D.x && A.x >= rhs.A.x && A.y >=  rhs.D.y && A.y <= rhs.B.y )
            return (rhs.D.x - A.x) * (rhs.B.y - A.y);
        if ( B.x <=  rhs.D.x && B.x >= rhs.A.x && B.y >=  rhs.D.y && B.y <= rhs.B.y )
            return (rhs.D.x - B.x) * (rhs.B.y - B.y);
        if ( C.x <=  rhs.D.x && C.x >= rhs.A.x && C.y >=  rhs.D.y && C.y <= rhs.B.y )
            return (rhs.D.x - C.x) * (rhs.B.y - C.y);
        if ( D.x <=  rhs.D.x && D.x >= rhs.A.x && D.y >=  rhs.D.y && D.y <= rhs.B.y )
            return (rhs.D.x - D.x) * (rhs.B.y - D.y);
        return 0;
    }

    operator = (const Pramoy& pr) {
        this->A = pr.A;
        this->B = pr.B;
        this->C = pr.C;
        this->D = pr.D;
    }


    operator == (const Pramoy& pr) {
        if (A == pr.A && B == pr.B && C == pr.C && D == pr.D)
            return true;
        else
            return false;
    }

    operator != (const Pramoy& pr) {
        if (A == pr.A && B == pr.B && C == pr.C && D == pr.D)
            return false;
        else
            return true;
    }

    void View() {
        std::cout << A.x << " " << A.y << "\n";
        std::cout << B.x << " " << B.y << "\n";
        std::cout << C.x << " " << C.y << "\n";
        std::cout << D.x << " " << D.y << "\n";
    }

};

int main()
{
//    Point<float> A(2, 1);
//    Point<float> B(2, 5);
//    Point<float> C(7, 5);
//    Point<float> D(7, 1);
//    Pramoy<float> Pr(A, B, C, D);
//
//    Point<float> A1(5, 3);
//    Point<float> B1(5, 7);
//    Point<float> C1(7, 7);
//    Point<float> D1(7, 3);
//    Pramoy<float> Pr1(A1, B1, C1, D1);

//    float t = Pr1.PeresekSquare(Pr);
//    std::cout << t;







    return 0;
}
