#include "../Matrix/include/Matrix.h"
#include <iostream>

template <typename T>
mymatrix::Matrix<T> genHilbert(int n) {
    mymatrix::Matrix<T> H(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            H(i, j) = 1.0 / (i + j + 1);
        }
    }
    return H;
}

int main(int argc, char* argv[]) {
    
    for (int n = 2; n <= 10; n++) {
        mymatrix::Matrix<float> H = genHilbert<float>(n);
        std::cout << "n = " << n << ":\n";
        
        mymatrix::Matrix<float> x_sol(n, 1);

        for (int i = 0; i < n; i++) {
            x_sol(i, 0) = 1.0;
        }
        mymatrix::Matrix<float> b = H * x_sol;
        mymatrix::Matrix<float> x = H.Gausssolve(b);
        x.print();

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