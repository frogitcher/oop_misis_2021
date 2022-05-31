#pragma once 
#include <ostream>

class Rational{
    public:
        Rational() = default;
        Rational(int _num);
        Rational(int _num, int _den);
        Rational(const Rational& other);
        ~Rational() = default;
        Rational& operator=(const Rational& rhs);
        Rational operator+(const Rational& rhs) const;
        Rational operator-(const Rational& rhs) const;
        Rational operator*(const Rational& rhs) const;
        Rational operator/(const Rational& rhs) const;
        Rational& operator+=(const Rational& rhs);
        Rational& operator-=(const Rational& rhs);
        Rational& operator*=(const Rational& rhs);
        Rational& operator/=(const Rational& rhs);
        Rational& operator++();
        Rational operator++(int);
        Rational& operator--();
        Rational operator--(int);
        Rational operator-();
        bool operator<(const Rational& rhs) const;
        bool operator>(const Rational& rhs) const;
        bool operator<=(const Rational& rhs) const;
        bool operator>=(const Rational& rhs) const;
        bool operator==(const Rational&rhs) const;
        bool operator!=(const Rational&rhs) const;
        int get_num() const;
        int get_den() const;
    private:
        int num;//numerator-числитель
        int den;//denominator-знаменатель
        void simplify();
};

std::ostream& operator<<(std::ostream& ost, const Rational& num);