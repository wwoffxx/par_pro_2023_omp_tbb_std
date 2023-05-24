// Copyright 2023 Gosteeva Ekaterina

#include "../../../modules/task_3/gosteeva_e_dijkstra_tbb/dijkstra.h"

std::vector<int> DijkstraSeq(std::vector<int> graph, int source, int size) {
    std::vector<int> dist(size);
    std::vector<bool> visited(size);
    int min = INT_MAX, index;
    for (int i = 0; i < size; i++) {
        dist.at(i) = INT_MAX;
        visited.at(i) = false;
    }
    dist.at(source) = 0;
    for (int i = 0; i < size; i++) {
        min = INT_MAX;
        for (int i = 0; i < size; i++) {
            if (visited.at(i) == false && dist.at(i) <= min) {
                min = dist.at(i);
                index = i;
            }
        }
        visited.at(index) = true;
        for (int i = 0; i < size; i++) {
            if (!visited.at(i) && graph.at(index * size + i) && dist.at(index) != INT_MAX
            && dist.at(index) + graph.at(index * size + i) < dist.at(i)) {
                dist.at(i) = dist.at(index) + graph.at(index * size + i);
            }
        }
    }
    return dist;
}

std::vector<int> DijkstraParallel(std::vector<int> graph,
    int source, int size) {

    std::vector dist(size, INT_MAX);
    std::vector visited(size, false);
    dist.at(source) = 0;
    int min = INT_MAX, index;

    tbb::parallel_for(tbb::blocked_range<int>(0, size),
        [&](const tbb::blocked_range<int>& r) {
        for (int i = r.begin(); i != r.end(); ++i) {
            int minDist = INT_MAX;
            int minIndex = 0;

            for (int j = 0; j < size; ++j) {
                if (!visited.at(j) && dist.at(j) <= minDist) {
                    minDist = dist.at(j);
                    minIndex = j;
                }
            }

            visited[minIndex] = true;

            for (int j = 0; j < size; ++j) {
                if (!visited.at(j) && graph.at(minIndex * size + j) &&
                    dist.at(minIndex) != INT_MAX &&
                    dist.at(minIndex) + graph.at(minIndex * size + j) <
                    dist.at(j)) {
                    dist.at(j) = dist.at(minIndex) + graph.at(minIndex * size + j);
                }
            }
        }
    });
    return dist;
}
