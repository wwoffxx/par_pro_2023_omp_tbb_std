// Copyright 2023 Anoschenkova Anna
#ifndef MODULES_TASK_2_ANOSCHENKOVA_A_CANNON_CANNON_H_
#define MODULES_TASK_2_ANOSCHENKOVA_A_CANNON_CANNON_H_
#include <vector>
#include <iostream>
#include <cmath>
typedef std::vector<std::vector<double>> matrix;

matrix RandomMat(const int n);

matrix NaiveMult(const matrix &A, const matrix &B);
matrix BlockMult(const matrix &A, const matrix &B, const int &blockSize);

bool CompareMatrices(const matrix &A, const matrix &B);
bool IsNear(const double &a, const double &b);

#endif  // MODULES_TASK_2_ANOSCHENKOVA_A_CANNON_CANNON_H_
