// Copyright 2023 Smirnov Nick
#include "./dijkstra.h"

TEST(Sequential_Dijkstra, Test_Get_Dijkstra_With_Static_Data_No_Throw) {
    const std::vector<std::vector<int>> graf = {
        {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
        {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};

    ASSERT_NO_THROW(getDijkstra(graf, 0));
}

TEST(Sequential_Dijkstra, Test_Sequential_Dijkstra_With_Static_Data_No_Throw) {
    const std::vector<std::vector<int>> graf = {
        {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
        {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};

    ASSERT_NO_THROW(getSequentialDijkstra(graf));
}

TEST(Parallel_Dijkstra, Test_Parallel_Dijkstra_With_Static_Data_No_Throw) {
    const std::vector<std::vector<int>> graf = {
        {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
        {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};

    ASSERT_NO_THROW(getParallelDijkstra(graf));
}

TEST(Sequential_Dijkstra, Test_Sequential_Dijkstra_With_Static_Data) {
    const std::vector<std::vector<int>> graf = {
        {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
        {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};
    const std::vector<int> trueResult = {
        0,  7,  9,  20, 20, 11, 7,  0,  10, 15, 21, 12, 9,  10, 0, 11, 11, 2,
        20, 15, 11, 0,  6,  13, 20, 21, 11, 6,  0,  9,  11, 12, 2, 13, 9,  0};
    bool check = true;
    const int count = graf.size();

    const std::vector<int> algorithmResult = getSequentialDijkstra(graf);
    for (int i = 0; i < count; ++i) {
        if (trueResult[i] != algorithmResult[i]) {
            check = false;
        }
    }

    ASSERT_EQ(check, true);
}

TEST(Sequential_Dijkstra, Test_Sequential_Dijkstra_Two_Times_Static) {
    const std::vector<std::vector<int>> graf = {
        {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
        {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};
    bool check = true;
    const int count = graf.size();

    const std::vector<int> algorithmResultFirst = getSequentialDijkstra(graf);

    const std::vector<int> algorithmResultSecond = getSequentialDijkstra(graf);

    for (int i = 0; i < count; ++i) {
        if (algorithmResultFirst[i] != algorithmResultSecond[i]) {
            check = false;
        }
    }

    ASSERT_EQ(check, true);
}

TEST(Sequential_Dijkstra, Test_Sequential_Dijkstra_Two_Times_Random) {
    const std::vector<std::vector<int>> graf = getRandomVector(10);
    bool check = true;
    const int count = graf.size();

    const std::vector<int> algorithmResultFirst = getSequentialDijkstra(graf);

    const std::vector<int> algorithmResultSecond = getSequentialDijkstra(graf);

    for (int i = 0; i < count; ++i) {
        if (algorithmResultFirst[i] != algorithmResultSecond[i]) {
            check = false;
        }
    }

    ASSERT_EQ(check, true);
}

TEST(Parallel_Dijkstra, Test_Parallel_Dijkstra_With_Seq_Static) {
    const std::vector<std::vector<int>> graf = {
        {0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0}, {9, 10, 0, 11, 0, 2},
        {0, 15, 11, 0, 6, 0}, {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};
    bool check = true;
    const int count = graf.size();

    const std::vector<int> algorithmResultSeq = getSequentialDijkstra(graf);

    const std::vector<int> algorithmResultRarallel = getParallelDijkstra(graf);

    for (int i = 0; i < count; ++i) {
        if (algorithmResultSeq[i] != algorithmResultRarallel[i]) {
            check = false;
        }
    }

    ASSERT_EQ(check, true);
}

TEST(Parallel_Dijkstra, Test_Parallel_Dijkstra_With_Seq_Random) {
    const std::vector<std::vector<int>> graf = getRandomVector(50);
    bool check = true;
    const int count = graf.size();
    const std::vector<int> algorithmResultSeq = getSequentialDijkstra(graf);
    const std::vector<int> algorithmResultRarallel = getParallelDijkstra(graf);

    for (int i = 0; i < count; ++i) {
        if (algorithmResultSeq[i] != algorithmResultRarallel[i]) {
            check = false;
        }
    }

    ASSERT_EQ(check, true);
}
