#include<iostream>
#include <iomanip>
#include <cmath>

double tol = 1e-6;

double func(double x) {
    return sin(10*x) - x;
}

double bisect(double a, double b) {
    double c = (a + b) / 2;
    double fa = func(a);
    double fb = func(b);
    double fc = func(c); 

        if (abs(fc) < tol) {
            return a, b, c;
        } else if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
}

int main(int argc, char* argv[]) {
    double a = -1;
    double b = 1;
    double c;

    std::cout << "==========>> BISECTION METHOD <<==========" << std::endl;
    a, b, c = bisect(a, b);
    while (a-c > tol) {
        a, b, c = bisect(a, b);
    }
    

    return 0;
}