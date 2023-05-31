// Copyright 2023 Zanozin Danila
#ifndef MODULES_TASK_1_ZANOZIN_D_MULTIPLICATION_OF_DENSE_MATRICES_MULTIPLICATION_OF_DENSE_MATRICES_H_
#define MODULES_TASK_1_ZANOZIN_D_MULTIPLICATION_OF_DENSE_MATRICES_MULTIPLICATION_OF_DENSE_MATRICES_H_

#include <cmath>
#include <iostream>
#include <vector>
typedef std::vector<std::vector<double>> matrix;

matrix RandomMat(const int n);

matrix NaiveMult(const matrix &A, const matrix &B);
matrix BlockMult(const matrix &A, const matrix &B, const int &blockSize);

bool CompareMatrices(const matrix &A, const matrix &B);
bool IsNear(const double &a, const double &b);
#endif  // MODULES_TASK_1_ZANOZIN_D_MULTIPLICATION_OF_DENSE_MATRICES_MULTIPLICATION_OF_DENSE_MATRICES_H_
