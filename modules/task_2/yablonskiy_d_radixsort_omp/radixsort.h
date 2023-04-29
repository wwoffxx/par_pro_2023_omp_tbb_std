// Copyright 2023 Yablonskiy Dmitriy

#ifndef MODULES_TASK_2_YABLONSKIY_D_RADIXSORT_OMP_RADIXSORT_H_
#define MODULES_TASK_2_YABLONSKIY_D_RADIXSORT_OMP_RADIXSORT_H_

#include <omp.h>
#include <algorithm>
#include <vector>
#include <random>


int max_elem(std::vector<int> *arr);
void radixSort_e(std::vector<int> *arr, int exp);
void radixSort(std::vector<int> *arr);
std::vector<int> merge(std::vector<int> *arr_1, std::vector<int> *arr_2);
std::vector<int> radixSort_mer(std::vector<int> *arr);
std::vector<int> create_rand_arr(int size);

#endif  // MODULES_TASK_2_YABLONSKIY_D_RADIXSORT_OMP_RADIXSORT_H_
