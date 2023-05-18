// Copyright 2023 Mironova Ekaterina
#include "../../../modules/task_1/mironova_e_radix_batcher/radix_batcher.h"
#include <vector>
#include <cstdint>
#include <limits>
#include <cstring>
#include <utility>

void compexch(double* x, double* y) {
    if (*y < *x) {
        std::swap(*x, *y);
    }
}

std::vector<double> radixSort(std::vector<double> data, int exp) {
    int size = data.size();
    std::vector<double> res(size);
    std::vector<int> counter(256, 0);
    uint64_t n;
    for (int i = 0; i < size; i++) {
        std::memcpy(&n, &data[i], sizeof(n));
        counter[255 & (n >> (8 * exp))]++;
    }
    for (int i = 1; i < 256; i++) {
        counter[i] += counter[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        std::memcpy(&n, &data[i], sizeof(n));
        res[counter[255 & (n >> (8 * exp))] - 1] = data[i];
        counter[255 & (n >> (8 * exp))]--;
    }
    return res;
}

std::vector<double> fullRadixSort(std::vector<double> unsortedData) {
    std::vector<double> negativePart, nonNegativePart;
    for (int i = 0; i < unsortedData.size(); i++) {
        if (unsortedData[i] >= 0){
            nonNegativePart.push_back(unsortedData[i]);
        } else {
            negativePart.push_back(unsortedData[i]);
        }
    }
    for (int exp = 0; exp < sizeof(double); exp++) {
        negativePart = radixSort(negativePart, exp);
        nonNegativePart = radixSort(nonNegativePart, exp);
    }
    std::vector<double> sortedData(unsortedData.size());
    for (int i = negativePart.size(), j = 0; i > 0; i--, j++) {
        sortedData[j] = negativePart[i-1];
    }
    for (int i = 0, j = negativePart.size(); i < nonNegativePart.size(); i++, j++) {
        sortedData[j] = nonNegativePart[i];
    }
    return sortedData;
}

std::vector<double> batcherMerge(const std::vector<double>& firstPart, const std::vector<double>& secondPart) {
    int size = firstPart.size() + secondPart.size();
    std::vector<double> fullData(size);
    for (int i = 0, j = 0; i < size; j++, i += 2) {
        fullData[i] = firstPart[j];
        fullData[i + 1] = secondPart[j];
    }
    for (int i = 0; i < size; i += 2)
        compexch(&fullData[i], &fullData[i + 1]);
    for (int i = 1; i < size - 1; i += 2)
        compexch(&fullData[i], &fullData[i + 1]);
    int hsize = size / 2;
    for (int i = 0; i + hsize < size; i++)
        compexch(&fullData[i], &fullData[i + hsize]);
    return fullData;
}

std::vector<double> radixSortBatcherMerge(const std::vector<double>& data) {
    size_t size = data.size();
    if (size % 2 != 0)
        size++;
    std::vector<double> firstPart(data.begin(), data.begin() + size / 2);
    std::vector<double> secondPart(data.begin() + size / 2, data.end());
    if (data.size() % 2 != 0)
        secondPart.push_back(std::numeric_limits<double>::max());
    firstPart = fullRadixSort(firstPart);
    secondPart = fullRadixSort(secondPart);
    std::vector<double> res(firstPart.size() + secondPart.size());
    res = batcherMerge(firstPart, secondPart);
    if (data.size() % 2 != 0)
        res.pop_back();
    return res;
}
