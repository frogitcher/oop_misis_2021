#pragma once

class rational {
private:
    void normal();

    _int64 num, denum;

public:
    rational() = default;
    rational(const _int64 num);
    rational(const _int64 num, const _int64 denum);
    rational(const rational& num);
    ~rational() = default;
    
    rational operator+ (const rational& rhs) const;
    rational operator- (const rational& rhs) const;
    rational operator* (const rational& rhs) const;
    rational operator/ (const rational& rhs) const;

    rational& operator+= (const rational& rhs);
    rational& operator-= (const rational& rhs);
    rational& operator*= (const rational& rhs);
    rational& operator/= (const rational& rhs);

    rational& operator++ ();
    rational& operator-- ();
    rational operator++ (int);
    rational operator-- (int);

    bool operator== (const rational& rhs) const;
    bool operator> (const rational& rhs) const;
    bool operator< (const rational& rhs) const;
    bool operator>= (const rational& rhs) const;
    bool operator<= (const rational& rhs) const;
    bool operator!= (const rational& rhs) const;
};