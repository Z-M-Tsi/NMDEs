/*
    * Matrix.h
    * This is the header file for the Matrix class for dense matrices.
    * The class is templated to allow for different data types.
    * The class is designed to be used in numerical linear algebra.
    * The class supports basic matrix operations, 
    * such as addition, subtraction, multiplication, transpose, submatrix, etc.
    * The class also supports frequently used matrix generations,
    * such as identity matrix, zero matrix, one matrix, and random integer matrix.
*/


#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <random>

namespace mymatrix{
template <typename T>
class Matrix {
private:
    int rows, cols;
    T* data;

    int findpivot(int r) const;

public:
    // Constructors and Destructor
    Matrix(int rows, int cols);
    Matrix(const Matrix<T>& M);
    ~Matrix();
    
    // Getters
    int get_rows() const;
    int get_cols() const;
    std::pair<int, int> size() const;
    Matrix<T> subMatrix(int init_row, int final_row, int init_col, int final_col) const;
    void print() const;

    // Overloaded operators 
    T& operator()(int i, int j);
    const T& operator()(int i, int j) const;
    Matrix<T>& operator=(const Matrix<T>& M);
    Matrix<T> operator+(const Matrix<T>& M) const;
    Matrix<T> operator-(const Matrix<T>& M) const;
    Matrix<T> operator*(const Matrix<T>& M) const;
    
    template <typename U>
    friend Matrix<U> operator*(const U& scalar, const Matrix<U>& M);
    template <typename U>
    friend Matrix<U> operator*(const Matrix<U>& M, const U& scalar);
    
    // Frequently used matrix self operations
    Matrix<T> transpose() const;
    // double det() const;
    Matrix<T> inverse() const;

    // Frequently used generations
    static Matrix<T> eyes(int n);
    static Matrix<T> zeros(int rows, int cols);
    static Matrix<T> ones(int rows, int cols);
    static Matrix<T> randi(int rows, int cols, int min, int max);
    
};
} // namespace mymatrix

#include "MatixBasic.hpp"
#include "MatrixOperater.hpp"
#include "MatrixSelf.hpp"
#include "MatrixGen.hpp"

#endif // MATRIX_H