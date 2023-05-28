// Copyright 2023 Pankov Anatoliy
#ifndef MODULES_TASK_3_PANKOV_A_LGAUSSVERT_LGAUSSVERT_H_
#define MODULES_TASK_3_PANKOV_A_LGAUSSVERT_LGAUSSVERT_H_

#include <gtest/gtest.h>
#include <tbb/parallel_for.h>
#include <tbb/tick_count.h>

#include <ctime>
#include <random>
#include <vector>

int Clamp(int value, int min, int max);
std::vector<double> MakeRandomMatrix(int m, int n);
std::vector<double> SeqGaussFilter(const std::vector<double>& matrix, int m,
                                   int n);
std::vector<double> TBBGaussFilter(const std::vector<double>& matrix, int m,
                                   int n);

#endif  // MODULES_TASK_3_PANKOV_A_LGAUSSVERT_LGAUSSVERT_H_
