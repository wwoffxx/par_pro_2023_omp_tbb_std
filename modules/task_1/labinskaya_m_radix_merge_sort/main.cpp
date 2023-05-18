// Copyright 2023 Labinskaya Marina
#include <gtest/gtest.h>
#include <algorithm>
#include "../../../modules/task_1/labinskaya_m_radix_merge_sort/radix_merge_sort.h"


TEST(Sequential, RadixMergeSortTest_1) {
    int size = 1;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSort(v);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Sequential, RadixMergeSortTest_2) {
    int size = 2;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSort(v);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Sequential, RadixMergeSortTest_10) {
    int size = 10;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSort(v);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Sequential, RadixMergeSortTest_100) {
    int size = 100;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSort(v);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Sequential, RadixMergeSortTest_1000) {
    int size = 1000;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSort(v);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

TEST(Sequential, RadixMergeSortTest_10000) {
    int size = 10000;
    std::vector<double> v = getRandVec(size, -10, 10);
    std::vector<double> res = radixMergeSort(v);
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        ASSERT_EQ(v[i], res[i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
