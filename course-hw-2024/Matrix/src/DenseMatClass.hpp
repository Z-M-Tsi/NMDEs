#pragma once

#include "../include/DenseMat/DenseMat.h"

namespace myDenseMat{
template <typename T>
DenseMat<T>::DenseMat(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows * cols);
}

template <typename T>
DenseMat<T>::DenseMat(const DenseMat<T>& M) : rows(M.rows), cols(M.cols) {
    data = M.data;
}

template <typename T>
DenseMat<T>::~DenseMat() {
    data.clear();
}

template <typename T>
inline int DenseMat<T>::selectPivot(int r) const {
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
inline bool DenseMat<T>::isSymmetric() const {
    if (rows != cols) {
        return false;
    }
    for (int i=0; i<rows; ++i) {
        for (int j=i+1; j<cols; ++j) {
            if (data[i*cols+j] != data[j*cols+i]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
inline int DenseMat<T>::get_rows() const {
    return rows;
}

template <typename T>
inline int DenseMat<T>::get_cols() const {
    return cols;
}

template <typename T>
inline std::pair<int, int> DenseMat<T>::size() const {
    return std::make_pair(rows, cols);
}

template <typename T>
void DenseMat<T>::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            if (fabs(data[i * cols + j]) < 1e-6)
                std::cout << std::setw(8) << 0 << " ";
            else
                {std::cout << std::setw(8) << data[i * cols + j] << " ";}
        std::cout << std::endl;
    }
}

template <typename T>
DenseMat<T> DenseMat<T>::subMatrix(int init_row, int final_row, int init_col, int final_col) const {
    if (init_row < 0 || init_row >= rows || final_row < 0 || final_row >= rows || init_col < 0 || init_col >= cols || final_col < 0 || final_col >= cols)
        throw std::out_of_range("Index out of range");

    if (init_row > final_row || init_col > final_col)
        throw std::invalid_argument("Invalid submatrix range");

    int sub_rows = final_row - init_row + 1;
    int sub_cols = final_col - init_col + 1;
    DenseMat<T> result(sub_rows, sub_cols);
    for (int i = 0; i < sub_rows; i++) {
        for (int j = 0; j < sub_cols; j++) {
            result.data[i * sub_cols + j] = data[(init_row + i) * cols + init_col + j];
        }
    }
    return result;
}

template <typename T>
const DenseMat<T>& DenseMat<T>::operator=(const DenseMat<T>& M) {
    if (this == &M)
        return *this;
    rows = M.rows;
    cols = M.cols;
    data = M.data;
    return *this;
}

template <typename T>
inline const T& DenseMat<T>::operator()(int row, int col) const {
    return data[row * cols + col];
}

template <typename T>
inline T& DenseMat<T>::operator()(int row, int col)
{
    return data[row * cols + col];
}

template <typename U>
const DenseMat<U> operator*(const DenseMat<U>& lhs, const DenseMat<U>& rhs) {
    if (lhs.cols != rhs.rows)
        throw std::invalid_argument("Matrix dimensions do not match");

    DenseMat<U> result(lhs.rows, rhs.cols);
    for (int i = 0; i < lhs.rows; i++) {
        for (int j = 0; j < rhs.cols; j++) {
            result.data[i * result.cols + j] = 0;
            for (int k = 0; k < lhs.cols; k++) {
                result.data[i * result.cols + j] += lhs.data[i * lhs.cols + k] * rhs.data[k * rhs.cols + j];
            }
        }
    }
    return result;
}

template <typename U>
const DenseMat<U> operator*(const U& scalar, const DenseMat<U>& rhs) {
    DenseMat<U> result(rhs.rows, rhs.cols);
    for (int i = 0; i < rhs.rows * rhs.cols; i++) {
        result.data[i] = scalar * rhs.data[i];
    }
    return result;
}

template <typename U>
const DenseMat<U> operator*(const DenseMat<U>& lhs, const U& scalar) {
    return scalar * lhs;
}

template <typename U>
const DenseMat<U> operator+(const DenseMat<U>& lhs, const DenseMat<U>& rhs) {
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
        throw std::invalid_argument("Matrix dimensions do not match");

    DenseMat<U> result(lhs.rows, lhs.cols);
    for (int i = 0; i < lhs.rows * lhs.cols; i++) {
        result.data[i] = lhs.data[i] + rhs.data[i];
    }
    return result;
}

template <typename U>
const DenseMat<U> operator+(const U& scalar, const DenseMat<U>& rhs) {
    DenseMat<U> result(rhs.rows, rhs.cols);
    for (int i = 0; i < rhs.rows * rhs.cols; i++) {
        result.data[i] = scalar + rhs.data[i];
    }
    return result;
}

template <typename U>
const DenseMat<U> operator+(const DenseMat<U>& lhs, const U& scalar) {
    return scalar + lhs;
}

template <typename U>
const DenseMat<U> operator-(const DenseMat<U>& lhs, const DenseMat<U>& rhs) {
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
        throw std::invalid_argument("Matrix dimensions do not match");

    DenseMat<U> result(lhs.rows, lhs.cols);
    for (int i = 0; i < lhs.rows * lhs.cols; i++) {
        result.data[i] = lhs.data[i] - rhs.data[i];
    }
    return result;
}

template <typename U>
const DenseMat<U> operator-(const U& scalar, const DenseMat<U>& rhs) {
    DenseMat<U> result(rhs.rows, rhs.cols);
    for (int i = 0; i < rhs.rows * rhs.cols; i++) {
        result.data[i] = scalar - rhs.data[i];
    }
    return result;
}


} // namespace myDenseMat