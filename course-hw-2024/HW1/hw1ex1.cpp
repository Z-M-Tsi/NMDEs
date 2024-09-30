#include<iostream>
#include <iomanip>

int main(int argc, char* argv[]) {
    double c_double = 2;
    float c_float = 2;
    int round = 0;

    std::cout << "==========>> DOUBLE VERSION <<==========" << std::endl;
    while (c_double > 1) {
        std::cout << std::fixed << std::setprecision(8);    
        std::cout << "Round " << round << ", c = " << c_double << std::endl;
        c_double = (c_double + 1) / 2;
        round += 1;
    }

    round = 0;
    std::cout << "==========>> FLOAT VERSION <<==========" << std::endl;
    while (c_float > 1) {    
        std::cout << std::fixed << std::setprecision(6); 
        std::cout << "Round " << round << ", c = " << c_float << std::endl;
        c_float = (c_float + 1) / 2;
        round += 1;
    }

    return 0;
}