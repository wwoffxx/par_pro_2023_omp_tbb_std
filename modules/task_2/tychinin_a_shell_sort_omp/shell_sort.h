// Copyright 2023 Tychinin Alexey
#ifndef MODULES_TASK_2_TYCHININ_A_SHELL_SORT_OMP_SHELL_SORT_H_
#define MODULES_TASK_2_TYCHININ_A_SHELL_SORT_OMP_SHELL_SORT_H_

#include <vector>

namespace task2 {
    std::vector<double> shell_sort(const std::vector<double>& vec);

    std::vector<double> parallel_shell_sort(const std::vector<double>& vec, std::size_t num_threads);

    std::vector<double> merge_sorted_partitions(const std::vector<double>& part1,
                                                const std::vector<double>& part2);

}  // namespace task2

#endif  // MODULES_TASK_2_TYCHININ_A_SHELL_SORT_OMP_SHELL_SORT_H_
