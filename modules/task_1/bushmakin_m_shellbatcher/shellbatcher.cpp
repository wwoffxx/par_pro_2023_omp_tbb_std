// Copyright 2023 Bushmakin Maksim
#include <omp.h>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include "../../../modules/task_1/bushmakin_m_shellbatcher/shellbatcher.h"

std::vector<int> getRandomIntVec(int length) {
    std::random_device randomDevice;
    std::mt19937 engine(randomDevice());
    std::uniform_int_distribution<> distrib(1, 100);
    std::vector<int> vec(length);

    for (int i = 0; i < length; i++)
        vec[i] = distrib(engine);

    return vec;
}

std::vector<int> getReversedVec(int length) {
    std::vector<int> vec(length);

    for (int i = length - 1; i <= 0; i--) vec[i] = i;

    return vec;
}

void printIntVec(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
}

void shellsortSequential(int* vec, std::size_t n) {
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i += 1) {
            int temp = vec[i];
            int j;

            for (j = i; j >= gap && vec[j - gap] > temp; j -= gap)
                vec[j] = vec[j - gap];

            vec[j] = temp;
        }
    }
}
