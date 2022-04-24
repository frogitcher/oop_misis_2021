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
    bool operator ==(const rational& b) const {
        return (p == b.p && q == b.q);
    }
    rational operator +(rational b) {
        rational res;
        int a,  c;
        res.p = p * b.q + b.p * q;
        res.q = q * b.q;
        socr(&res.p, &res.q);
        return res;
    }
    rational operator -(rational b) {
        rational res;
        int a, c;
        b.p *= -1;
        res.p = p * b.q + b.p * q;
        res.q = q * b.q;
        socr(&res.p, &res.q);
        return res;
    }
    rational operator *(rational b) {
        rational rec;
        rec.p = p * b.p;
        rec.q = q * b.q;
        socr(&rec.p, &rec.q);
        return rec;
    }
    rational operator /(rational b) {
        rational rec;
        try {
            rec.p = p * b.q;
            rec.q = q * b.p;
            if (!rec.q)throw 1;
            socr(&rec.p, &rec.q);
            return rec;
        }
        catch(int i){
            rec.p = 0;
            rec.q = 1;
            cout << "delenie na 0" << "\n";
            return rec;
        }
        
    }
    rational operator +=(rational a) {
        rational res(p,q);
        res = res + a;
        p = res.p;
        q = res.q;
        return res;
    }
    rational operator -=(rational a) {
        rational res(p, q);
        res = res - a;
        p = res.p;
        q = res.q;
        return res;
    }
    rational operator *=(rational a) {
        rational res(p, q);
        res = res*a;
        p = res.p;
        q = res.q;
        return res;
    }
    rational operator /=(rational a) {
        rational res(p, q);
        res = res/a;
        p = res.p;
        q = res.q;
        return res;
    }
    rational operator ++() {
        rational res(1, 1);
        rational a(p, q);
        res = res + a;
        p = res.p;
        q = res.q;
        return res;
    }
    rational operator --() {
        rational res(1, 1);
        rational a(p, q);
        res = a-res;
        p = res.p;
        q = res.q;
        return res;
    }
    rational operator ++(int d) {
        rational res(1, 1);
        rational a(p, q);
        res = res + a;
        p = res.p;
        q = res.q;
        return res;
    }
    rational operator --(int d) {
        rational res(1, 1);
        rational a(p, q);
        res = a - res;
        p = res.p;
        q = res.q;
        return res;
    }
    friend ostream& operator<<(ostream& stream, rational a);
    friend rational operator+(int a, rational b);
    rational operator+(int b) {
        rational res;
        res.p = q * b + p;
        res.q = q;
        socr(&res.p, &res.q);
        return res;
    }
    friend rational operator-(int a, rational b);
    rational operator-(int b) {
        rational res;
        res.p = p - b*q;
        res.q = q;
        socr(&res.p, &res.q);
        return res;
    }
    friend rational operator*(int a, rational b);
    rational operator*(int b) {
        rational res;
        res.p = b * p;
        res.q = q;
        socr(&res.p, &res.q);
        return res;
    }
    friend rational operator/(int a, rational b);
    rational operator/(int b) {
        rational res;
        try {
            res.p = p;
            res.q = q * b;
            if (!res.q)throw 1;
            socr(&res.p, &res.q);
            return res;
        }
        catch (int i) {
            cout << "delenie na 0" << "\n";
            res.p = 0;
            res.q = 1;
            return res;
        }
    }
    ~rational() = default;
};

rational operator+(int a, rational b) {
    rational res;
    res.p = a * b.q + b.p;
    res.q = b.q;
    socr(&res.p, &res.q);
    return res;
}

rational operator-(int a, rational b) {
    rational res;
    res.p = a * b.q - b.p;
    res.q = b.q;
    socr(&res.p, &res.q);
    return res;
}

rational operator*(int a, rational b) {
    rational res;
    res.p = a * b.p;
    res.q = b.q;
    socr(&res.p, &res.q);
    return res;
}

rational operator/(int a, rational b) {
    rational res;
    res.p = a * b.q;
    res.q = b.p;
    socr(&res.p, &res.q);
    return res;
}

ostream& operator<<(ostream& stream, rational a) {
    stream << a.p << "/" << a.q;
    return stream;
}

