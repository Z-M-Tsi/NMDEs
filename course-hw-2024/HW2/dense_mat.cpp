#include "../Matrix/Matrix.h"
#include <iostream>
#include <chrono>

int getElement(int n, int small, int big) {
    return (1+small) * (n - big);
}

mymatrix::Matrix<float> getCyclic(int n) {
    mymatrix::Matrix<float> A(n, n);
    float factor =  1.0 / (n + 1);
    for (int i = 0; i < n; i++) {
        A(i, i) = factor * getElement(n, i, i);
        for (int j = i+1; j < n; j++) {
            float element = (float) getElement(n, i, j);
            A(i, j) = factor*element;
            A(j, i) = factor*element;
        }
    }
    return A;
}

void benchmark(int n) {
    std::cout << "Benchmarking with size: " << n << "x" << n << "\n";

    mymatrix::Matrix<float> MA = getCyclic(n);

    auto start = std::chrono::high_resolution_clock::now();
    mymatrix::Matrix<float> MC = MA.inverse("symPosi");
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Inverse Time with Matrix.h: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    std::cout << "Benchmarking finished!\n\n";
}


int main(int argc, char* argv[]) {

    mymatrix::Matrix<float> A1 = getCyclic(4);
    mymatrix::Matrix<float> A1inv = A1.inverse("symPosi");
    std::cout << "The inverse matrix for n = 4:\n\n";
    A1inv.print();
    std::cout << std::endl;

    mymatrix::Matrix<float> A2 = getCyclic(8);
    mymatrix::Matrix<float> A2inv = A2.inverse("symPosi");
    std::cout << "The inverse matrix for n = 8:\n\n";
    A2inv.print();
    std::cout << std::endl;

    benchmark(100);
    benchmark(200);
    benchmark(400);
    benchmark(800);

    return 0;
}