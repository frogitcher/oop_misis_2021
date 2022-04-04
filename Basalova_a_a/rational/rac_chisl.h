#include <iostream>

using namespace std;

int nod(int n, int m) {
    int c;
    n = abs(n);
    m = abs(m);
    if (n < m) {
        c = n;
        n = m;
        m = c;
    }
    while (m > 0) {
        c = n;
        n = m;
        m = c % m;
    }
    return n;
}

class rac {
private: int p, q;
public:
    rac(double p = 0, double q = 1) :p(p/nod(p,q)), q(q/nod(p,q)) {};
    bool operator ==(const rac& b)const{
    	return (p == b.p && q == b.q);
    }
    rac operator +(rac b) {
        rac res;
        int a,  c;
        a = p * b.q + b.p * q;
        c = q * b.q;
        int d = nod(a, c);
        res.p = a / d;
        res.q = c / d;
        return res;
    }
    rac operator -(rac b) {
        rac res;
        int a, c;
        b.p *= -1;
        a = p * b.q + b.p * q;
        c = q * b.q;
        int d = nod(a, c);
        res.p = a / d;
        res.q = c / d;
        return res;
    }
    rac operator *(rac b) {
        rac rec;
        rec.p = p * b.p;
        rec.q = q * b.q;
        int d = nod(rec.p, rec.q);
        rec.p = rec.p /d;
        rec.q = rec.q / d;
        return rec;
    }
    rac operator /(rac b) {
        rac rec;
        rec.p = p * b.q;
        rec.q = q * b.p;
        int d = nod(rec.p, rec.q);
        rec.p = rec.p / d;
        rec.q = rec.q / d;
        return rec;
    }
    friend ostream& operator<<(ostream& stream, rac a);
    friend rac operator+(int a, rac b);
    rac operator+(int b) {
        rac res;
        res.p = q * b + p;
        res.q = q;
        int d = nod(res.p, res.q);
        res.p /= d;
        res.q /= d;
        return res;
    }
    friend rac operator-(int a, rac b);
    rac operator-(int b) {
        rac res;
        res.p = p - b*q;
        res.q = q;
        int d = nod(res.p, res.q);
        res.p /= d;
        res.q /= d;
        return res;
    }
    friend rac operator*(int a, rac b);
    rac operator*(int b) {
        rac res;
        res.p = b * p;
        res.q = q;
        int d = nod(res.p, res.q);
        res.p /= d;
        res.q /= d;
        return res;
    }
    friend rac operator/(int a, rac b);
    rac operator/(int b) {
        rac res;
        res.p = p;
        res.q = q*b;
        int d = nod(res.p, res.q);
        res.p /= d;
        res.q /= d;
        return res;
    }
    ~rac() = default;
};

rac operator+(int a, rac b) {
    rac res;
    res.p = a * b.q + b.p;
    res.q = b.q;
    int d = nod(res.p, res.q);
    res.p /= d;
    res.q /= d;
    return res;
}

rac operator-(int a, rac b) {
    rac res;
    res.p = a * b.q - b.p;
    res.q = b.q;
    int d = nod(res.p, res.q);
    res.p /= d;
    res.q /= d;
    return res;
}

rac operator*(int a, rac b) {
    rac res;
    res.p = a * b.p;
    res.q = b.q;
    int d = nod(res.p, res.q);
    res.p /= d;
    res.q /= d;
    return res;
}

rac operator/(int a, rac b) {
    rac res;
    res.p = a * b.q;
    res.q = b.p;
    int d = nod(res.p, res.q);
    res.p /= d;
    res.q /= d;
    return res;
}

ostream& operator<<(ostream& stream, rac a) {
    stream << a.p << "/" << a.q;
    return stream;
}

rac f(int op, int a, int b, int c, int d= 1){
rac r(a,b);
	rac r1(a,b); rac r2(c,d);
	switch(op){
	case 0:
		return(r + c);
		break;
	case 1:
		return(c+r);
		break;
	case 2:
		return(r - c);
		break;
	case 3:
		 return(c-r);
		 break;
	case 4:
		return(r*c);
		break;
	case 5:
		return(c*r);
		break;
	case 6:
		return(r/c);
		break;
	case 7:
		return(c/r);
		break;
	case 8:
		return(r1 + r2);
		break;
	case 9:
		return(r1 - r2);
		break;
	case 10:
		return(r1*r2);
		break;
	case 11:
		return(r1/r2);
		break;
	}
	return (1,2);
}

/*int main()
{
    int a = 2;
    rac b(1, 2);
    cout << a + b << " " << b + a << "\n" << a * b << " " << b * a << "\n" << a - b << " ";
        cout << b - a << "\n" << a / b << " " << b / a;
}*/
