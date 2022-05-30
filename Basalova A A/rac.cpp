#include <iostream>
#include "rac.h"
#include <math.h>

int nod(int n, int m) {
    int c;
    n = abs(n);
    m = abs(m);
    if (n < m) {
        swap(n, m);
    }
    while (m > 0) {
        c = n;
        n = m;
        m = c % m;
    }
    return (n>0?n:1);
}

void socr(int *a, int *b) {
    int d = nod(*a, *b);
    *a = *a / d;
    *b = *b / d;
    return;
}

rational& rac::operator=(const rational &rhs) {
    p = rhs.p;
    q = rhs.q;
    return *this;
}

rational rac::operator+(const rational &rhs) const {
    return rational(*this) += rhs;
}

rational rac::operator-(const rational &rhs) const {
    return rational(*this) -= rhs;
}

rational& rac::operator+=(const rational &rhs) {
    int c = abs(q*rhs.q)/nod(q,rhs.q);
    p = p * (c / q) + rhs.p * (c / rhs.q);
    q = q;
    socr(p,q);
    return *this;
}

rational& rac::operator-=(const rational &rhs) {
    int c = abs(q*rhs.q)/nod(q,rhs.q);
    p = p * (c / q) - rhs.p * (c / rhs.q);
    q = q;
    socr(p,q);
    return *this;
}

rational& rac::operator*=(const rational &rhs) {
    p *= rhs.p;
    q *= rhs.q;
    Normal(p,q);
    return *this;
}

rational& rac::operator/=(const rational &rhs) {
    if (rhs == Rational(0)) {
        throw domain_error("Zero division.");
    }
    p *= rhs.q();
    q *= rhs.p();
    socr(p, q);
    return *this;
}

rational rac::operator/(const rational &rhs) const {
    return rational(*this) /= rhs;
}

rational rac::operator*(const rational &rhs) const {
    return rational(*this) *= rhs;
}

rational rac::operator-() const {
    rational a(*this);
    a.p *= -1;
    return a;
}

rational rac::operator+() const {
    return rational(*this);
}

rational& rac::operator++() {
    return *this += cational(1, 1);
}

rational rac::operator++(int) {
    rational c(*this);
    ++*this;
    return c;
}

rational& rac::operator--() {
    return *this -= rational(1, 1);
}

rational rac::operator--(int) {
    rational c(*this);
    --*this;
    return c;
}

bool rac::operator==(const rational &rhs) const {
    return p * rhs.q == rhs.p * q;
}

bool rac::operator!=(const rational &rhs) const {
    return !(*this == rhs);
}
