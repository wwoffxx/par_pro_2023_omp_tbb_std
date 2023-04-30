// Copyright 2023 Smirnov Nick
#ifndef MODULES_TASK_2_SMIRNOV_N_DIJKSTRA_OMP_DIJKSTRA_OMP_H_
#define MODULES_TASK_2_SMIRNOV_N_DIJKSTRA_OMP_DIJKSTRA_OMP_H_

#include <gtest/gtest.h>
#include <omp.h>

#include <algorithm>
#include <random>
#include <string>
#include <utility>
#include <vector>

std::vector<std::vector<int>> getRandomVector(const int count);
std::vector<int> getDijkstra(const std::vector<std::vector<int>>& graf,
                             const int top);
std::vector<int> getSequentialDijkstra(
    const std::vector<std::vector<int>>& graf);
std::vector<int> getParallelDijkstra(const std::vector<std::vector<int>>& graf);

#endif  // MODULES_TASK_2_SMIRNOV_N_DIJKSTRA_OMP_DIJKSTRA_OMP_H_
