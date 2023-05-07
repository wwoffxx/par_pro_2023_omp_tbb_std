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

    int current_vertex;
    int current_dist;
    //tbb::mutex mutex;
    std::vector<int> dist(size);
    std::priority_queue<std::pair<int, int>> queue;
    dist.at(source) = 0;

    queue.push(std::make_pair(0, 0));
    while (!queue.empty()) {
        current_vertex = queue.top().second;
        current_dist = (-1) * queue.top().first;
        queue.pop();
        if (current_dist > dist[current_vertex]) continue;

        tbb::parallel_for(
            tbb::blocked_range<int>(0, size),
            [&](const tbb::blocked_range<int>& range) {
            for (int i = range.begin(); i != range.end(); i++) {
                int dist_curr_v = graph.at(current_vertex * size + i);
                if (dist.at(current_vertex) + dist_curr_v < dist.at(i)) {
                    dist.at(i) = dist.at(current_vertex) + dist_curr_v;
                    std::pair<int, int> pair = std::make_pair((-1) * dist.at(i), i);
                    //mutex.lock();
                    queue.push(pair);
                    //mutex.unlock();
                }
            }
        });
    }

    return dist;
}
