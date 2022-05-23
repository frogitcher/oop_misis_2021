#include <iostream>

using namespace std;

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

class rational {
private: int p, q;
public:
    rational(int pp = 0, int qq =1)  {
        int d = nod(pp, qq);
        p = pp / d;
        q = qq / d;
    };
    bool operator ==(const rational& b) const;
    rational operator +(rational b);
    rational operator -(rational b);
    rational operator *(rational b);
    rational operator /(rational b);
    rational operator +=(rational a);
    rational operator -=(rational a);
    rational operator *=(rational a);
    rational operator /=(rational a);
    rational operator ++();
    rational operator --();
    rational operator ++(int d);
    rational operator --(int d);
    rational operator +(int b);
    rational operator -(int b);
    rational operator *(int b);
    rational operator /(int b);
    friend rational operator+();
    ~rational() = default;
};

friend rational operator+(int a, rational b) {
    rational res;
    res.p = a * b.q + b.p;
    res.q = b.q;
    socr(&res.p, &res.q);
    return res;
}

friend rational operator-(int a, rational b) {
    rational res;
    res.p = a * b.q - b.p;
    res.q = b.q;
    socr(&res.p, &res.q);
    return res;
}

friend rational operator*(int a, rational b) {
    rational res;
    res.p = a * b.p;
    res.q = b.q;
    socr(&res.p, &res.q);
    return res;
}

friend rational operator/(int a, rational b) {
    rational res;
    res.p = a * b.q;
    res.q = b.p;
    socr(&res.p, &res.q);
    return res;
}

friend ostream& operator<<(ostream& stream, rational a) {
    stream << a.p << "/" << a.q;
    return stream;
}

