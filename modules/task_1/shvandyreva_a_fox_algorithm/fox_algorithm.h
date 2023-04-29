// Copyright 2023 Shvandyreva Alina
#ifndef MODULES_TASK_1_SHVANDYREVA_A_FOX_ALGORITHM_FOX_ALGORITHM_H_
#define MODULES_TASK_1_SHVANDYREVA_A_FOX_ALGORITHM_FOX_ALGORITHM_H_

#include <vector>
#include <random>

using matrix = std::vector<std::vector<double>>;

matrix generate_matrix(size_t x_size, size_t y_size);

matrix generate_identity_matrix(size_t size);

matrix seq_multiply(const matrix& A, const matrix& B);

#endif  // MODULES_TASK_1_SHVANDYREVA_A_FOX_ALGORITHM_FOX_ALGORITHM_H_
