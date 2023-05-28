// Copyright 2023 Nosonova Darina

#include <gtest/gtest.h>

#include "./nosonova_d_double_radix_sort_tbb.h"

TEST(TBB, Test_TBB_MergeRadixSort_1) {
    DCArray array(10);
    array.setRandValue(-100, 100);
    TBBRadixSort(&array);
    EXPECT_TRUE(array.isSorted());
}

TEST(TBB, Test_TBB_MergeRadixSort_2) {
    DCArray array(100);
    array.setRandValue(-100, 100);
    TBBRadixSort(&array);
    EXPECT_TRUE(array.isSorted());
}

TEST(TBB, Test_TBB_MergeRadixSort_3) {
    DCArray array(1000);
    array.setRandValue(-100, 100);
    TBBRadixSort(&array);
    EXPECT_TRUE(array.isSorted());
}

TEST(TBB, Test_TBB_MergeRadixSort_4) {
    DCArray array(2000);
    array.setRandValue(-100, 100);
    TBBRadixSort(&array);
    EXPECT_TRUE(array.isSorted());
}

TEST(TBB, Test_TBB_MergeRadixSort_5) {
    DCArray array(3000);
    array.setRandValue(-100, 100);
    TBBRadixSort(&array);
    EXPECT_TRUE(array.isSorted());
}
