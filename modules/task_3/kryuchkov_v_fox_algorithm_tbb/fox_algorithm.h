// Copyright 2023 Kryuchkov Vladimir
#ifndef MODULES_TASK_3_KRYUCHKOV_V_FOX_ALGORITHM_TBB_FOX_ALGORITHM_H_
#define MODULES_TASK_3_KRYUCHKOV_V_FOX_ALGORITHM_TBB_FOX_ALGORITHM_H_

#include <math.h>

#include <vector>
using Matrix = std::vector<std::vector<double>>;

bool square(const Matrix& X);
bool isMultiply(const Matrix& X, const Matrix& Y);
Matrix OneMult(const Matrix& X, const Matrix& Y);
Matrix foxMultiply(const Matrix& X, const Matrix& Y);
Matrix randM(const int& num);

#endif  // MODULES_TASK_3_KRYUCHKOV_V_FOX_ALGORITHM_TBB_FOX_ALGORITHM_H_
