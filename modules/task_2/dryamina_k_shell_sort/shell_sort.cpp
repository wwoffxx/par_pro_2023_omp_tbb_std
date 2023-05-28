// Copyright 2023 Dryamina Ksenia
#include <vector>
#include <random>
#include <iostream>
#include "../../modules/task_2/dryamina_k_shell_sort/shell_sort.h"

std::vector<int> genVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = gen() % 100;
    }
    return vec;
}

std::vector<int> sequentialShellSort(const std::vector<int>& vec) {
    int vecSize = static_cast<int>(vec.size());
    std::vector<int> result(vec);

    for (int s = vecSize / 2; s > 0; s /= 2) {
        for (int i = s; i < vecSize; ++i) {
            for (
                int j = i - s;
                j >= 0 && result[j] > result[j + s];
                j -= s
            ) {
                std::swap(result[j], result[j + s]);
            }
        }
    }

    return result;
}

std::vector<int> parallelShellSort(const std::vector<int>& vec) {
    int vecSize = static_cast<int>(vec.size());
    std::vector<int> result(vec);

    for (int s = vecSize / 2; s > 0; s /= 2) {
        #pragma omp parallel for shared(result, s, vecSize)
        for (int i = 0; i < s; ++i) {
            for (int j = s + i; j < vecSize; j += s) {
                int k = j;
                while (k > i && result[k - s] > result[k]) {
                    std::swap(result[k - s], result[k]);
                    k -= s;
                }
            }
        }
    }

    return result;
}
