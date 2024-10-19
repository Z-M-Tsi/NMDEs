#ifndef MATRIXPRIVATE_HPP
#define MATRIXPRIVATE_HPP

#include"Matrix.h"

namespace mymatrix{
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
bool Matrix<T>::isSymmetric() const {
    for (int i=0; i<rows; ++i) {
        for (int j=0; j<i; ++j) {
            if (data[i*rows+j] != data[j*rows+i]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
Matrix<T> Matrix<T>::Cholesky() const { // M = LDL^T

    int n = rows;
    Matrix<T> result(*this);
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
Matrix<T> Matrix<T>::symPosiInverse() const { 
    
    Matrix<T> result = Cholesky();
    int n = rows;

    for (int r = 0; r < n; ++r) { // Forward elimination for inv(L)
        result.data[r*n+r] = 1.0 / result.data[r*n+r]; // inv(D) = 1./D
        for (int j=0; j<r; ++j) {
            T sum = 0.0;
            for (int k=j; k<r; ++k) {
                T Lkj = (k==j) ? 1.0 : result.data[k*n+j];  
                sum += result.data[r*n+k] * Lkj;
            }
            result.data[r*n+j] = -sum;
            result.data[j*n+r] = -sum;
        }
    }


    T* tmp_data = new T[n];
    for (int i = 0; i < n; ++i) { // Compute inv(A) = inv(L^T) * inv(D) * inv(L)
        for (int j = 0; j <= i; ++j) { 
            tmp_data[j] = 0.0; 
            for (int k=std::max(i, j); k<n; ++k) {   
                T Lki = (k==i) ? 1.0 : result.data[k*n+i];
                T Lkj = (k==j) ? 1.0 : result.data[k*n+j];  
                tmp_data[j] += Lki * result.data[k*n+k] * Lkj;
            }
            result.data[i*n+j] = tmp_data[j];
            result.data[j*n+i] = tmp_data[j];
        }
    }

    
    
    return result;
}


} // namespace mymatrix

#endif // MATRIXPRIVATE_HPP