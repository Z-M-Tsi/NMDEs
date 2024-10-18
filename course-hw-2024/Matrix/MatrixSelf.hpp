#ifndef MATRIXSELF_HPP
#define MATRIXSELF_HPP
#include "Matrix.h"

namespace mymatrix {
template <typename T>
inline int Matrix<T>::selectPivot(int r) const {
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
double Matrix<T>::det() const {
    if (rows != cols) {
        throw std::invalid_argument("Matrix must be square to compute determinant");
    }
    int n = rows;
    Matrix<T> result(*this);
    double Det = 1.0;
    for (int r=0; r<n; ++r) {
        int pivot = selectPivot(r);
        if (pivot != r) {
            Det = -Det;
            for (int i=0; i<n; ++i) {
                std::swap(result.data[r*n+i], result.data[pivot*n+i]);
            }
        }
        Det *= result.data[r*n+r];
        if (fabs(result.data[r*n+r]) < 1e-15) {
            return 0.0;
        }
        for (int i=r+1; i<n; ++i) {
            result.data[i*n+r] /= result.data[r*n+r];
            for (int k=r+1; k<n; ++k) {
                result.data[i*n+k] -= result.data[i*n+r] * result.data[r*n+k];
            }
        }
    }
    return Det;
}

template <typename T>
Matrix<T> Matrix<T>::inverse() const {
    if (rows != cols) {
        throw std::invalid_argument("Matrix must be square to be invertible");
    }
    int n = rows;
    Matrix<T> result(*this);
    std::pair<int, int>* swap_order = new std::pair<int, int>[n]; 

    for (int r=0; r<n; ++r) {
        for (int i=r; i<n; ++i) { // Forward elimination
            for (int k=0; k<r; ++k) {
                result.data[i*n+r] -= result.data[i*n+k] * result.data[k*n+r]; 
            }
        }
        int pivot = selectPivot(r); // Select pivot
        if (pivot != r) { // Swap rows
            swap_order[r] = std::make_pair(r, pivot);
            for (int i=0; i<n; ++i) {
                std::swap(result.data[r*n+i], result.data[pivot*n+i]);
            }
        }
        if (fabs(result.data[r * n + r]) < 1e-15) {
            delete[] swap_order;
            throw std::runtime_error("Matrix is singular and cannot be inverted");
        }
        for (int i=r+1; i<n; ++i) { // Compute the r-th row of U and the r-th column of L
            result.data[i*n+r] /= result.data[r*n+r];
            for (int k=0; k<r; ++k) {
                result.data[r*n+i] -= result.data[r*n+k] * result.data[k*n+i];
            }  
        }
    }

    /* 
        * Now we have the LU decomposition of the matrix
        * L is stored in the lower triangular part of the matrix (i > j)
        * U is stored in the upper triangular part of the matrix (i <= j)
    */

    for (int i=n-1; i>=0; --i) { // Backward elimination for inv(U)
        result.data[i*n+i] = 1.0 / result.data[i*n+i];  
        for (int j=i-1; j>=0; --j) {
            T sum = 0.0;
            for (int k=j+1; k<=i; ++k) {
                sum += result.data[j*n+k] * result.data[k*n+i];
            }
            result.data[j*n+i] = -sum / result.data[j*n+j];
        }
    }
    for (int r = 0; r < n; ++r) { // Forward elimination for inv(L)
        for (int j = 0; j < r; ++j) {
            T sum = 0.0;
            for (int k = j; k < r; ++k) {
                T Lkj = (k == j) ? 1.0 : result.data[k * n + j];  
                sum += result.data[r * n + k] * Lkj;
            }
            result.data[r * n + j] = -sum;
        }
    }

    T* tmp_data = new T[n*n];
    for (int i = 0; i < n; ++i) { // Compute inv(A) = inv(U) * inv(L)
        for (int j = 0; j < n; ++j) {  
            for (int k=std::max(i, j); k<n; ++k) {   
                T Lkj = (k==j) ? 1.0 : result.data[k*n+j];  
                tmp_data[i*n+j] += result.data[i*n+k] * Lkj;
            }
        }
    }
    std::swap(result.data, tmp_data);
    
    for (int i = n-1; i >= 0; --i) { // Swap columns
        int row1 = swap_order[i].first;
        int row2 = swap_order[i].second;
        for (int j = 0; j < n; ++j) {
            std::swap(result.data[j * n + row1], result.data[j * n + row2]);
        }
    }

    delete[] swap_order;
    delete[] tmp_data;
    return result;
}

}

#endif // MATRIXSELF_HPP