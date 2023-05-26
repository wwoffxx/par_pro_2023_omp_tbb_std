// Copyright 2023 Mironova Ekaterina
#include <gtest/gtest.h>
#include "../../../modules/task_1/mironova_e_radix_batcher/radix_batcher.h"

TEST(radix_batcher, sort_mixed_array_len_6) {
    std::vector<double> unsorted = {1.1, -125.67, 101.2, 53.9, -27.6, 0.008};
    std::vector<double> sorted = {-125.67, -27.6, 0.008, 1.1, 53.9, 101.2};
    std::vector<double> res = radixSortBatcherMerge(unsorted);
    ASSERT_EQ(sorted.size(), res.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(sorted[i], res[i]);
    }
}

TEST(radix_batcher, sort_mixed_array_len_7) {
    std::vector<double> unsorted = {1.1, -125.67, 101.2, 53.9, -27.6, 0.008, 203.4};
    std::vector<double> sorted = {-125.67, -27.6, 0.008, 1.1, 53.9, 101.2, 203.4};
    std::vector<double> res = radixSortBatcherMerge(unsorted);
    ASSERT_EQ(sorted.size(), res.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(sorted[i], res[i]);
    }
}

TEST(radix_batcher, sort_positive_array_len_5) {
    std::vector<double> unsorted = {1.1, 101.2, 53.9, 0.008, 203.4};
    std::vector<double> sorted = {0.008, 1.1, 53.9, 101.2, 203.4};
    std::vector<double> res = radixSortBatcherMerge(unsorted);
    ASSERT_EQ(sorted.size(), res.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(sorted[i], res[i]);
    }
}

TEST(radix_batcher, sort_positive_array_len_4) {
    std::vector<double> unsorted = {1.1, 101.2, 53.9, 0.008};
    std::vector<double> sorted = {0.008, 1.1, 53.9, 101.2};
    std::vector<double> res = radixSortBatcherMerge(unsorted);
    ASSERT_EQ(sorted.size(), res.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(sorted[i], res[i]);
    }
}

TEST(radix_batcher, sort_negative_array_len_3) {
    std::vector<double> unsorted = {-1.1, -125.67, -27.6};
    std::vector<double> sorted = {-125.67, -27.6, -1.1};
    std::vector<double> res = radixSortBatcherMerge(unsorted);
    ASSERT_EQ(sorted.size(), res.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(sorted[i], res[i]);
    }
}

TEST(radix_batcher, sort_negative_array_len_4) {
    std::vector<double> unsorted = {-1.1, -125.67, -27.6, -1.13};
    std::vector<double> sorted = {-125.67, -27.6, -1.13, -1.1};
    std::vector<double> res = radixSortBatcherMerge(unsorted);
    ASSERT_EQ(sorted.size(), res.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(sorted[i], res[i]);
    }
}
