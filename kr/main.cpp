#include <iostream>

#include "dict.h"

int main() {
  dict<int> a;
  std::pair<int, double> n(1, 2.5);
  std::pair<int, double> n2(2, 3.5);
  //   n.first = 1;
  //   n.second = 2.5;
  a.add(n);
  a.add(n2);
  a.print();
  std::cout << a.avg() << std::endl;
  std::cout << a.get(1) << std::endl;
  //   a.remove(1);
  //   a.print();
  return 0;
}