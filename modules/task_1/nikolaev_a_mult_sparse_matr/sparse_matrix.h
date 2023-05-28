// Copyright 2023 Nikolaev Alexander
#ifndef MODULES_TASK_1_NIKOLAEV_A_MULT_SPARSE_MATR_SPARSE_MATRIX_H_
#define MODULES_TASK_1_NIKOLAEV_A_MULT_SPARSE_MATR_SPARSE_MATRIX_H_

#include <vector>
#include <complex>
#include <iostream>

typedef std::complex<double> Complex;

struct CCSMatrix {
    int sizeMatrix;
    int countNZ;
    std::vector<Complex> value;
    std::vector<int> colIndex;
    std::vector<int> rowIndex;
};

void printMatrix(const std::vector<std::vector<Complex>>& Pmatrix);
CCSMatrix GetRandomMatrix(int N, int nonZero);
void TransposeMatrix(CCSMatrix* mtx);
CCSMatrix MatrixtoCCSMatrix(const std::vector<std::vector<Complex>> &matrix);
CCSMatrix Multiplicate(const CCSMatrix& A, const CCSMatrix& B);

#endif  // MODULES_TASK_1_NIKOLAEV_A_MULT_SPARSE_MATR_SPARSE_MATRIX_H_
