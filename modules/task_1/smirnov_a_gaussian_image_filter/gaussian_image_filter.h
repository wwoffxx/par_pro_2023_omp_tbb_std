// Copyright 2023 Smirnov Andrew
#ifndef MODULES_TASK_1_SMIRNOV_A_GAUSSIAN_IMAGE_FILTER_GAUSSIAN_IMAGE_FILTER_H_
#define MODULES_TASK_1_SMIRNOV_A_GAUSSIAN_IMAGE_FILTER_GAUSSIAN_IMAGE_FILTER_H_
#include <vector>
#include <iostream>
#include <random>

using std::vector;
using intensityType = unsigned char;

const vector<intensityType> kernel{ 1, 2, 1, 2, 4, 2, 1, 2, 1 };
const intensityType kernelSum = 16;
const intensityType kernelSize = 3;

vector<intensityType> genImage(int rows, int columns);
vector<intensityType> gaussianFilterSeq(const vector<intensityType>& image, int rows, int columns);

#endif  // MODULES_TASK_1_SMIRNOV_A_GAUSSIAN_IMAGE_FILTER_GAUSSIAN_IMAGE_FILTER_H_
