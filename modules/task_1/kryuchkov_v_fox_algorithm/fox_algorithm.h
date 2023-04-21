// Copyright 2023 Kryuchkov Vladimir
#ifndef MODULES_TASK_1_KRYUCHKOV_V_FOX_ALGORITHM_FOX_ALGORITHM_H_
#define MODULES_TASK_1_KRYUCHKOV_V_FOX_ALGORITHM_FOX_ALGORITHM_H_

#include <vector>

std::vector<std::vector<double>> GetRandomMatrix(const int& size);
std::vector<std::vector<double>> SimpleMultiplication(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B);
std::vector<std::vector<double>> BlockMultiplication(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B);
bool CompareMatrix(const std::vector<std::vector<double>>& A,
                   const std::vector<std::vector<double>>& B);

#endif  // MODULES_TASK_1_KRYUCHKOV_V_FOX_ALGORITHM_FOX_ALGORITHM_H_
