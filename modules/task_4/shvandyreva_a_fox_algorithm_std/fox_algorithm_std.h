// Copyright 2023 Shvandyreva Alina
#ifndef MODULES_TASK_4_SHVANDYREVA_A_FOX_ALGORITHM_STD_FOX_ALGORITHM_STD_H_
#define MODULES_TASK_4_SHVANDYREVA_A_FOX_ALGORITHM_STD_FOX_ALGORITHM_STD_H_

#include <vector>
#include <random>

using matrix = std::vector<std::vector<double>>;

matrix generate_matrix(size_t x_size, size_t y_size);

matrix generate_identity_matrix(size_t size);

matrix seq_multiply(const matrix& A, const matrix& B);

matrix std_multiply(const matrix& A, const matrix& B, int tasks_by_dim);

#endif  // MODULES_TASK_4_SHVANDYREVA_A_FOX_ALGORITHM_STD_FOX_ALGORITHM_STD_H_
