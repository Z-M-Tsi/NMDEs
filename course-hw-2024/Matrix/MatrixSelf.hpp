#ifndef MATRIXSELF_HPP
#define MATRIXSELF_HPP
#include "Matrix.h"

namespace mymatrix {
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

}

#endif // MATRIXSELF_HPP