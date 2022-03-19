#include "rational.h"
#include <iostream>

int main(){
    Rational a(1, 2);
    std::cout <<a.GetNumerator() << " "<< a.GetDenominator();
    return 0;
}