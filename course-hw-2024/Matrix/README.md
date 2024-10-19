## Introduction

Welcome to the Matrix project for the MATH6207H Scientific Computing course at Shanghai Jiao Tong University (SJTU). 
This repository contains a C++ library named Matrix.
Its goal is to provide a simple, efficient, and flexible toolkit for performing linear algebra operations. 
This library offers fundamental matrix manipulation utilities and numerical methods essential for scientific computing.


## Table of Contents

- [Introduction](#introduction)
- [Table of Contents](#table-of-contents)
- [Features](#features)
- [Structure](#structure)
- [Requirements](#requirements)
- [Installation](#installation)
- [Quickstart](#quickstart)
- [Contributing](#contributing)
- [License](#license)


## Features
* Matrix Operations: Addition, subtraction, multiplication, and transposition.
* Vector Support: Support for vectors and matrix-vector operations.
* Determinants and Inverses: Efficient algorithms to compute determinants and matrix inverses.
* Decompositions: LU decomposition and other factorizations (Only modified Cholesky and QR now).


## Structure
* `include/`: Header files defining the Matrix class, vector utilities, and key functions. 
* `tests/`: Unit tests to validate correctness of the operations.


## Requirements
* C++11 or later for modern syntax and memory management.
* CMake for building the project.


## Installation

To get started, clone the repository and install the necessary dependencies:

```bash
git clone https://github.com/Z-M-Tsi/Matrix.git
cd Matrix
```

## Quickstart

Here is a simple example of how to use the Matrix:

```cpp
#include"Matrix.h"

# Create matrices
A = mymatric::Matrix(2, 2);
B = Matrix([[5, 6], [7, 8]])

# Perform operations
C = A + B
D = A * B
E = A.inverse()

print("Sum:\n", C)
print("Product:\n", D)
print("Inverse of A:\n", E)
```

## Contributing

Contributions are welcome! Please read the [contributing guidelines](CONTRIBUTING.md) before submitting a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.