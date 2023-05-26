// Copyright 2023 Reshetnik Yana
#ifndef MODULES_TASK_1_RESHETNIK_Y_SOBEL_SOBEL_H_
#define MODULES_TASK_1_RESHETNIK_Y_SOBEL_SOBEL_H_

#include <ctime>
#include <iostream>
#include <random>
#include <vector>

std::vector<int> InitRandomMatrix(int height, int width);

int Clamp(int value, int min, int max);
int Index(int x, int y, int height);
std::vector<int> XSobelFilter(std::vector<int> source, int height, int width);

#endif  // MODULES_TASK_1_RESHETNIK_Y_SOBEL_SOBEL_H_
