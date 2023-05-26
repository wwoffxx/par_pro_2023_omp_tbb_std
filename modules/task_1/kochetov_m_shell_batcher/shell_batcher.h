// Copyright 2023 Kochetov Maksim
#ifndef MODULES_TASK_1_KOCHETOV_M_SHELL_BATCHER_SHELL_BATCHER_H_
#define MODULES_TASK_1_KOCHETOV_M_SHELL_BATCHER_SHELL_BATCHER_H_
#include <vector>

void PrintVec(std::vector<int> vec);

std::vector<int> GetRandomVec(int length);
std::vector<int> GetSortedVec(int size);
std::vector<int> GetReversedVec(int length);

void ShellsortSeq(int* array, int n);

#endif  // MODULES_TASK_1_KOCHETOV_M_SHELL_BATCHER_SHELL_BATCHER_H_
