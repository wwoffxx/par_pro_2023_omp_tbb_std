// Copyright 2023 Labinskaya Marina
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "../../../modules/task_2/labinskaya_m_radix_merge_sort_omp/radix_merge_sort_omp.h"

TEST(ParallelOpenMP, RadixMergeSortTest_1) {
    int size = 1;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSortOmp(v, 4);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(ParallelOpenMP, RadixMergeSortTest_2) {
    int size = 2;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSortOmp(v, 4);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(ParallelOpenMP, RadixMergeSortTest_10) {
    int size = 10;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSortOmp(v, 4);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(ParallelOpenMP, RadixMergeSortTest_100) {
    int size = 100;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSortOmp(v, 4);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}


TEST(ParallelOpenMP, RadixMergeSortTest_1000) {
    int size = 1000;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSortOmp(v, 4);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(ParallelOpenMP, RadixMergeSortTest_10000) {
    int size = 10000;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSortOmp(v, 4);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
