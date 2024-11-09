#pragma once

#include "../include/DenseMat/DenseMat.h"

namespace myDenseMat{

template <typename T>
DenseMat<T> eyes(int n)
{
    DenseMat<T> M(n, n);
    for (int i = 0; i < n; i++)
    {
        M(i, i) = 1;
    }
    return M;
}

template <typename T>
DenseMat<T> zeros(int rows, int cols)
{
    DenseMat<T> M(rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        M(i / cols, i % cols) = 0;
    }
    return M;
}

template <typename T>
DenseMat<T> ones(int rows, int cols)
{
    DenseMat<T> M(rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        M(i / cols, i % cols) = 1;
    }
    return M;
}

template <typename T>
DenseMat<T> randomMatrix(int rows, int cols, T min, T max)
{
    DenseMat<T> M(rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        M(i / cols, i % cols) = min + (max - min) * rand() / static_cast<T>(RAND_MAX);
    }
    return M;
}


} // namespace myDenseMat