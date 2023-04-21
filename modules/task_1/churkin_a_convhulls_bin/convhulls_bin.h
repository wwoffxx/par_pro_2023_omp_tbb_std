// Copyright 2023 Churkin Aleksandr
#ifndef MODULES_TASK_1_CHURKIN_A_CONVHULLS_BIN_CONVHULLS_BIN_H_
#define MODULES_TASK_1_CHURKIN_A_CONVHULLS_BIN_CONVHULLS_BIN_H_

#include <vector>
#include <map>
#include <utility>

std::vector<int> GetRandomBinImage(int M, int N);
void PrintImage(const std::vector<int>& image, int M, int N);

void BFS(std::vector<int>* image, int M, int N, int yStart, int xStart,
         int label);
void MarkComponents(std::vector<int>* image, int M, int N);

double rotate(std::pair<int, int> p1, std::pair<int, int> p2,
              std::pair<int, int> p3);
std::vector<std::pair<int, int>> GrahamScan(
    std::vector<std::pair<int, int>> points);
std::map<int, std::vector<std::pair<int, int>>> LeaveOnlyHulls(
    std::vector<int>* image, int M, int N);

#endif  // MODULES_TASK_1_CHURKIN_A_CONVHULLS_BIN_CONVHULLS_BIN_H_
