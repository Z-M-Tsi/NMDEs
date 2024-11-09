#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <string>

namespace myDenseMat{
template <typename T>
class DenseMat {
private:
    int rows, cols;
    int selectPivot(int r) const;
    std::vector<T> data;
    bool isSymmetric() const;

public:
    // Constructors and Destructor
    DenseMat(int rows, int cols);
    DenseMat(const DenseMat<T>& M);
    ~DenseMat();

    // Getters
    int get_rows() const;
    int get_cols() const;
    std::pair<int, int> size() const;
    void print() const; 
    DenseMat<T> subMatrix(int init_row, int final_row, int init_col, int final_col) const;

    const DenseMat<T>& operator=(const DenseMat<T>& M);

    // Inverse and Transpose
    DenseMat<T> inverse() const;
    DenseMat<T> transpose() const;
    T det() const;
    

    // Overloaded operators
    const T& operator()(int row, int col)const;
    T& operator()(int row, int col);

    template <typename U>
    friend const DenseMat<U> operator*(const DenseMat<U>& lhs, const DenseMat<U>& rhs);

    template <typename U>
    friend const DenseMat<U> operator*(const U& scalar, const DenseMat<U>& rhs);

    template <typename U>
    friend const DenseMat<U> operator*(const DenseMat<U>& lhs, const U& scalar);

    template <typename U>
    friend const DenseMat<U> operator+(const DenseMat<U>& lhs, const DenseMat<U>& rhs);

    template <typename U>
    friend const DenseMat<U> operator+(const U& scalar, const DenseMat<U>& rhs);

    template <typename U>
    friend const DenseMat<U> operator+(const DenseMat<U>& lhs, const U& scalar);

    template <typename U>
    friend const DenseMat<U> operator-(const DenseMat<U>& lhs, const DenseMat<U>& rhs);

    template <typename U>
    friend const DenseMat<U> operator-(const U& scalar, const DenseMat<U>& rhs);

    template <typename U>
    friend const DenseMat<U> operator-(const DenseMat<U>& lhs, const U& scalar);


    // Matrix Decomposition
    std::pair<DenseMat<T>, std::vector<std::pair<int, int>>> LU() const;

    DenseMat<T> Cholesky() const;
    std::pair<DenseMat<T>, DenseMat<T>> QR(const std::string &flag="") const;
};

// Special Matrices
template <typename T>
DenseMat<T> eyes(int n);

template <typename T>
DenseMat<T> zeros(int rows, int cols);

template <typename T>
DenseMat<T> ones(int rows, int cols);

template <typename T>
DenseMat<T> randomMatrix(int rows, int cols, T min=0, T max=1);


} // namespace myDenseMat   

#include "DenseMatClass.hpp"
#include "DenseMatGens.hpp"
#include "DenseMatSelf.hpp"
#include "DenseMatDecomp.hpp"
#include "DenseMatSolvers.hpp"