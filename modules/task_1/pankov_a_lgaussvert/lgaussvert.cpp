// Copyright 2023 Pankov Anatoliy
#include "../../../modules/task_1/pankov_a_lgaussvert/lgaussvert.h"

int Clamp(int value, int max, int min) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}
std::vector<double> MakeRandomMatrix(int m, int n) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<double> result(m * n);
    for (int i = 0; i < m * n; i++)
        result[i] = gen() % 256;
    return result;
}
std::vector<double> SeqGaussFilter(const std::vector<double>& matrix,
    int m, int n) {
    if (m <= 0 || n <= 0 || matrix.size() == 0) {
        throw - 1;
    }
    const int size = 3;
    const double sigma = 1.0;
    const int radius = 1;
    double norm = 0;

    std::vector<double> result(m * n);
    std::vector<double> kernel(size * size);


    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius) * size + j + radius;
            kernel[idx] = exp(-(i * i + j * j) / (sigma * sigma));
            norm += kernel[idx];
        }
    }

    for (int i = 0; i < size * size; i++)
        kernel[i] /= norm;

    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            double res = 0;
            for (int i = -radius; i <= radius; i++) {
                for (int j = -radius; j <= radius; j++) {
                    int idx = (i + radius) * size + j + radius;

                    int x_ = Clamp(x + j, m - 1, 0);
                    int y_ = Clamp(y + i, n - 1, 0);

                    double value = matrix[x_ * n + y_];

                    res += value * kernel[idx];
                }
            }
            res = Clamp(res, 255, 0);
            result[x * n + y] = res;
        }
    }
    return result;
}
