// Copyright 2023 Maksim Orlov

#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include "../../../modules/task_3/orlov_m_simple_merge_quicksort/quicksort_parallel.h"

TEST(orlov_quicksort_TBB, incorrect_number_of_elements) {
    double* pd = new double;
    EXPECT_ANY_THROW(quicksortTBB(pd, 0));
    delete pd;
}

TEST(orlov_quicksort_TBB, can_sort_array1) {
    double arr[7] = { 3, 5, 2, 10, -3, 0, 4 };
    double sorted[7] = { -3, 0, 2, 3, 4, 5, 10 };
    quicksortTBB(arr, 7);
    ASSERT_TRUE(compareArrays(arr, 7, sorted, 7));
}

TEST(orlov_quicksort_TBB, can_sort_array2) {
    double arr[6] = { 0.3, 0, -0.4, 1.2, 0.3, -0.2 };
    double sorted[6] = { -0.4, -0.2, 0, 0.3, 0.3, 1.2 };
    quicksortTBB(arr, 6);
    ASSERT_TRUE(compareArrays(arr, 6, sorted, 6));
}

TEST(orlov_quicksort_TBB, can_sort_array3) {
    int n = 5000;
    double* arr1 = new double[n];
    double* arr2 = new double[n];
    double* arr3 = new double[n];
    std::mt19937 gen;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < n; i++) {
        arr1[i] = distribution(gen);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
    tick_count t0 = tbb::tick_count::now();
    quicksortSequential(arr3, n);
    tick_count t1 = tbb::tick_count::now();
    double sequential_time = (t1 - t0).seconds();
    tick_count t2 = tbb::tick_count::now();
    quicksortTBB(arr1, n);
    tick_count t3 = tbb::tick_count::now();
    double TBB_time = (t3 - t2).seconds();
    std::cout << "Sequential time: " << sequential_time << std::endl << \
        "TBB time: " << TBB_time << std::endl << \
        "Ratio: " << sequential_time / TBB_time << std::endl;
    std::sort(arr2, arr2 + n);
    ASSERT_TRUE(compareArrays(arr1, n, arr2, n));
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
}

TEST(orlov_quicksort_TBB, can_sort_array4) {
    double arr[6] = { 0, -23090, 12239, 0.002, -1290, 0.0022 };
    double sorted[6] = { -23090, -1290, 0, 0.002, 0.0022, 12239 };
    quicksortTBB(arr, 6);
    ASSERT_TRUE(compareArrays(arr, 6, sorted, 6));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

