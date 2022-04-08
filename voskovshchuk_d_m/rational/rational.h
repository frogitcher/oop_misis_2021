#pragma once
#include <iostream>

class rational {
private:
    enum class State { integer, real };
    enum class Sign { null, positive, negative };

    //unsigned _int64 findDenum(const float x);
    //unsigned _int64 lcm(_int64 a, _int64 b);
    //unsigned _int64 gcd(_int64 a, _int64 b);
    void normal();
    void stateCheck();

    _int64 num, denum;
    State state;
    Sign sign;

public:
    rational() = default;
    template<typename Type>
    rational(const Type rhs);
    ~rational() = default;
    
    rational operator+ (const rational& rhs) const;
    rational operator- (const rational& rhs) const;
    rational operator* (const rational& rhs) const;
    rational operator/ (const rational& rhs) const;
    rational operator% (const rational& rhs) const;

    rational& operator= (const rational& rhs);
    rational& operator+= (const rational& rhs);
    rational& operator-= (const rational& rhs);
    rational& operator*= (const rational& rhs);
    rational& operator/= (const rational& rhs);
    rational& operator%= (const rational& rhs);

    rational& operator++ ();
    rational& operator-- ();
    rational operator++ (int);
    rational operator-- (int);

    bool operator== (const rational& rhs) const;

};