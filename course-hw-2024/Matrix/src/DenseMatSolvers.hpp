#pragma once

#include "../include/DenseMat/DenseMat.h"

namespace myDenseMat{
template <typename T>
myDenseMat::DenseMat<T> GaussSolve(myDenseMat::DenseMat<T> A, myDenseMat::DenseMat<T> b){
    if (A.get_rows() != A.get_cols()) {
        throw std::invalid_argument("Matrix must be square to be decomposed");
    }

    if (A.get_rows() != b.get_rows()) {
        throw std::invalid_argument("Matrix and vector dimensions do not match");
    }

    int n = A.get_rows();
    myDenseMat::DenseMat<T> x(b);

    std::pair<myDenseMat::DenseMat<T>, std::vector<std::pair<int, int>>> result = A.LU();
    myDenseMat::DenseMat<T> LU_result = result.first;
    std::vector<std::pair<int, int>> swap_order = result.second;


    for (int i=swap_order.size()-1; i>=0; --i) { // Swap rows of b
        int row1 = swap_order[i].first;
        int row2 = swap_order[i].second;
        std::swap(x(row1, 0), x(row2, 0));
    }

    for (int i = 0; i < n; ++i) {
        T sum = 0;
        for (int j = 0; j < i; ++j) {
            sum += LU_result(i, j) * x(j, 0);
        }
        x(i, 0) = x(i, 0) - sum;
    }

    for (int i = n - 1; i >= 0; --i) {
        T sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += LU_result(i, j) * x(j, 0);
        }
        x(i, 0) = (x(i, 0) - sum) / LU_result(i, i);
    }

    return x; 
}
} // namespace myDenseMat