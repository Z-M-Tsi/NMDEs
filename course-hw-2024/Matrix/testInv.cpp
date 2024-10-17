#include"Matrix.h"

int main(int argc, char* argv[]) {
    mymatrix::Matrix<double> A(3, 3);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
    A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 10;
    // A.print();
    mymatrix::Matrix<double> B = A.inverse();
    B.print();
    mymatrix::Matrix<double> C = A * B;
    C.print();
    return 0;
}