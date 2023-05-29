// Copyright 2023 Kiselev Vladislav
#ifndef MODULES_TASK_3_KISELEV_VLADISLAV_VERT_GAUSSIAN_VERT_GAUSSIAN_H_
#define MODULES_TASK_3_KISELEV_VLADISLAV_VERT_GAUSSIAN_VERT_GAUSSIAN_H_
#define _USE_MATH_DEFINES

#include<tbb/tbb.h>
#include <vector>
#include<random>
#include<cmath>

std::vector<std::vector<double>> createGaussian();
std::vector<std::vector<int>> GaussianFilter_Seq(
    std::vector<std::vector<int>> sourceImg);
int newPixelColor(std::vector<std::vector<int>> sourceImg,
    int x, int y, std::vector<std::vector<double>> kernel);
std::vector<std::vector<int>> GaussianFilter_Tbb(
    std::vector<std::vector<int>> sourceImg);
int newPixelColor(std::vector<std::vector<int>> sourceImg,
    int x, int y, std::vector<std::vector<double>> kernel);
int checkValue(int value, int min, int max);
std::vector<std::vector<int>> getRandomImg(int width, int height);

template<class T>
bool imgEquivalent(std::vector<std::vector<T>> sourceImg,
    std::vector<std::vector<T>> resultImg) {
    int sourceW = sourceImg.size();
    int sourceH = sourceImg[0].size();
    int resultW = resultImg.size();
    int resultH = resultImg[0].size();

    if (sourceW != resultW || sourceH != resultH) return false;
    for (int i = 0; i < sourceW; i++) {
        for (int j = 0; j < sourceH; j++) {
            if (sourceImg[i][j] != resultImg[i][j])
                return false;
        }
    }
    return true;
}

#endif  // MODULES_TASK_3_KISELEV_VLADISLAV_VERT_GAUSSIAN_VERT_GAUSSIAN_H_

