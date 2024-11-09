#include "../Matrix/include/DenseMat/DenseMat.h" 
#include <iostream>

template <typename T>
myDenseMat::DenseMat<T> genHilbert(int n) {
    myDenseMat::DenseMat<T> H(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            H(i, j) = 1.0 / (i + j + 1);
        }
    }
    return H;
}

int main(int argc, char* argv[]) {
    
    for (int n = 2; n <= 7; n++) {
        myDenseMat::DenseMat<float> H = genHilbert<float>(n);
        std::cout << "n = " << n << ":\n";
        
        myDenseMat::DenseMat<float> x_sol = myDenseMat::ones<float>(n, 1);

        myDenseMat::DenseMat<float> b = H * x_sol;
        myDenseMat::DenseMat<float> x = myDenseMat::GaussSolve(H, b);

        float max_error = 0.0;
        for (int i = 0; i < n; i++) {
            float tmp = fabs(x(i, 0) - x_sol(i, 0));
            if (tmp > max_error) {
                max_error = tmp;
            }
        }
        
        std::cout << "Maximal absolute error: " << max_error << std::endl;
    }



    return 0;
}