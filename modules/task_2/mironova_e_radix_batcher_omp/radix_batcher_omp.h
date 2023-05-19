// Copyright 2023 Mironova Ekaterina
#ifndef MODULES_TASK_2_MIRONOVA_E_RADIX_BATCHER_OMP_RADIX_BATCHER_OMP_H_
#define MODULES_TASK_2_MIRONOVA_E_RADIX_BATCHER_OMP_RADIX_BATCHER_OMP_H_

#include <vector>

void compexch(double* x, double* y);
std::vector<double> batcherMerge(const std::vector<double>& firstPart, const std::vector<double>& secondPart);
std::vector<double> radixSort(std::vector<double> data, int exp);
std::vector<double> fullRadixSort(std::vector<double> unsortedData);
std::vector<double> radixSortBatcherMergeOmp(const std::vector<double>& data);

#endif  // MODULES_TASK_2_MIRONOVA_E_RADIX_BATCHER_OMP_RADIX_BATCHER_OMP_H_