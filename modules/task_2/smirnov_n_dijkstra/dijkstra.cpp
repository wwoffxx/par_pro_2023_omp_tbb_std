// Copyright 2023 Smirnov Nick
#include "../../../modules/task_2/smirnov_n_dijkstra/dijkstra.h"

std::vector<std::vector<int>> getRandomVector(const int count) {
    std::vector<std::vector<int>> graf(count, std::vector<int>(count));
    std::mt19937 gen(0);
    for (int i = 0; i < count; ++i) {
        graf[i][i] = 0;
        for (int j = i + 1; j < count; ++j) {
            graf[i][j] = gen() % 100;
            graf[j][i] = graf[i][j];
        }
    }
    return graf;
}

std::vector<int> getDijkstra(const std::vector<std::vector<int>>& graf,
                             const int top) {
    const int count = graf.size();
    std::vector<bool> visitedTops(count);
    std::vector<int> dist(count, 10000);
    dist[top] = 0;
    int min_dist = 0;
    int min_vertex = top;

    while (min_dist < 10000) {
        int i = min_vertex;
        visitedTops[i] = true;
        for (int j = 0; j < count; ++j)
            if ((dist[i] + graf[i][j] < dist[j]) && (graf[i][j] != 0))
                dist[j] = dist[i] + graf[i][j];
        min_dist = 10000;
        for (int j = 0; j < count; ++j)
            if (!visitedTops[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                min_vertex = j;
            }
    }

    return dist;
}

std::vector<int> getParallelDijkstra(
    const std::vector<std::vector<int>>& graf) {
    int top = 0;
    const int count = graf.size();
    std::vector<int> result(count * count, 0);
    int numThreads = 12;

#pragma omp parallel for shared(count, result, graf) private(top) \
    schedule(static) num_threads(numThreads)
    for (top = 0; top < count; ++top) {
        auto tmp = getDijkstra(graf, top);
        for (int i = 0; i < count; ++i) {
            result[top * count + i] = tmp[i];
        }
    }
    return result;
}

std::vector<int> getSequentialDijkstra(
    const std::vector<std::vector<int>>& graf) {
    int top = 0;
    const int count = graf.size();
    std::vector<int> result(count * count, 0);
    for (top = 0; top < count; ++top) {
        auto tmp = getDijkstra(graf, top);
        for (int i = 0; i < count; ++i) {
            result[top * count + i] = tmp[i];
        }
    }
    return result;
}
