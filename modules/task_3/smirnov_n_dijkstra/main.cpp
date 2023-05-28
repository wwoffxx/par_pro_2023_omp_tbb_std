// Copyright 2023 Smirnov Nick
#include "./dijkstra.h"

void RunDijkstraTest(int N, int maxWeight, double edgeProb,
                     bool print = false) {
    vector<vector<int>> graph = genRandomGraph(N, maxWeight, edgeProb);
    int startVertex = genRandomInt(0, N - 1);

    if (print) {
        cout << "Graph generated:\n";
        printGraphAsMatrix(graph);
        cout << '\n';
        cout << "Start vertex: " << (startVertex + 1) << "\n\n";
    }

    vector<int> distancesSeq(N, INF);
    vector<int> distancesTBB(N, INF);

    dijkstraSeq(graph, &distancesSeq, startVertex);
    dijkstraTBB(graph, &distancesTBB, startVertex);

    if (print) {
        cout << "Seq: shortest distances from vertex " << startVertex << ":\n";
        for (int i = 0; i < N - 1; i++)
            cout << i + 1 << ": " << distancesSeq[i] << ", ";
        cout << (N - 1) + 1 << ": " << distancesSeq[N - 1] << "\n";
        cout << "TBB: shortest distances from vertex " << startVertex << ":\n";
        for (int i = 0; i < N - 1; i++)
            cout << i + 1 << ": " << distancesTBB[i] << ", ";
        cout << (N - 1) + 1 << ": " << distancesTBB[N - 1] << "\n";
    }

    ASSERT_EQ(distancesSeq, distancesTBB);
}

void go() {
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 0, 0, 2, 0, 3, 0}, {1, 0, 2, 0, 5, 0, 0, 5, 0, 3},
        {0, 2, 0, 3, 1, 1, 1, 4, 0, 0}, {0, 0, 3, 0, 1, 1, 0, 3, 5, 1},
        {0, 5, 1, 1, 0, 0, 2, 3, 0, 5}, {0, 0, 1, 1, 0, 0, 0, 0, 2, 0},
        {2, 0, 1, 0, 2, 0, 0, 0, 0, 0}, {0, 5, 4, 3, 3, 0, 0, 0, 4, 4},
        {3, 0, 0, 5, 0, 2, 0, 4, 0, 4}, {0, 3, 0, 1, 5, 0, 0, 4, 4, 0}};
    const int N = graph.size();
    int startVertex = 7;

    vector<int> distancesTBB(N, INF);

    dijkstraTBB(graph, &distancesTBB, startVertex);

    vector<int> rightResult = {6, 5, 4, 3, 3, 4, 5, 0, 4, 4};
    EXPECT_EQ(distancesTBB, rightResult);
}

TEST(DijkstraTBB, Test_1_5Vertices_Manual) {
    vector<vector<int>> graph = {{0, 2, 0, 1, 0},
                                 {2, 0, 5, 0, 0},
                                 {0, 5, 0, 2, 1},
                                 {1, 0, 2, 0, 0},
                                 {0, 0, 1, 0, 0}};
    const int N = graph.size();
    int startVertex = 0;

    vector<int> distancesTBB(N, INF);

    dijkstraTBB(graph, &distancesTBB, startVertex);

    vector<int> rightResult = {0, 2, 3, 1, 4};
    EXPECT_EQ(distancesTBB, rightResult);
}

TEST(DijkstraTBB, Test_2_10Vertices_Manual) {
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 0, 0, 2, 0, 3, 0}, {1, 0, 2, 0, 5, 0, 0, 5, 0, 3},
        {0, 2, 0, 3, 1, 1, 1, 4, 0, 0}, {0, 0, 3, 0, 1, 1, 0, 3, 5, 1},
        {0, 5, 1, 1, 0, 0, 2, 3, 0, 5}, {0, 0, 1, 1, 0, 0, 0, 0, 2, 0},
        {2, 0, 1, 0, 2, 0, 0, 0, 0, 0}, {0, 5, 4, 3, 3, 0, 0, 0, 4, 4},
        {3, 0, 0, 5, 0, 2, 0, 4, 0, 4}, {0, 3, 0, 1, 5, 0, 0, 4, 4, 0}};
    const int N = graph.size();
    int startVertex = 7;

    vector<int> distancesTBB(N, INF);

    dijkstraTBB(graph, &distancesTBB, startVertex);

    vector<int> rightResult = {6, 5, 4, 3, 3, 4, 5, 0, 4, 4};
    EXPECT_EQ(distancesTBB, rightResult);
}

TEST(DijkstraTBB, Test_3_20Vertices_Random) {
    int N = 20;
    int maxWeight = 5;
    double edgeProb = 0.4;
    RunDijkstraTest(N, maxWeight, edgeProb);
}

TEST(DijkstraTBB, Test_4_50Vertices_Random) {
    int N = 50;
    int maxWeight = 8;
    double edgeProb = 0.6;
    RunDijkstraTest(N, maxWeight, edgeProb);
}

TEST(DijkstraTBB, Test_5_100Vertices_Random) {
    int N = 100;
    int maxWeight = 5;
    double edgeProb = 0.7;
    RunDijkstraTest(N, maxWeight, edgeProb);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
