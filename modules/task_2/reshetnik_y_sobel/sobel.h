// Copyright 2023 Reshetnik Yana

#ifndef MODULES_TASK_2_RESHETNIK_Y_SOBEL_SOBEL_H_
#define MODULES_TASK_2_RESHETNIK_Y_SOBEL_SOBEL_H_

#include <gtest/gtest.h>
#include <omp.h>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

class Image {
   public:
    int width = 0, height = 0;
    std::vector<int> matrix;
    explicit Image(const std::vector<int>& mat);
    Image(int _width, int _height);
    bool EqualTo(const Image& img2);
};

Image getRandomImage(int _width, int _height);
Image SobelSeq(Image Start);
Image SobelOMP(Image Start);

#endif  //  MODULES_TASK_2_RESHETNIK_Y_SOBEL_SOBEL_H_
