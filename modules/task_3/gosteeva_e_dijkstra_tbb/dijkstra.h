// Copyright 2023 Gosteeva Ekaterina
#ifndef MODULES_TASK_3_GOSTEEVA_E_DIJKSTRA_TBB_DIJKSTRA_H_
#define MODULES_TASK_3_GOSTEEVA_E_DIJKSTRA_TBB_DIJKSTRA_H_

#include <tbb/tbb.h>
#include <queue>
#include <climits>
#include <vector>

std::vector<int> DijkstraSeq(std::vector<int> graph,
    int source, int size);
std::vector<int> DijkstraParallel(std::vector<int> graph,
    int source, int size);
#endif  // MODULES_TASK_3_GOSTEEVA_E_DIJKSTRA_TBB_DIJKSTRA_H_
