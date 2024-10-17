#ifndef MATRIXSELF_HPP
#define MATRIXSELF_HPP
#include "Matrix.h"
#include <utility>
#include <cmath>

namespace mymatrix {
template <typename T>
inline int Matrix<T>::findpivot(int r) const {
    int n = rows;
    int pivot = r;
    for (int i=r+1; i<n; ++i) {
        if (std::abs(data[i*n+r]) > std::abs(data[pivot*n+r])) {
            pivot = i;
        }
    }
    return pivot;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[j*rows+i] = data[i*cols+j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::inverse() const {
    if (rows != cols) {
        throw std::invalid_argument("Matrix must be square to be invertible");
    }
    int n = rows;
    Matrix<T> result = eyes(n);

    T* tmp_data = new T[n*n];
    for (int i=0; i<n*n; ++i) {
        tmp_data[i] = data[i];
    }

    std::vector<std::pair<int, int>> swap_order; 

    for (int r=0; r<n; ++r) {
        for (int i=r; i<n; ++i) { // Forward elimination
            for (int k=0; k<r; ++k) {
                tmp_data[i*n+r] -= tmp_data[i*n+k] * tmp_data[k*n+r]; 
            }
        }
        int pivot = findpivot(r); // Find pivot
        if (pivot != r) { // Swap rows
            swap_order.emplace_back(r, pivot);
            for (int i=0; i<n; ++i) {
                std::swap(tmp_data[r*n+i], tmp_data[pivot*n+i]);
            }
        }
        if (fabs(tmp_data[r * n + r]) < 1e-15) {
            delete[] tmp_data;
            throw std::runtime_error("Matrix is singular and cannot be inverted");
        }
        for (int i=r+1; i<n; ++i) { // Compute the r-th row of U and the r-th column of L
            tmp_data[i*n+r] /= tmp_data[r*n+r];
            for (int k=0; k<r; ++k) {
                tmp_data[r*n+i] -= tmp_data[r*n+k] * tmp_data[k*n+i];
            }  
        }
    }

    for (int r=n-1; r>=0; --r){ // Backward elimination for inv(U)
        result.data[r*n+r] = 1.0/tmp_data[r*n+r];
        for (int j=r; j<n; ++j) {
            if (j > r) {
                tmp_data[r*n+j] *= result.data[r*n+r];
                result.data[r*n+j] *= result.data[r*n+r];
            }
            for (int k=r-1; k>=0; --k) {
                result.data[k*n+j] -= tmp_data[k*n+r] * result.data[r*n+j];
            }
        }
    }

    for (int r=0; r<n; ++r) { // Forward elimination for inv(L)
        T tmp = result.data[r*n+r];
        result.data[r*n+r] = 1.0;
        for (int j=0; j<=r; ++j) {
            for (int k=r+1; k<n; ++k) {
                result.data[k*n+j] -= tmp_data[k*n+r] * result.data[r*n+j];
            }
        }
        result.data[r*n+r] = tmp;
    }

    for (int i=0; i<n; ++i){
        tmp_data[i*n+i] = 1.0;
        for (int j=i+1; j<n; ++j){
            tmp_data[j*n+i] = result.data[j*n+i];
            result.data[j*n+i] = 0.0;
            tmp_data[i*n+j] = 0.0;
        }
    }


    T* tmp_prod = new T[n*n];
    for (int i=0; i<n; ++i) { // Multiply inv(U) * inv(L)
        for (int j=0; j<n; ++j) {
            T sum = 0;
            for (int k=0; k<n; ++k) {
                sum += result.data[i*n+k] * tmp_data[k*n+j];
            }
            tmp_prod[i*n+j] = sum;
        }
    }
    std::swap(result.data, tmp_prod);
    
    for (auto it = swap_order.rbegin(); it != swap_order.rend(); ++it) { // Swap columns
        int row1 = it->first;
        int row2 = it->second;

        for (int i = 0; i < n; ++i) {
            std::swap(result.data[i * n + row1], result.data[i * n + row2]);
        }
    }

    delete[] tmp_prod;
    delete[] tmp_data;
    return result;

}

}

#endif // MATRIXSELF_HPP