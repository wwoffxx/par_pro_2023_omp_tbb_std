// Copyright 2023 Melnik Denis
#ifndef MODULES_TASK_2_MELNIK_D_BLOCK_GAUSS_FILTER_BLOCK_GAUSS_FILTER_H_
#define MODULES_TASK_2_MELNIK_D_BLOCK_GAUSS_FILTER_BLOCK_GAUSS_FILTER_H_

#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::vector;

struct GaussBlock {
    int pixels[3][3];

    int GaussValue();

    void Print();
};

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

    void FillRandom();

    void Load(int *pixels);

    void Print() const;

    bool operator==(const Image &other) const;

    vector<GaussBlock> GetBlocks() const;
};

Image GaussFilter(const Image &origin);

Image GaussFilterBlockParallel(const Image &origin);

#endif  // MODULES_TASK_2_MELNIK_D_BLOCK_GAUSS_FILTER_BLOCK_GAUSS_FILTER_H_
