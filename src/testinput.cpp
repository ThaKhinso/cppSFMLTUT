#include <iostream>
#include <vector>


int main() {
    std::vector<int>crap;
    crap.reserve(3);
    crap.push_back(1);
    crap[2] = 3;
    {
        crap[0] = 123;
    }
    std::cout << crap[0] << "\n";
    
}