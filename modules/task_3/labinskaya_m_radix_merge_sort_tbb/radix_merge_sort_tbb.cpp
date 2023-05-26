// Copyright 2023 Labinskaya Marina
#include <tbb/tbb.h>
#include <tbb/global_control.h>
#include <vector>
#include <random>
#include <ctime>
#include "../../../modules/task_3/labinskaya_m_radix_merge_sort_tbb/radix_merge_sort_tbb.h"

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
        } else {
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

std::vector<double> radixMergeSortSeq(const std::vector<double>& data) {
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

std::vector<std::vector<double>> split(const std::vector<double>& v, int n) {
    std::vector<std::vector<double>> res;
    std::vector<double> temp;

    if (n < 2 || v.size() < n) {
        res.push_back(v);
        return res;
    }

    int i = 0;
    int numSeq = v.size() / n + 1;
    for (i = 0; i < n - 1; i++) {
        for (int k = i * numSeq; k < (i + 1) * numSeq; k++) {
            temp.push_back(v[k]);
        }
        res.push_back(temp);
        temp.clear();
    }
    for (int j = i * numSeq; j < v.size(); j++) {
        temp.push_back(v[j]);
    }
    res.push_back(temp);
    return res;
}

std::vector<double> radixMergeSortTBB(const std::vector<double>& data, int n) {
    std::vector<std::vector<double>> vOmp = split(data, n);
    std::vector<double> res;
    // auto st1 = std::chrono::high_resolution_clock::now();
    tbb::global_control gc(tbb::global_control::max_allowed_parallelism, vOmp.size());
    tbb::parallel_for(tbb::blocked_range<double>(0, vOmp.size()),
        [&](const tbb::blocked_range<double>& range) {
        for (int i = range.begin(); i < range.end(); ++i) {
            vOmp[i] = radixMergeSortSeq(vOmp[i]);
        }
        });
    // auto fn1 = std::chrono::high_resolution_clock::now();
    // auto dur1 = std::chrono::duration_cast<std::chrono::microseconds>(fn1 - st1);
    // std::cout << "durTBB: " << dur1.count() << '\n';
    for (int i = 0; i < vOmp.size(); i++) {
        res = merge(res, vOmp[i]);
    }
    return res;
}
