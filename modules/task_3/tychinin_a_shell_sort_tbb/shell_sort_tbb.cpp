// Copyright 2023 Tychinin Alexey

#include "shell_sort_tbb.h"  // NOLINT
#include <tbb/tbb.h>
#include <algorithm>
#include <iostream>
#include <utility>

namespace task3 {
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

    vector<vector<double>> make_partitions(const vector<double>& vec, size_t partitions_n) {
        vector<vector<double>> res;
        size_t interval = vec.size() / partitions_n;
        size_t residue = vec.size() % partitions_n;
        size_t start = 0, finish = 0;
        for (size_t i = 0; i < std::min(partitions_n, vec.size()); ++i) {
            finish += (residue > 0) ? (interval + !!(residue--)) : interval;
            res.emplace_back(vec.begin() + start, vec.begin() + finish);
            start = finish;
        }
        return res;
    }

    vector<double> parallel_shell_sort(const vector<double>& vec) {
        if (vec.size() == 0 || vec.size() == 1) {
            return vec;
        }
        int num_threads = tbb::info::default_concurrency();
        auto parts = make_partitions(vec, num_threads);
        tbb::parallel_for(tbb::blocked_range<int>(0, num_threads), [&parts](const tbb::blocked_range<int> rng) {
            int start = rng.begin(), finish = rng.end();
            for (int i = start; i != finish; ++i)
                parts[i] = shell_sort(parts[i]);
        }, tbb::simple_partitioner());
        auto res = parts[0];
        for (int i = 1; i < parts.size(); i++) {
            res = merge_sorted_partitions(res, parts[i]);
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

}  // namespace task3
