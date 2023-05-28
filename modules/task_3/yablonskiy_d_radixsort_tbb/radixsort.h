// Copyright 2023 Yablonskiy Dmitriy

#ifndef MODULES_TASK_3_YABLONSKIY_D_RADIXSORT_TBB_RADIXSORT_H_
#define MODULES_TASK_3_YABLONSKIY_D_RADIXSORT_TBB_RADIXSORT_H_

#include <tbb/tbb.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

int max_elem(std::vector<int>* arr);

void radix_sort_e(std::vector<int>* arr, int exp);

void radix_sort(std::vector<int>* arr);

std::vector<int> radix_m(const std::vector<int>& arr_1, const std::vector<int>& arr_2);

std::vector<int> radix_sort_mer(std::vector<int>* arr);

std::vector<int> create_rand_arr(int size);

#endif  // MODULES_TASK_3_YABLONSKIY_D_RADIXSORT_TBB_RADIXSORT_H_
