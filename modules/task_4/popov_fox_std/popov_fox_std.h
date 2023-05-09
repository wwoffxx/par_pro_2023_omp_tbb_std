// Copyright 2023 Popov Andrey
#ifndef MODULES_TASK_4_POPOV_FOX_STD_POPOV_FOX_STD_H_
#define MODULES_TASK_4_POPOV_FOX_STD_POPOV_FOX_STD_H_

#include <vector>
#include <string>

using Matrix = std::vector<std::vector<double>>;

inline bool isSquare(const Matrix& M) noexcept {
  return M.size() == M[0].size();
}

inline bool doublechecking(const double& x, const double& y) noexcept {
  return std::abs(x - y) <= 0.001 * std::abs(x + y);
}

Matrix getrandM(const int& num);
Matrix artlessmultiply(const Matrix& M1, const Matrix& M2);
Matrix modularmultiply(const Matrix& M1, const Matrix& M2);
bool matrixchecking(const Matrix& M1, const Matrix& M2);

Matrix algorhythm_fox_parallel(const Matrix& M1, const Matrix& M2);

#endif  // MODULES_TASK_4_POPOV_FOX_STD_POPOV_FOX_STD_H_
