// Copyright 2023 Reshetnik Yana
#include "../../../modules/task_3/reshetnik_y_sobel/sobel.h"

const int FilterKernel[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

std::vector<int> CreateRandomImage(int width, int height) {
    if (height <= 0 || width <= 0)
        throw std::runtime_error("Image should have positive width and height");
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> result(height * width);
    for (int i = 0; i < height * width; ++i) result[i] = gen() % 256;
    return result;
}

int GetIndex(int x, int y, int width) {
    return x + y * width;
}

int CalculatePixelValue(const std::vector<int>& source, int width, int x,
                        int y) {
    int height = source.size() / width;
    int pixel = 0;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j) {
            int index = GetIndex(Clamp(x + j, 0, width - 1),
                              Clamp(y + i, 0, height - 1), width);
            pixel += FilterKernel[3 * (i + 1) + (j + 1)] * source[index];
        }
    return Clamp(pixel, 0, 255);
}

std::vector<int> SequentialSobelFilter(const std::vector<int>& source,
                                       int width, int height) {
    std::vector<int> ResultImage(width * height);

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            ResultImage[GetIndex(x, y, width)] =
                CalculatePixelValue(source, width, x, y);

    return ResultImage;
}

std::vector<int> ParallelSobelFilter(const std::vector<int>& source, int width,
                                     int height) {
    std::vector<int> ResultImage(source.size());

    auto functor = [&](const tbb::blocked_range<size_t>& range) {
        for (size_t i = range.begin(); i != range.end(); ++i) {
            int y = (i) / width;
            int x = (i) % width;
            ResultImage[i] = CalculatePixelValue(source, width, x, y);
        }
    };

    tbb::parallel_for(tbb::blocked_range<size_t>(0, source.size()), functor);
    return ResultImage;
}
