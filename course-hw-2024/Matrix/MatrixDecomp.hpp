#ifndef MATRIXDECOMP_HPP
#define MATRIXDECOMP_HPP

#include"Matrix.h"

namespace mymatrix{
template <typename T>
Matrix<T> Matrix<T>::DecompCholesky() const { // M = LDL^T

    if (!isSymmetric()) {
        throw std::runtime_error("Matrix is not symmetric");
    }

    return Cholesky();

}

}

#endif // MATRIXDECOMP_HPP