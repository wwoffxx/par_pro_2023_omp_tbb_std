// Copyright 2023 Mikerin Ilya
#ifndef MODULES_TASK_3_MIKERIN_I_SHELL_SORT_TBB_SHELLSORT_H_
#define MODULES_TASK_3_MIKERIN_I_SHELL_SORT_TBB_SHELLSORT_H_

#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <tbb/tbb.h>
#include<tbb/parallel_invoke.h>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

std::vector<double> getRandomVector(int  sz);

void MergeSort(std::vector<double> &vec, std::size_t first, std::size_t second); //NOLINT

void ShellSort(std::vector<double> &vec);  //NOLINT

void MergeSortTBB(std::vector<double> &vec, std::size_t first, std::size_t second); //NOLINT

void ShellSortTBB(std::vector<double> &vec);  //NOLINT

#endif  // MODULES_TASK_3_MIKERIN_I_SHELL_SORT_TBB_SHELLSORT_H_
