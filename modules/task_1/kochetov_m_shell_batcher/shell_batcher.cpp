// Copyright 2023 Kochetov Maksim
#include <omp.h>
#include <vector>
#include <random>
#include <iostream>
#include "../../../modules/task_1/kochetov_m_shell_batcher/shell_batcher.h"

void PrintVec(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
}

std::vector<int> GetRandomVec(int size) {
    std::random_device randDev;
    std::mt19937 engine(randDev());
    std::uniform_int_distribution<> distrib(0, 1000);
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = distrib(engine);
    }
    return vec;
}

std::vector<int> GetSortedVec(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = i;
    }
    return vec;
}

std::vector<int> GetReversedVec(int size) {
    std::vector<int> vec(size);
    for (int i = size - 1; i <= 0; i--) {
        vec[i] = i;
    }
    return vec;
}

void ShellsortSeq(int* array, int size) {
    for (int interval = size / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < size; i += 1) {
            int temp = array[i];
            int j;
            for (j = i; j >= interval && array[j - interval] > temp;
                j -= interval) {
                array[j] = array[j - interval];
            }
            array[j] = temp;
        }
    }
}
