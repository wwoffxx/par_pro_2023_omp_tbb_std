// Copyright 2023 Smirnov Nick
#ifndef MODULES_TASK_3_SMIRNOV_N_DIJKSTRA_DIJKSTRA_H_
#define MODULES_TASK_3_SMIRNOV_N_DIJKSTRA_DIJKSTRA_H_

#include <gtest/gtest.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/tbb.h>

#include <numeric>
#include <limits>
#include <random>
#include <vector>

using std::cout;
using std::vector;
using tbb::blocked_range;
using tbb::parallel_for;

const int INF = 2147483647;

class DijkstraFunctor {
 public:
    const vector<vector<int>>& graph;
    int start;
    vector<int>* distances;
    vector<bool>* visited;

    DijkstraFunctor(const vector<vector<int>>& _graph, vector<int>* _distances,
                    vector<bool>* _visited, int _start)
        : graph(_graph),
          distances(_distances),
          visited(_visited),
          start(_start) {}

    void operator()(const blocked_range<int>& range) const;
};

int genRandomInt(int min, int max);
vector<vector<int>> genRandomGraph(int N, int maxWeight, double edgeProb);
void printGraphAsMatrix(const vector<vector<int>>& graph);

void dijkstraSeq(const vector<vector<int>>& graph, vector<int>* distances, int start);

void dijkstraTBB(const vector<vector<int>>& graph, vector<int>* distances, int start);

#endif  // MODULES_TASK_3_SMIRNOV_N_DIJKSTRA_DIJKSTRA_H_
