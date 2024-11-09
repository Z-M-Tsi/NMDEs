#include"../include/DenseMat/DenseMat.h"
#include <chrono>
#include <iostream>
#include <exception>

void testAdd(myDenseMat::DenseMat<float> A, myDenseMat::DenseMat<float> B);
void testSubtract(myDenseMat::DenseMat<float> A, myDenseMat::DenseMat<float> B);
void testMultiply(myDenseMat::DenseMat<float> A, myDenseMat::DenseMat<float> B);
void testInverse(myDenseMat::DenseMat<float> A);
void testTranspose(myDenseMat::DenseMat<float> A);
// void testDet(myDenseMat::DenseMat<float> A);
void testSubMatrix(myDenseMat::DenseMat<float> A);

int main() {
    int rows = 10, cols = 10;
    float min_value = 0, max_value = 1;

    myDenseMat::DenseMat<float> A = myDenseMat::randomMatrix(rows, cols,min_value,max_value);
    myDenseMat::DenseMat<float> B = myDenseMat::randomMatrix(rows, cols,min_value,max_value); 
    std::cout << "Testing all basic matrix operations...\n";

    testAdd(A, B);
    testSubtract(A, B);
    testMultiply(A, B);
    testInverse(A);
    testTranspose(A);
    testSubMatrix(A);

    

    std::cout << "All Basic functions tested successfully!\n";

    return 0;
}

void testAdd(myDenseMat::DenseMat<float> A, myDenseMat::DenseMat<float> B)
{
    std::cout << "Begin to test addition...\n";
    myDenseMat::DenseMat<float> C = A + B;
    int rows = A.get_rows();
    int cols = A.get_cols();

    bool additionPassed = true;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (C(i, j) != A(i, j) + B(i, j)) {
                additionPassed = false;
                std::cerr << "Addition test failed at (" << i << ", " << j << ")!\n";
            }
        }
    }
    if (additionPassed) std::cout << "Addition test passed!\n";
}

void testSubtract(myDenseMat::DenseMat<float> A, myDenseMat::DenseMat<float> B)
{
    std::cout << "Begin to test subtraction...\n";
    myDenseMat::DenseMat<float> C = A - B;
    int rows = A.get_rows();
    int cols = A.get_cols();

    bool subtractionPassed = true;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (C(i, j) != A(i, j) - B(i, j)) {
                subtractionPassed = false;
                std::cerr << "Subtraction test failed at (" << i << ", " << j << ")!\n";
            }
        }
    }
    if (subtractionPassed) std::cout << "Subtraction test passed!\n";
}

void testMultiply(myDenseMat::DenseMat<float> A, myDenseMat::DenseMat<float> B)
{
    std::cout << "Begin to test multiplication...\n";
    myDenseMat::DenseMat<float> C = A * B;
    int rows = A.get_rows();
    int cols = B.get_cols();
    int common = A.get_cols();

    bool multiplicationPassed = true;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float sum = 0;
            for (int k = 0; k < common; ++k) {
                sum += A(i, k) * B(k, j);
            }
            if (C(i, j) != sum) {
                multiplicationPassed = false;
                std::cerr << "Multiplication test failed at (" << i << ", " << j << ")!\n";
            }
        }
    }
    if (multiplicationPassed) std::cout << "Multiplication test passed!\n";
}

void testInverse(myDenseMat::DenseMat<float> A)
{
    std::cout << "Begin to test inverse...\n";
    myDenseMat::DenseMat<float> B = A.inverse();
    myDenseMat::DenseMat<float> C = A * B;
    int rows = A.get_rows();
    int cols = A.get_cols();
    C.print();

    bool inversePassed = true;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == j) {
                if (std::abs(C(i, j) - 1) > 1e-6) {
                    inversePassed = false;
                    std::cerr << "Inverse test failed at (" << i << ", " << j << ")!\n";
                }
            } else {
                if (std::abs(C(i, j)) > 1e-6) {
                    inversePassed = false;
                    std::cerr << "Inverse test failed at (" << i << ", " << j << ")!\n";
                }
            }
        }
    }
    if (inversePassed) std::cout << "Inverse test passed!\n";
}

void testTranspose(myDenseMat::DenseMat<float> A)
{
    std::cout << "Begin to test transpose...\n";
    myDenseMat::DenseMat<float> B = A.transpose();
    int rows = A.get_rows();
    int cols = A.get_cols();

    bool transposePassed = true;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (A(i, j) != B(j, i)) {
                transposePassed = false;
                std::cerr << "Transpose test failed at (" << i << ", " << j << ")!\n";
            }
        }
    }
    if (transposePassed) std::cout << "Transpose test passed!\n";
}

void testSubMatrix(myDenseMat::DenseMat<float> A)
{
    std::cout << "Begin to test submatrix...\n";
    int rows = A.get_rows();
    int cols = A.get_cols();
    int init_row = 1, final_row = 5, init_col = 2, final_col = 7;
    myDenseMat::DenseMat<float> B = A.subMatrix(init_row, final_row, init_col, final_col);

    bool subMatrixPassed = true;
    for (int i = init_row; i < final_row; ++i) {
        for (int j = init_col; j < final_col; ++j) {
            if (A(i, j) != B(i - init_row, j - init_col)) {
                subMatrixPassed = false;
                std::cerr << "Submatrix test failed at (" << i << ", " << j << ")!\n";
            }
        }
    }
    if (subMatrixPassed) std::cout << "Submatrix test passed!\n";
}
