#include <iostream>
#include <vector>
#include"../include/DenseMat/DenseMat.h"  // Include your matrix class header

// Define a simple 3x3 matrix and 3x1 vector

void testGaussSolve() {
    // Define a 3x3 matrix A
    myDenseMat::DenseMat<float> A(3, 3);
    A(0, 0) = 2;  A(0, 1) = 1;  A(0, 2) = -1;
    A(1, 0) = -3; A(1, 1) = -1; A(1, 2) = 2;
    A(2, 0) = -2; A(2, 1) = 1;  A(2, 2) = 2;

    // Define a 3x1 vector b
    myDenseMat::DenseMat<float> b(3, 1);
    b(0, 0) = 8;
    b(1, 0) = -11;
    b(2, 0) = -3;

    
        // Solve for x in Ax = b
        myDenseMat::DenseMat<float> x = myDenseMat::GaussSolve(A, b);

        // Output the solution
        std::cout << "Solution vector x:\n";
        for (int i = 0; i < x.get_rows(); ++i) {
            std::cout << x(i, 0) << std::endl;
        }
    
}

int main() {
    testGaussSolve(); 
    return 0;
}
