#include "exam.h"
#include <iostream>

int main() {
    Vector a(5, 2);
    Vector b(5, 3);
    Vector c(5, 3);
    c = a + b;
    std::cout << c[2];
    return 0;
}
