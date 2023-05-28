// Copyright 2023 Troegubova Alexandra
#ifndef MODULES_TASK_3_TROEGUBOVA_A_STRASSEN_TBB_STRASSEN_TBB_H_
#define MODULES_TASK_3_TROEGUBOVA_A_STRASSEN_TBB_STRASSEN_TBB_H_

#include <vector>

std::vector<double> getRandomMatrix(int n);
std::vector<double> multiplyNaive(const std::vector<double>& A, const std::vector<double>& B);
std::vector<double> sumMatrix(const std::vector<double>& A, const std::vector<double>& B);
std::vector<double> diffMatrix(const std::vector<double>& A, const std::vector<double>& B);
std::vector<std::vector<double>> getBlockMatrix(const std::vector<double>& A);
std::vector<double> multiplyStrassenTbb(const std::vector<double>& A, const std::vector<double>& B, bool parallel);

#endif  // MODULES_TASK_3_TROEGUBOVA_A_STRASSEN_TBB_STRASSEN_TBB_H_
