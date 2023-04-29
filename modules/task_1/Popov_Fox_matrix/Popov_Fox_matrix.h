// Copyright 2023 Popov Andrey
#include <vector>
#ifndef MODULES_TASK_1_POPOV_FOX_MATRIX_POPOV_FOX_MATRIX_H_
#define MODULES_TASK_1_POPOV_FOX_MATRIX_POPOV_FOX_MATRIX_H_
using matrix = std::vector<std::vector<double>>;

matrix simpleMult(const matrix& X, const matrix& Y);
matrix foxMult(const matrix& X, const matrix& Y, const int& sizeb);
matrix randMatrix(const int& cnt);
#endif  // MODULES_TASK_1_POPOV_FOX_MATRIX_POPOV_FOX_MATRIX_H_
