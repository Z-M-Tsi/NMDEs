#include <iostream>
#include "../include/DenseMat/DenseMat.h"


int main() {
    // Initialize a 3x3 matrix
    myDenseMat::DenseMat<double> A(3, 3);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 0;
    A(1, 0) = 0;  A(1, 1) = 1; A(1, 2) = 1;
    A(2, 0) = 1; A(2, 1) = 0;  A(2, 2) = 1;

    std::cout << "Original Matrix A:" << std::endl;
    A.print();

    // Perform QR decomposition
    auto [Q, R] = A.QR("Householder");
    std::cout << "\nMatrix Q:" << std::endl;
    Q.print();
    std::cout << "\nMatrix R:" << std::endl;
    R.print();

    auto QR = Q * R;
    std::cout << "\nMatrix Q * R:" << std::endl;
    QR.print();

    return 0;
}