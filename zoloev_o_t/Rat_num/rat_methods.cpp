#include "rat_class.h"
#include <iostream>

Rational::Rational():
    numerator(0), denominator(1) {
    Normalize();
}

Rational::Rational(const double value):
    numerator(value), denominator(1) {
    Normalize();
}

Rational::Rational(const double num, const double den):
    numerator(num), denominator(den) {
    if (den == 0) {
        throw std::invalid_argument("denominator must not be equal to 0");
    }

    Normalize();
}

Rational::Rational(const Rational& other) = default;


Rational::~Rational() = default;

void Rational::View() {

    if (this->numerator == 0) {
        std::cout << 0 << std::endl;
    } else {
        if (this->denominator == 1) {
            std::cout << this->numerator << std::endl;
        }

        std::cout << this->numerator << "/" << this->denominator << std::endl;
    }
}

void Rational::Normalize() {
    auto g = gcd(this->numerator < 0 ? -this->numerator
                 : this->numerator, this->denominator);
    this->numerator /= g;
    this->denominator /= g;
    if(this->numerator < 0 && this->denominator < 0) {
        this->numerator = -this->numerator;
        this->denominator = -this->denominator;
    }
    if(this->numerator > 0 && this->denominator < 0) {
        this->numerator = -this->numerator;
        this->denominator = -this->denominator;
    }
}

int gcd(int a, int b) {
    while (a) {
        auto t = b % a;
        b = a;
        a = t;
    }

    return b;
}

double Rational::ToDouble() const {
    return this->numerator / (double)this->denominator;
}

Rational Rational::operator + (const Rational& rhs) const {
    return Rational{ (this->numerator * rhs.denominator + this->denominator * rhs.numerator),
                     this->denominator * rhs.denominator};
}

Rational Rational::operator - (const Rational& rhs) const {
    return Rational{ (this->numerator * rhs.denominator - this->denominator * rhs.numerator),
                     this->denominator * rhs.denominator};
}

Rational Rational::operator * (const Rational& rhs) const {
    return Rational{ (this->numerator * rhs.numerator),
                     (this->denominator * rhs.denominator) };
}

Rational Rational::operator / (const Rational& rhs) const {
    if(rhs.numerator == 0) {
        throw std::invalid_argument("Invalid divisor(divisor == 0)");
    }
    return Rational{ (this->numerator * rhs.denominator),
                     (this->denominator * rhs.numerator) };
}

Rational Rational::operator ++ () const {
    return Rational{ (this->numerator + (this->denominator)), (this->denominator) };
}

Rational Rational::operator -- () const {
    return Rational{ (this->numerator - (this->denominator)), (this->denominator) };
}

Rational Rational::operator += (const Rational& rhs) {
    *this = *this + rhs;
    return *this;
}

Rational Rational::operator -= (const Rational& rhs) {
    *this = *this - rhs;
    return *this;
}

Rational Rational::operator *= (const Rational& rhs) {
    *this = *this * rhs;
    return *this;
}

Rational Rational::operator /= (const Rational& rhs) {
    *this = *this / rhs;
    return *this;
}

bool Rational::operator < (const Rational& rhs) const {
    return ((this->numerator * rhs.denominator) < (this->denominator * rhs.numerator));
}

bool Rational::operator > (const Rational& rhs) const {
    return (rhs < *this);
}

bool Rational::operator <= (const Rational& rhs) const {
    return !(rhs < *this);
}

bool Rational::operator >= (const Rational& rhs) const {
    return !(rhs > *this);
}

bool Rational::operator == (const Rational& rhs) const {
    return (rhs.numerator == this->numerator && rhs.denominator == this->denominator);
}

bool Rational::operator != (const Rational& rhs) const {
    return !(rhs == *this);
}

std::ostream& operator << (std::ostream& out, const Rational& rhs) {
    if(rhs.denominator == 1) {
        out << rhs.numerator;
    } else {
        out << rhs.numerator << "/" << rhs.denominator;
    }

    return out;
}

std::istream& operator >> (std::istream& in, Rational& rhs) {
    int num, den;
    in >> num >> den;
    rhs = Rational(num, den);

    return in;
}
