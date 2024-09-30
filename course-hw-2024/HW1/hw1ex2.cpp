#include<iostream>
#include<iomanip>
#include<cmath>

const double eps = 1e-15;

double f(double x, int n) {
    return pow(x, n)*exp(x);
}

double trap_adap(double a, double b, int n, double tol){
    double h = b - a;
    double c = (a+b)/2.0;
    double S0 = (h/2.0)*(f(a, n) + f(b, n));
    double S1 = (h / 4.0) * (f(a, n) + 2 * f(c, n) + f(b, n));;
    double err = fabs(S1 - S0);

    if (err < tol) {
        return S1;
    }
    else {
        return trap_adap(a, c, n, tol) + trap_adap(c, b, n, tol);
    }

}

int main(int argv, char* argc[]) {
    double a = 0.0, b = 1.0;
    double tol = 3.0*eps/(b-a);

    for (int i = 1; i <= 1000; i++) {
        if (i % 50 == 0)
        {std::cout << "n = " << i << ": " << std::fixed << std::setprecision(15) 
        << trap_adap(a, b, i, tol) << std::endl;}
    }

    return 0;
}