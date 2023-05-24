// Copyright 2023 Gosteeva Ekaterina

#include "../../../modules/task_3/gosteeva_e_dijkstra_tbb/dijkstra.h"
#include <tbb>

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
    int cur_vertex;
    int cur_dist;
    tbb::mutex mutex;
    std::vector<int> dist(size, INT_MAX);
    std::priority_queue<std::pair<int, int>> queue;

    dist.at(source) = 0;
    queue.push(std::make_pair(0, source));
    while (!queue.empty()) {
        cur_vertex = queue.top().second;
        cur_dist = (-1) * queue.top().first;
        queue.pop();
        if (cur_dist > dist.at(cur_vertex)) continue;

        tbb::parallel_for(
            tbb::blocked_range<int>(0, size),
            [&](const tbb::blocked_range<int>& r) {
            for (int v = r.begin(); v != r.end(); ++v) {
                int dist_curV_V = graph.at(cur_vertex * size + v);
                if (dist.at(cur_vertex) + dist_curV_V < dist.at(v)) {
                dist.at(v) = dist.at(cur_vertex) + dist_curV_V;
                std::pair<int, int> pair = std::make_pair((-1) * dist[v], v);
                mutex.lock();
                queue.push(pair);
                mutex.unlock();
                }
            }
            });
    }

    return dist;
}
