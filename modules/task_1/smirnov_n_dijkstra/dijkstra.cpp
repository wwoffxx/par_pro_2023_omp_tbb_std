// Copyright 2023 Smirnov Nick
#include <vector>

#include "../../../modules/task_1/smirnov_n_dijkstra/dijkstra.h"

std::vector<int> dijkstra(const int start,
                          const std::vector<std::vector<int>>& matrix) {
  int size = static_cast<int>(matrix.size());
  const int INF = 1000000;
  std::vector<int> dist(size, INF);

  dist[start] = 0;
  int curr_v = start;
  while (true) {
    std::vector<int> updated;
    int min = INF, pos = -1;
    for (int i = 0; i < size; i++) {
      if (i == curr_v) continue;
      if (dist[curr_v] + matrix[curr_v][i] < dist[i]) {
        updated.push_back(i);
        dist[i] = dist[curr_v] + matrix[curr_v][i];
      }
    }
    for (int v : updated) {
      if (dist[v] < min) {
        min = dist[v];
        pos = v;
      }
    }
    if (pos == -1) break;
    curr_v = pos;
  }
  return dist;
}


