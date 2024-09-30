#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include "iter_methods.h"

const double eps = 1e-8;
const int max_iter = (int)1e4;

double f(double x) {
    return pow(x, 4) - 4*x*x + 4;
}

double f_diff(double x) {
    return 4*pow(x, 3) - 8*x;
}

int main(int argc, char* argv[]) {
    double x0 = 1.0;
    double x_star;
    double alpha = 0.5;

    // Newton's method
    std::vector<double> roots_newton = iter::newton(f, f_diff, x0, eps, max_iter);
    std::cout << "Root found by Newton's method:" << std::endl;
    x_star = roots_newton.back();
    std::cout << "x" << " = " << x_star << std::endl;
    roots_newton.pop_back();

    // Convergence order of Newton's method
    std::vector<double> errors_newton = iter::abs_errors(roots_newton, x_star);
    iter:: error_order(errors_newton);
    std::cout << "=============== >> END << ===============" << std::endl;
    std::cout << std::endl;

    // Newton down hill method
    std::vector<double> roots_newton_down_hill = iter::newton_down_hill(f, f_diff, x0, eps, max_iter, alpha);
    std::cout << "Roots find by Newton down hill method:" << std::endl;
    x_star = roots_newton_down_hill.back();
    std::cout << "x" << " = " << x_star << std::endl;
    roots_newton_down_hill.pop_back();

    // Convergence order of Newton down hill method
    std::vector<double> errors_newton_down_hill = iter::abs_errors(roots_newton_down_hill, x_star);
    iter:: error_order(errors_newton_down_hill);
    std::cout << "=============== >> END << ===============" << std::endl;
    std::cout << std::endl;

    // Iteration with Aitken's technique
    std::vector<double> roots_iter_Aitken = iter::iter_Aitken(f, x0, eps, max_iter);
    std::cout << "Roots find by iteration with Aitken's technique:" << std::endl;
    x_star = roots_iter_Aitken.back();
    std::cout << "x" << " = " << x_star << std::endl;
    roots_iter_Aitken.pop_back();
    
    // Convergence order of iteration with Aitken's technique
    std::vector<double> errors_iter_Aitken = iter::abs_errors(roots_iter_Aitken, x_star);
    iter:: error_order(errors_iter_Aitken);
    std::cout << "=============== >> END << ===============" << std::endl;
    std::cout << std::endl;

    return 0;
}