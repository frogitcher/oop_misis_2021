#pragma once

class Rational {
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

    Rational operator-() const;

    bool operator<(const Rational& rhs) const;
    bool operator<=(const Rational& rhs) const;
    bool operator>(const Rational& rhs) const;
    bool operator>=(const Rational& rhs) const;
    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;

    void showme() const;

    int getden() const;
    int getnum() const;
    void setden(const int& _den);
    void setnum(const int& _num);

private:
    void Normalize();
    int num, den;
};
