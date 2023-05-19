// Copyright 2023 Mironova Ekaterina
#ifndef MODULES_TASK_3_MIRONOVA_E_RADIX_BATCHER_TBB_RADIX_BATCHER_TBB_H_
#define MODULES_TASK_3_MIRONOVA_E_RADIX_BATCHER_TBB_RADIX_BATCHER_TBB_H_

#include <vector>

void compexch(double* x, double* y);
std::vector<double> batcherMerge(const std::vector<double>& firstPart, const std::vector<double>& secondPart);
std::vector<double> radixSort(std::vector<double> data, int exp);
std::vector<double> fullRadixSort(std::vector<double> unsortedData);
std::vector<double> radixSortBatcherMergeTbb(const std::vector<double>& data);

#endif  // MODULES_TASK_3_MIRONOVA_E_RADIX_BATCHER_TBB_RADIX_BATCHER_TBB_H_
