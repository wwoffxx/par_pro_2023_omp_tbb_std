// Copyright 2023 Labinskaya Marina
#ifndef MODULES_TASK_2_LABINSKAYA_M_RADIX_MERGE_SORT_OMP_RADIX_MERGE_SORT_OMP_H_
#define MODULES_TASK_2_LABINSKAYA_M_RADIX_MERGE_SORT_OMP_RADIX_MERGE_SORT_OMP_H_

#include <vector>

std::vector<double> merge(const std::vector<double>& v1,
    const std::vector<double>& v2);
std::vector<double> radixMergeSortSeq(const std::vector<double>& data);
bool bitwiseSortLast(double* in, double* out, int size);
void bitwiseSort(double* in, double* out, int size, int byteNum);
std::vector<double> getRandVec(int size, int a, int b);
std::vector<std::vector<double>> split(const std::vector<double>& data, int n);
std::vector<double> radixMergeSortOmp(const std::vector<double>& data, int n);

#endif  // MODULES_TASK_2_LABINSKAYA_M_RADIX_MERGE_SORT_OMP_RADIX_MERGE_SORT_OMP_H_
