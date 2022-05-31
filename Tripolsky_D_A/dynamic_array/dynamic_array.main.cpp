#include "dynamic_array.h"
#include <vector>
#include <iostream>

using namespace Tripolsky_D_A;

int main() {
    DynamicArray<int> v{1, 2, 3, 4, 5, 6};
    auto it=v.begin();
    it++;/*
    std::cout << ((*it)==2) <<'\n';
    it=v.begin();
    std::swap(v[0], v[1]);
    std::cout << ((*it) == 2) <<'\n';
    it=v.begin();
    for (int i = 0; i < 667; ++i) {
        v.push_back(i);
    }

    it+=672;
    std::cout << ((*it)==666) <<'\n';
    it=v.begin();
    it+=v.size();
    std::cout << ((it == v.end())) <<'\n';
    std::cout << (*(v.end()-1)==6) <<'\n';
    it=v.begin();
    std::cout << (*(it+1) ==2) <<'\n';
    it+=4;
    std::cout << (*(it) == 5) <<'\n';
    std::cout << (*(it-2)==3) <<'\n';
    it-=2;
    std::cout << (*(it)==3) <<'\n';
    std::cout << (*(it++)==3) <<'\n';
    std::cout << (*(it)==4) <<'\n';
    std::cout << (*(it--)==4) <<'\n';
    std::cout << (*(it)==3) <<'\n';
    std::cout << (*(++it)==4) <<'\n';
    std::cout << (*(--it)==3) <<'\n';
*/

    std::cout << v.front();


    return 0;
}