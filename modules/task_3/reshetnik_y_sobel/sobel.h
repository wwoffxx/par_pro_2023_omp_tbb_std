// Copyright 2023 Reshetnik Yana
#ifndef MODULES_TASK_3_RESHETNIK_Y_SOBEL_SOBEL_H_
#define MODULES_TASK_3_RESHETNIK_Y_SOBEL_SOBEL_H_

#include <gtest/gtest.h>
#include <tbb/blocked_range.h>
#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>
#include <tbb/tick_count.h>

#include <algorithm>
#include <exception>
#include <iostream>
#include <random>
#include <vector>

template <class T>
T Clamp(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

std::vector<int> CreateRandomImage(int width, int height);
int GetIndex(int x, int y, int height);
int CalculatePixelValue(const std::vector<int>& source, int width, int x,
                        int y);
std::vector<int> SequentialSobelFilter(const std::vector<int>& source,
                                       int width, int height);
std::vector<int> ParallelSobelFilter(const std::vector<int>& source, int width,
                                     int height);

#endif  // MODULES_TASK_3_RESHETNIK_Y_SOBEL_SOBEL_H_
