#include <iostream>

using namespace std;

class rational {
private: int p, q;
public:
    rational(int pp = 0, int qq =1)  {
        int d = nod(pp, qq);
        p = pp / d;
        q = qq / d;
    };
    rational(int num){
        p = num;
        q = 1;
    }
    rational(const rational& rhs){
        p = rhs->p;
        q = rhs->q;
    }
    bool operator ==(const rational& b) const;
    rational& operator=(const rational& rhs);
    rational operator+(const rational& rhs) const;
    rational& operator+=(const rational& rhs);
    rational operator-(const rational& rhs) const;
    rational& operator-=(const rational& rhs);
    rational operator*(const rational& rhs) const;
    rational& operator*=(const rational& rhs);
    rational operator/(const rational& rhs) const;
    rational& operator/=(const rational& rhs);
    rational operator-() const;
    rational operator+() const;
    rational& operator++();
    rational operator++(int);
    rational& operator--();
    rational operator--(int);
    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;
    ~rational() = default;
};
