// Copyright 2023 Maksim Orlov

#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include "../../../modules/task_1/orlov_m_simple_merge_quicksort/quicksort_sequential.h"

TEST(orlov_quicksort_sequential, incorrect_number_of_elements) {
    double* pd = new double;
    EXPECT_ANY_THROW(quicksortSequential(pd, 0));
}

TEST(orlov_quicksort_sequential, can_sort_array1) {
    double arr[7] = { 3, 5, 2, 10, -3, 0, 4 };
    double sorted[7] = { -3, 0, 2, 3, 4, 5, 10 };
    quicksortSequential(arr, 7);
    ASSERT_TRUE(compareArrays(arr, 7, sorted, 7));
}

TEST(orlov_quicksort_sequential, can_sort_array2) {
    double arr[6] = { 0.3, 0, -0.4, 1.2, 0.3, -0.2};
    double sorted[6] = { -0.4, -0.2, 0, 0.3, 0.3, 1.2 };
    quicksortSequential(arr, 6);
    ASSERT_TRUE(compareArrays(arr, 6, sorted, 6));
}

TEST(orlov_quicksort_sequential, can_sort_array3) {
    int n = 5000;
    double* arr1 = new double[n];
    double* arr2 = new double[n];
    std::mt19937 gen;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < n; i++) {
        arr1[i] = distribution(gen);
        arr2[i] = arr1[i];
    }
    quicksortSequential(arr1, n);
    std::sort(arr2, arr2 + n);
    ASSERT_TRUE(compareArrays(arr1, n, arr2, n));
    delete[] arr1;
    delete[] arr2;
}

TEST(orlov_quicksort_sequential, can_sort_array4) {
    double arr[6] = { 0, -23090, 12239, 0.002, -1290, 0.0022 };
    double sorted[6] = { -23090, -1290, 0, 0.002, 0.0022, 12239 };
    quicksortSequential(arr, 6);
    ASSERT_TRUE(compareArrays(arr, 6, sorted, 6));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
