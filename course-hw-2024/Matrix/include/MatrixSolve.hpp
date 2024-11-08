#ifndef MATRIXSOLVE_HPP
#define MATRIXSOLVE_HPP

#include"Matrix.h"

namespace mymatrix{
template <typename T>
Matrix<T> Matrix<T>::Gausssolve(const Matrix<T> &b) const
{
    auto lu_result = LU(); 
    Matrix<T> LU_matrix = lu_result.first;
    std::pair<int, int>* swap_order = lu_result.second;

    int n = LU_matrix.rows;

    if (b.rows != n || b.cols != 1) {
        throw std::runtime_error("Matrix dimensions do not match for equation Ax = b");
    }

    Matrix<T> y(b);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            y.data[i] -= LU_matrix.data[i*n + j] * y.data[j];
        }
        y.data[i] /= LU_matrix.data[i*n + i];
    }

    Matrix<T> x(b);
    for (int i = n-1; i >= 0; --i) {
        for (int j = i+1; j < n; ++j) {
            x.data[i] -= LU_matrix.data[i*n + j] * x.data[j];
        }
        x.data[i] /= LU_matrix.data[i*n + i];
    }

    for (int i = 0; i < n; ++i) {
        if (swap_order[i].first != swap_order[i].second) {
            std::swap(x.data[swap_order[i].first], x.data[swap_order[i].second]);
        }
    }

    return x;
}



} // namespace mymatrix


#endif