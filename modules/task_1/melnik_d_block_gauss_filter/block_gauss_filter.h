// Copyright 2023 Melnik Denis
#ifndef MODULES_TASK_1_MELNIK_D_BLOCK_GAUSS_FILTER_BLOCK_GAUSS_FILTER_H_
#define MODULES_TASK_1_MELNIK_D_BLOCK_GAUSS_FILTER_BLOCK_GAUSS_FILTER_H_

#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::vector;

class Image {
 private:
    vector<int> pixels;
    int width;
    int height;

 public:
    Image(int w, int h);

    int W() const { return width; }
    int H() const { return height; }

    int GetPixel(int x, int y) const;
    void SetPixel(int x, int y, int value);

    void Load(int *pixels);

    void Print() const;

    bool operator==(const Image &other) const;
};

Image GaussFilter(const Image &origin);

#endif  // MODULES_TASK_1_MELNIK_D_BLOCK_GAUSS_FILTER_BLOCK_GAUSS_FILTER_H_
