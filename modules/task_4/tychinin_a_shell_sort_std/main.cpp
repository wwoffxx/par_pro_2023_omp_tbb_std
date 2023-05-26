// Copyright 2023 Tychinin Alexey
#include <gtest/gtest.h>
#include <algorithm>
#include <limits>
#include <random>
#include <vector>
#include "shell_sort_std.h"  // NOLINT

using std::vector;
using std::sort;

namespace {
    vector<double> gen_vector(size_t vec_size) {
        std::random_device rnd_dev;
        std::mt19937 twister{ rnd_dev() };
        std::uniform_real_distribution<> dist{};

        vector<double> res(vec_size);
        for (double& val : res) {
            val = dist(twister);
        }

        return res;
    }
}  // namespace

TEST(shell_sort, sort_empty_vector) {
    vector<double> vec;
    EXPECT_NO_THROW(task4::shell_sort(vec));
}

TEST(shell_sort, sort_single_element_vector) {
    vector<double> vec{1.};
    auto shell_sorted = vec;
    task4::shell_sort(shell_sorted);
    EXPECT_EQ(shell_sorted, vec);
}

TEST(shell_sort, sort_sorted_vector) {
    vector<double> vec{1., 3., 4., 5., 994., 12341.};
    auto shell_sorted = task4::shell_sort(vec);
    EXPECT_EQ(shell_sorted, vec);
}

TEST(shell_sort, sort_sort_descending_vector) {
    vector<double> vec{12341, 994., 5., 4., 2., 1.};
    auto shell_sorted = task4::shell_sort(vec);
    sort(vec.begin(), vec.end());
    EXPECT_EQ(shell_sorted, vec);
}

TEST(shell_sort, sort_random_vec) {
    std::random_device rnd_dev;
    std::mt19937 twister{rnd_dev()};
    std::uniform_int_distribution<> dist{100, 1000};
    auto random_vec = gen_vector(dist(twister));
    auto shell_sorted = task4::shell_sort(random_vec);
    sort(random_vec.begin(), random_vec.end());
    EXPECT_EQ(shell_sorted, random_vec);
}

TEST(shell_sort, merge_sorted_partitions_inc) {
    vector<double> vec1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<double> vec2{ 11, 12, 13, 14, 15, 16 };
    vector<double> vec12 = vec1;
    vec12.insert(vec12.end(), vec2.begin(), vec2.end());
    vector<double> merged = task4::merge_sorted_partitions(vec1, vec2);
    EXPECT_EQ(merged, vec12);
}

TEST(shell_sort, merge_sorted_partitions_dec) {
    vector<double> vec1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<double> vec2{ 4, 5, 152 };
    vector<double> vec12 = { 1, 2, 3, 4, 4, 5, 5, 6, 7, 8, 9, 10, 152 };
    vector<double> merged = task4::merge_sorted_partitions(vec1, vec2);
    EXPECT_EQ(merged, vec12);
}

TEST(shell_sort, parallel_sort_random_vec) {
    std::random_device rnd_dev;
    std::mt19937 twister{ rnd_dev() };
    std::uniform_int_distribution<> dist{ 100, 1000 };
    auto random_vec = gen_vector(dist(twister));
    vector<double> shell_sorted = random_vec;
    shell_sorted = task4::parallel_shell_sort(shell_sorted);
    sort(random_vec.begin(), random_vec.end());
    EXPECT_EQ(shell_sorted, random_vec);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
