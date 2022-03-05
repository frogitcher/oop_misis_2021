#include "rational.h"
#include <iostream>

int main(){
    Rational a = Rational(1, 2);
    std::cout <<a.GetNumerator() << " "<< a.GetDenominator();
    return 0;
}