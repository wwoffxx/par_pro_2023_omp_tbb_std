// Copyright 2023 Krainev Alexander
#ifndef MODULES_TASK_3_KRAINEV_A_SOBEL_OPERATOR_TBB_SOBEL_OPERATOR_TBB_H_
#define MODULES_TASK_3_KRAINEV_A_SOBEL_OPERATOR_TBB_SOBEL_OPERATOR_TBB_H_

#include <vector>
#include <random>

struct Pixel {
    Pixel(int r, int g, int b);

    unsigned char r;
    unsigned char g;
    unsigned char b;

    bool operator==(const Pixel& o) const;
};

using Image = std::vector<std::vector<Pixel>>;

Image white_image(int w, int h);

Image black_image(int w, int h);

Image random_image(int w, int h);

Image sobel(const Image& image);

Image sobel_tbb(const Image& image);

#endif  // MODULES_TASK_3_KRAINEV_A_SOBEL_OPERATOR_TBB_SOBEL_OPERATOR_TBB_H_
