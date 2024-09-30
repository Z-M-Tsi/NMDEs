#include<iostream>
#include<iomanip>
#include<cmath>

const double eps = 1e-6;
const int max_iter = (int)1e4;

double f(double x) {
    return x*x + x - 2.0;
}

double phi(double x) {
    return x*x + 2.0*x - 2.0;
}

int main(int argc, char* argv[]) {
    int iter = 0;
    double x0, x1;
    double init_guesses[5] = {-0.5, -0.05, 0.1, 0.5, 0.9};
    double res;
    
    for (int i = 0; i < 5; i++) {
        iter = 0;
        x0 = init_guesses[i];
        x1 = phi(x0);
        res = fabs(f(x1));

        std::cout << std::endl;
        std::cout << "===============>> Start with x0 = " << x0 << " <<===============" << std::endl;
        while (res > eps && iter < max_iter) {
            if (iter % 500 == 0 && iter != 0) {
                std::cout << "At round " << iter << ", x_previous = " << x0 
                << ", x_new = " << x1 << ", residual = " << res << std::endl;
            }
            x0 = x1;
            x1 = phi(x0);
            res = fabs(f(x1));
            iter += 1;
        }
        if (iter == max_iter) {
            std::cout << "After "<< max_iter << " iterations, the method did not converge for x0 = " 
            << init_guesses[i] << "." << std::endl;
        }
        if (res <= eps)
            {std::cout << "Converged for x0 = " << init_guesses[i] 
            << " at round " << iter << "! Now x_previous = " << x0 
            << ", x_new = " << x1 << ", residual = " << res << "." << std::endl;}
    }
}