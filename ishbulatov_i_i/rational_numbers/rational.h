#pragma once
#include <ostream>
class rational
{
private:
    int num,den;
    void normalize();
public:
    rational()=default;
    ~rational()=default;
    rational(int _num);
    rational(int _num,int _den);
    rational(const rational& other);
    rational operator+(const rational& rhs) const;
    rational operator-(const rational& rhs) const;
    rational operator*(const rational& rhs) const;
    rational operator/(const rational& rhs) const;
    rational& operator +=(const rational& rhs);
    rational& operator -=(const rational& rhs);
    rational& operator *=(const rational& rhs);
    rational& operator /=(const rational& rhs);
    rational& operator =(const rational& rhs);
    rational& operator ++();
    rational& operator --();
    rational operator ++(int);
    rational operator -() const;
    rational operator --(int);
    bool operator ==(const rational& rhs) const;
    bool operator !=(const rational& rhs) const;
    bool operator >(const rational& rhs) const;
    bool operator >=(const rational& rhs) const;
    bool operator <(const rational& rhs) const;
    bool operator <=(const rational& rhs) const;
    int GetNum() const;
    int GetDen() const;
    std::ostream& operator<<(const rational& r);
};
