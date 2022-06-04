#include "gist.h"
#include <iostream>

int main() {
	Gist<int, std::string> a;
	std::pair<int, std::string> p = {8, "aaa"};
	std::cout << 1 << std::endl;
	a.add(p);
	std::cout << a[8] << std::endl;
	a.add(p);
	return 0;
}