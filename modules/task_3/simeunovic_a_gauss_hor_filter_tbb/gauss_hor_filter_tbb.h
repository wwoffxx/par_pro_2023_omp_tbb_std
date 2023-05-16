// Copyright 2023 Simeunovic Aleksandar
#ifndef MODULES_TASK_3_SIMEUNOVIC_A_GAUSS_HOR_FILTER_TBB_GAUSS_HOR_FILTER_TBB_H_
#define MODULES_TASK_3_SIMEUNOVIC_A_GAUSS_HOR_FILTER_TBB_GAUSS_HOR_FILTER_TBB_H_

#include <tbb/tbb.h>

#include <cmath>
#include <vector>

using img = std::vector<std::vector<int>>;

struct Kernel {
  int size = 3;
  int len = 9;

  float* data = new float[len];
  float sigma = 3.f;
  float norm = 0;
  int signed_radius = static_cast<int>(1);

  Kernel() {
    for (int x = -signed_radius; x <= signed_radius; x++)
      for (int y = -signed_radius; y <= signed_radius; y++) {
        std::size_t idx = (x + 1) * size + (y + 1);
        data[idx] = std::exp(-(x * x + y * y) / (sigma * sigma));
        norm += data[idx];
      }
    for (int i = 0; i < len; i++) {
      data[i] /= norm;
    }
  }
};

const Kernel kernel;

img getRandomImage(int width, int height);
img getGauss(const img& image, int width, int height);
img getGaussTBB(const img& image, int width, int height);

#endif  // MODULES_TASK_3_SIMEUNOVIC_A_GAUSS_HOR_FILTER_TBB_GAUSS_HOR_FILTER_TBB_H_
