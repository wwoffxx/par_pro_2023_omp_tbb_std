// Copyright 2023 Bushmakin Maksim
#ifndef MODULES_TASK_1_BUSHMAKIN_M_SHELLBATCHER_SHELLBATCHER_H_
#define MODULES_TASK_1_BUSHMAKIN_M_SHELLBATCHER_SHELLBATCHER_H_
#include <vector>

std::vector<int> getRandomIntVec(int length);
std::vector<int> getReversedVec(int length);
void printIntVec(std::vector<int> vec);

void shellsortSequential(int* vec, std::size_t n);

#endif  // MODULES_TASK_1_BUSHMAKIN_M_SHELLBATCHER_SHELLBATCHER_H_
