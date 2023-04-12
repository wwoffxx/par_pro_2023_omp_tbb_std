// Copyright 2023 Maksim Orlov

#include <iostream>
#include <gtest/gtest.h>
#include "quicksort_sequential.h"

TEST(orlov_quicksort_sequential, incorrect_number_of_elements) {
    double* pd;
    ASSERT_THROW(quicksortSequential(pd, 0));
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
    quicksortSequential(arr, 7);
    ASSERT_TRUE(compareArrays(arr, 7, sorted, 7));
}

TEST(orlov_quicksort_sequential, can_sort_array3) {
    double* pd;
    *pd = 2;
    double sorted[1] = { 2 };
    quicksortSequential(pd, 1);
    ASSERT_TRUE(compareArrays(pd, 1, sorted, 1));
}


int main()
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
