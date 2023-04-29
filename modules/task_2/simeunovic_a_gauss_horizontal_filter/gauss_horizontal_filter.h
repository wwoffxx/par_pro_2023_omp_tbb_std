// Copyright 2023 Simeunovic Aleksandar
#ifndef MODULES_TASK_2_SIMEUNOVIC_A_GAUSS_HORIZONTAL_FILTER_H_
#define MODULES_TASK_2_SIMEUNOVIC_A_GAUSS_HORIZONTAL_FILTER_H_
#include <cstdint>
#include <cmath>
#include <ctime>
#include <vector>
#include <random>
#include <cinttypes>

int GetIndex(int i, int j, int offset);
std::vector<uint8_t> GetRandMatrix(int offset, int pixelHeight);
std::vector<uint8_t> Filter(std::vector<uint8_t> srcVec, int offset,
    int pixelHeight, double sigma = 1.0);
std::vector<uint8_t> ParFilter(std::vector<uint8_t> srcVec, int offset,
    int pixelHeight, int threads = 2, double sigma = 1.0);

#endif  // _MODULES_TASK_2_SIMEUNOVIC_A_GAUSS_HORIZONTAL_FILTER_H_
