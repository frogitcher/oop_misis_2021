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

        bool operator<(const Rational& rhs) const; //true if *this < rhs
        bool operator<=(const Rational& rhs) const;
        bool operator>(const Rational& rhs) const;
        bool operator>=(const Rational& rhs) const;
        bool operator==(const Rational& rhs) const;
        bool operator!=(const Rational& rhs) const;

        Rational& operator++();
        Rational operator++(int a);
        Rational& operator--();
        Rational operator--(int a);

        int get_numerator() const;
        int get_denumerator() const;

    private:
        int num, den;
        void normalize();
};