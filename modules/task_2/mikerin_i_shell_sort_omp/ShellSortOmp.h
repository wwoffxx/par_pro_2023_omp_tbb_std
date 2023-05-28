// Copyright 2023 Mikerin Ilya
#ifndef MODULES_TASK_2_MIKERIN_I_SHELL_SORT_OMP_SHELLSORTOMP_H_
#define MODULES_TASK_2_MIKERIN_I_SHELL_SORT_OMP_SHELLSORTOMP_H_

#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <omp.h> //NOLINT

std::vector<double> getRandomVector(int  sz);

void MergeSort(std::vector<double> &vec, std::size_t first, std::size_t second); //NOLINT

void MergeSortOmp(std::vector<double> &vec, std::size_t first, std::size_t second); //NOLINT

void ShellSort(std::vector<double> &vec);  //NOLINT

void ShellSortOmp(std::vector<double> &vec);  //NOLINT

#endif  // MODULES_TASK_2_MIKERIN_I_SHELL_SORT_OMP_SHELLSORTOMP_H_
