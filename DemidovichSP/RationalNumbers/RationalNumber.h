#pragma once
#include <ostream>

class RationalNumber {
public:
    RationalNumber() = default;
    explicit RationalNumber(int _num);
    RationalNumber(int _num, int _denom);
    RationalNumber(const RationalNumber& rationalNumber);
    ~RationalNumber() = default;


    RationalNumber operator+(const RationalNumber& rationalNumber) const;
    RationalNumber operator-(const RationalNumber& rationalNumber) const;
    RationalNumber operator*(const RationalNumber& rationalNumber) const;
    RationalNumber operator/(const RationalNumber& rationalNumber) const;

    RationalNumber& operator=(const RationalNumber& rationalNumber);
    RationalNumber& operator+=(const RationalNumber& rationalNumber);
    RationalNumber& operator-=(const RationalNumber& rationalNumber);
    RationalNumber& operator*=(const RationalNumber& rationalNumber);
    RationalNumber& operator/=(const RationalNumber& rationalNumber);

    bool operator<(const RationalNumber& rationalNumber) const;
    bool operator<=(const RationalNumber& rationalNumber) const;
    bool operator>(const RationalNumber& rationalNumber) const;
    bool operator>=(const RationalNumber& rationalNumber) const;
    bool operator==(const RationalNumber& rationalNumber) const;
    bool operator!=(const RationalNumber& rationalNumber) const;

    RationalNumber operator-();

    int getNum() const;
    int getDenom() const;

private:
    int num,denom;
    void normalize();

};
std::ostream& operator<<(std::ostream& osStream, const RationalNumber& rationalNumber);
