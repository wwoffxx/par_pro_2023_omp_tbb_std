// Copyright 2023 Reshetnik Yana
#include "../../../modules/task_1/reshetnik_y_sobel/sobel.h"

std::vector<int> InitRandomMatrix(int height, int width) {
    if (height <= 0 || width <= 0) throw "Sizes are incorrect!";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);

    std::vector<int> result(height * width);
    for (int i = 0; i < height * width; i++) {
        result[i] = dis(gen);
    }

    return result;
}

int Clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

int Index(int x, int y, int width) {
    return y * width + x;
}

std::vector<int> XSobelFilter(std::vector<int> source, int height, int width) {
    std::vector<int> result(height * width);
    int Kernel[9] = {-1, 0, 1,
                     -2, 0, 2,
                     -1, 0, 1};
    int Radius = 1, Size = 3;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel = 0;
            for (int i = -Radius; i <= Radius; i++) {
                for (int j = -Radius; j <= Radius; j++) {
                    int idx = (i + Radius) * Size + (j + Radius);
                    int index = Index(Clamp(x + j, 0, width - 1),
                                      Clamp(y + i, 0, height - 1), width);
                    pixel += Kernel[idx] * source[index];
                }
            }

            result[Index(x, y, width)] = Clamp(pixel, 0, 255);
        }
    }

    return result;
}
