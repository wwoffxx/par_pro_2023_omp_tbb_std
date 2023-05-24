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
    dist[source] = 0;
    int min = INT_MAX, index;
    tbb::queuing_mutex mutex;
    for (int i = 0; i < size; i++) {
        min = INT_MAX;
        tbb::parallel_for(0, size, [&](int j) {
            tbb::queuing_mutex::scoped_lock lock(mutex);
            if (visited.at(j) == false && dist.at(j) <= min) {
            min = dist.at(j);
            index = j;
            }
        });
        visited.at(index) = true;
        tbb::parallel_for(0, size, [&](int j) {
        tbb::queuing_mutex::scoped_lock lock(mutex);
        if (!visited.at(j) && graph.at(index * size + j) && dist.at(index) != INT_MAX
        && dist.at(index) + graph.at(index * size + j) < dist.at(j)) {
        dist.at(j) = dist.at(index) + graph.at(index * size + j);
        }
        });
    }
    return dist;
}
