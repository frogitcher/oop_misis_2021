#include <iostream>
#include "hist.h"
#include <vector>


int main() {
    Hist<std::string> hist;
    hist.append("Январь", 150);
    hist.append("Февраль", 200);
    std::cout << hist.median() << "\n";
    std::cout << hist.mean() << "\n";

    std::cout << hist.get("Январь") << "\n";
    std::cout << hist["Январь"] << "\n";

    hist.del("Январь");
    std::cout << hist["Январь"] << "\n";

    return 0;
}
