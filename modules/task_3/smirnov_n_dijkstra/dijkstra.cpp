// Copyright 2023 Smirnov Nick
#include "../../../modules/task_3/smirnov_n_dijkstra/dijkstra.h"

int genRandomInt(int min, int max) {
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// Graph generating function
vector<vector<int>> genRandomGraph(int N, int maxWeight, double edgeProb) {
    std::mt19937 gen;
    std::uniform_int_distribution<int> weightDist(1, maxWeight);
    std::bernoulli_distribution edgeDist(edgeProb);

    vector<vector<int>> graph(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (edgeDist(gen)) {
                int weight = weightDist(gen);
                graph[i][j] = weight;
                graph[j][i] = weight;
            }
        }
    }

    return graph;
}

// Graph printing function
void printGraphAsMatrix(const vector<vector<int>>& graph) {
    for (const auto& row : graph) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << std::endl;
    }
}

// Seq version of Dijkstra alg
void dijkstraSeq(const vector<vector<int>>& graph, vector<int>* distances,
                 int start) {
    int N = graph.size();
    vector<bool> visited(N, false);
    (*distances)[start] = 0;

    // For every vertex of graph
    for (int i = 0; i < N; i++) {
        int minDistance = INF;
        int minIndex = -1;

        // Searching for not already visited vertex that have minimum distance
        // value
        for (int j = 0; j < N; j++) {
            if (!visited[j] && (*distances)[j] < minDistance) {
                minDistance = (*distances)[j];
                minIndex = j;
            }
        }

        // if found that vertex
        if (minIndex != -1) {
            // we mark that vertex visited
            visited[minIndex] = true;

            // and update our distances for that vertex
            for (int j = 0; j < N; j++) {
                if (!visited[j] && graph[minIndex][j] != 0) {
                    int newDistance = (*distances)[minIndex] + graph[minIndex][j];
                    if (newDistance < (*distances)[j]) {
                        (*distances)[j] = newDistance;
                    }
                }
            }
        }
    }
}

// TBB Version of Dijkstra alg
void DijkstraFunctor::operator()(const blocked_range<int>& range) const {
    int N = graph.size();

    for (int k = range.begin(); k != range.end(); k++) {
        if (k != 0) return;

        for (int i = 0; i < N; i++) {
            int minDistance = INF;
            int minIndex = -1;

            for (int j = 0; j < N; j++) {
                if (!(*visited)[j] && (*distances)[j] < minDistance) {
                    minDistance = (*distances)[j];
                    minIndex = j;
                }
            }

            if (minIndex != -1) {
                (*visited)[minIndex] = true;

                for (int j = 0; j < N; j++) {
                    if (!(*visited)[j] && graph[minIndex][j] != 0) {
                        int newDistance =
                            (*distances)[minIndex] + graph[minIndex][j];
                        if (newDistance < (*distances)[j]) {
                            (*distances)[j] = newDistance;
                        }
                    }
                }
            }
        }
    }
}

void dijkstraTBB(const vector<vector<int>>& graph, vector<int>* distances,
                 int start) {
    int N = graph.size();
    vector<bool> visited(N, false);
    (*distances)[start] = 0;

    parallel_for(blocked_range<int>(0, N),
                 DijkstraFunctor(graph, distances, &visited, start));
}
