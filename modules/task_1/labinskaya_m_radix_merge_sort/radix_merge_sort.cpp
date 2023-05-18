// Copyright 2023 Labinskaya Marina
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "../../../modules/task_1/labinskaya_m_radix_merge_sort/radix_merge_sort.h"

std::vector<double> getRandVec(int size, int a, int b) {
    std::vector<double> v(size);
    std::mt19937 gen;
    gen.seed(static_cast<uint32_t>(time(0)));
    std::uniform_real_distribution<double> u(a, b);
    for (int i = 0; i < size; i++) {
        v[i] = u(gen);
    }
    return v;
}

std::vector<double> merge(const std::vector<double>& v1,
    const std::vector<double>& v2) {
    int size1 = v1.size();
    int size2 = v2.size();
    std::vector<double> res(size1 + size2);
    int idx1 = 0, idx2 = 0;
    for (int i = 0; i < size1 + size2; i++) {
        if (idx1 == size1) {
            res[i] = v2[idx2];
            idx2++;
            continue;
        }
        if (idx2 == size2) {
            res[i] = v1[idx1];
            idx1++;
            continue;
        }
        if (v1[idx1] > v2[idx2]) {
            res[i] = v2[idx2];
            idx2++;
        }
        else {
            if (v1[idx1] <= v2[idx2]) {
                res[i] = v1[idx1];
                idx1++;
            }
        }
    }
    return res;
}

void bitwiseSort(double* in, double* out, int size, int byteNum) {
    unsigned char* arr = reinterpret_cast<unsigned char*>(in);
    int counter[256] = { 0 };
    for (int i = 0; i < size; i++) {
        counter[arr[8 * i + byteNum]]++;
    }
    int s = 0;
    for (int i = 0; i < 256; i++) {
        int temp = counter[i];
        counter[i] = s;
        s += temp;
    }
    for (int i = 0; i < size; i++) {
        out[counter[arr[8 * i + byteNum]]] = in[i];
        counter[arr[8 * i + byteNum]]++;
    }
}

bool bitwiseSortLast(double* in, double* out, int size) {
    int negativeIdx = -1, positiveIdx = -1;
    for (int i = 0; i < size; i++) {
        if ((negativeIdx != -1) && (positiveIdx != -1)) {
            break;
        }
        if (in[i] < 0 && (negativeIdx == -1)) {
            negativeIdx = i;
        }
        if (in[i] > 0 && (positiveIdx == -1)) {
            positiveIdx = i;
        }
    }
    if ((negativeIdx != -1) && (positiveIdx != -1)) {
        int i = size - 1;
        bool f = false;
        for (int k = 0; k < size; k++) {
            out[k] = in[i];
            (f) ? i++ : i--;
            if (i == negativeIdx - 1 && !f) {
                i = 0;
                f = true;
            }
        }
        return true;
    } else {
        if (positiveIdx == -1) {
            int j = size - 1;
            for (int i = 0; j >= 0; i++) {
                out[i] = in[j];
                j--;
            }
            return true;
        }
    }
    return false;
}

std::vector<double> radixMergeSort(const std::vector<double>& data) {
    int size1 = static_cast<int>(data.size() / 2);
    int size2 = static_cast<int>(data.size() - data.size() / 2);
    std::vector<double> arr1(size1);
    std::vector<double> arr2(size2);
    for (int i = 0; i < size1; i++) {
        arr1[i] = data[i];
    }
    for (int i = 0; i < size2; i++) {
        arr2[i] = data[size1 + i];
    }
    std::vector<double> res1(size1);
    std::vector<double> res2(size2);
    for (int j = 0; j < 4; j++) {
        bitwiseSort(arr1.data(), res1.data(), size1, 2 * j);
        bitwiseSort(res1.data(), arr1.data(), size1, 2 * j + 1);
    }
    if (!bitwiseSortLast(arr1.data(), res1.data(), size1)) {
        arr1.swap(res1);
    }
    for (int j = 0; j < 4; j++) {
        bitwiseSort(arr2.data(), res2.data(), size2, 2 * j);
        bitwiseSort(res2.data(), arr2.data(), size2, 2 * j + 1);
    }
    if (!bitwiseSortLast(arr2.data(), res2.data(), size2)) {
        arr2.swap(res2);
    }
    return merge(res1, res2);
}
