// Copyright 2023 Labinskaya Marina
#ifndef MODULES_TASK_1_LABINSKAYA_M_RADIX_MERGE_SORT_RADIX_MERGE_SORT_H_
#define MODULES_TASK_1_LABINSKAYA_M_RADIX_MERGE_SORT_RADIX_MERGE_SORT_H_

#include <vector>

std::vector<double> merge(const std::vector<double>& v1,
    const std::vector<double>& v2);
std::vector<double> radixMergeSort(const std::vector<double>& data);
bool bitwiseSortLast(double* in, double* out, int size);
void bitwiseSort(double* in, double* out, int size, int byteNum);
std::vector<double> getRandVec(int size, int a, int b);

#endif  // MODULES_TASK_1_LABINSKAYA_M_RADIX_MERGE_SORT_RADIX_MERGE_SORT_H_
