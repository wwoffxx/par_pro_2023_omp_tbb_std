// Copyright 2023 Tychinin Alexey

#include "shell_sort.h"  // NOLINT
#include <omp.h>
#include <algorithm>
#include <iostream>
#include <utility>

namespace task2 {
    using std::vector;
    using std::size_t;
    using std::advance;

    vector<double> shell_sort(const vector<double>& vec) {
        vector<double> res(vec);
        for (int interval = res.size() / 2; interval > 0; interval /= 2) {
            for (int i = 0; i < interval; i++) {
                for (int j = interval + i; j < res.size(); j += interval) {
                    for (int k = j; k > i && res[k - interval] > res[k]; k -= interval) {
                        std::swap(res[k], res[k - interval]);
                    }
                }
            }
        }
        return res;
    }

    vector<double> parallel_shell_sort(const vector<double>& vec, size_t num_threads) {
        if (vec.size() == 0 || vec.size() == 1) {
            return vec;
        }
        omp_set_num_threads(num_threads);
        vector<double> res(vec.size());
        size_t quotient = vec.size() / num_threads;
        size_t residue = vec.size() % num_threads;
        vector<double> tmp;
    #pragma omp parallel shared(vec, residue) private(tmp)
        {
            size_t tid = omp_get_thread_num();
            if (tid == 0) {
                tmp.resize(quotient + residue);
                std::copy(vec.begin(), vec.begin() + quotient + residue, tmp.begin());
            } else {
                tmp.resize(quotient);
            }
            for (size_t i = 1; i < num_threads; i++) {
                if (tid == i) {
                    std::copy(vec.begin() + quotient * i + residue, vec.end() - quotient * (num_threads - i - 1),
                        tmp.begin());
                }
            }
            tmp = shell_sort(tmp);
    #pragma omp master
            res = tmp;
    #pragma omp barrier
    #pragma omp critical
            if (tid != 0) {
                res = merge_sorted_partitions(tmp, res);
            }
        }
        return res;
    }

    vector<double> merge_sorted_partitions(const vector<double>& part1,
                                           const vector<double>& part2) {
        int i = part1.size() - 1;
        int j = part2.size() - 1;
        int k = part1.size() + part2.size() - 1;
        std::vector<double> res = part1;
        res.resize(k + 1);

        while (j >= 0) {
            if (i >= 0 && part1[i] > part2[j]) {
                res[k--] = part1[i--];
            } else {
                res[k--] = part2[j--];
            }
        }
        return res;
    }

}  // namespace task2
