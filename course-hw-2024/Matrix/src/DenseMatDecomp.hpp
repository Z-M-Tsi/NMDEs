#pragma once

#include "../include/DenseMat/DenseMat.h"
#include <string>

namespace myDenseMat{
template <typename T>
std::pair<DenseMat<T>, std::vector<std::pair<int, int>>> DenseMat<T>::LU() const {
    if (rows != cols) {
        throw std::runtime_error("Matrix must be square to be decomposed");
    }

    int n = rows;
    DenseMat<T> result(*this);
    std::vector<std::pair<int, int>> swap_order; 
    for (int r = 0; r < n; ++r) {
        // Forward elimination
        for (int i = r; i < n; ++i) {
            for (int k = 0; k < r; ++k) {
                result.data[i * n + r] -= result.data[i * n + k] * result.data[k * n + r];
            }
        }

        int pivot = selectPivot(r); // Select pivot
        if (pivot != r) { // Swap rows if necessary
            swap_order.push_back({r, pivot}); // Record the swap
            // Perform row swap
            for (int i = 0; i < n; ++i) {
                std::swap(result.data[r * n + i], result.data[pivot * n + i]);
            }
        }

        // Compute the r-th row of U and the r-th column of L
        for (int i = r + 1; i < n; ++i) {
            result.data[i * n + r] /= result.data[r * n + r];
            for (int k = 0; k < r; ++k) {
                result.data[r * n + i] -= result.data[r * n + k] * result.data[k * n + i];
            }
        }
    }

    return std::make_pair(result, swap_order);
}

template <typename T>
DenseMat<T> DenseMat<T>::Cholesky() const { // M = LDL^T

    int n = rows;
    DenseMat<T> result(*this);
    for (int i=0; i<n; ++i) {
        for (int j=0; j<i; ++j) {
            T sum = 0.0;
            for (int k=0; k<j; ++k) {
                sum += result.data[i*n+k] * result.data[k*n+k] * result.data[j*n+k];
            }
            result.data[i*n+j] = (result.data[i*n+j] - sum) / result.data[j*n+j];
            result.data[j*n+i] = 0.0;
        }
        T sum = 0.0;
        for (int k=0; k<i; ++k) {
            sum += result.data[i*n+k] * result.data[k*n+k] * result.data[i*n+k];
        }
        result.data[i*n+i] = result.data[i*n+i] - sum;
        if (result.data[i*n+i] < 1e-15) {
            throw std::runtime_error("Matrix is not positive definite");
        }
    }
    return result;
}

template <typename T>
std::pair<DenseMat<T>, DenseMat<T>> DenseMat<T>::QR(const std::string &flag) const {
    if (rows != cols) {
        throw std::runtime_error("Matrix must be square to be decomposed");
    }

    int n = rows;
    DenseMat<T> R = myDenseMat::zeros<T>(n, n);  
    DenseMat<T> Q(*this);  

    

    for (int i=0; i<n; ++i) {
        T norm = 0.0;
        for (int j = 0; j < n; ++j) {
            norm += Q.data[j*n+i] * Q.data[j*n+i];
        }
        norm = std::sqrt(norm);
        R.data[i*n+i] = norm;

        for (int j=0; j<n; ++j) {
            Q.data[j * n + i] /= norm;
        }

        for (int j=i+1; j<n; ++j) {
            T dot = 0.0;
            for (int k = 0; k < n; ++k) {
                dot += Q.data[k*n+i] * Q.data[k*n+j];
            }
            R.data[i*n+j] = dot;
            for (int k=0; k<n; ++k) {
                Q.data[k*n+j] -= dot * Q.data[k*n+i];
            }
        }
    }

    return std::make_pair(Q, R);
}

} // namespace myDenseMat