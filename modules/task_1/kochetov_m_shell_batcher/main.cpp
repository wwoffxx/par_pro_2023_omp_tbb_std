// Copyright 2023 Kochetov Maksim
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shell_batcher.h"

TEST(ShellBatcher_Sequential, Test1_ArrayIsEmpty) {
    int size = 0;
    std::vector<int> vec(size);

    ShellsortSeq(vec.data(), size);

    EXPECT_EQ(vec.size(), 0);
}

TEST(ShellBatcher_Sequential, Test2_ArrayHas1Element) {
    int size = 1;
    std::vector<int> vec({ 0 });

    ShellsortSeq(vec.data(), size);

    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 0);
}

TEST(ShellBatcher_Sequential, Test3_ArrayHas2Elements) {
    int size = 2;
    std::vector<int> vec({ 2, 1 });
    std::vector<int> rightVec({ 1, 2 });

    ShellsortSeq(vec.data(), size);

    EXPECT_EQ(vec, rightVec);
}

TEST(ShellBatcher_Sequential, Test4_RandomArray9Elements) {
    int size = 9;
    std::vector<int> vec = GetRandomVec(size);
    std::vector<int> rightVec(vec);

    ShellsortSeq(vec.data(), size);
    std::sort(rightVec.begin(), rightVec.end());

    EXPECT_EQ(vec, rightVec);
}

TEST(ShellBatcher_Sequential, Test5_RandomArray999Elements) {
    int size = 999;
    std::vector<int> vec = GetRandomVec(size);
    std::vector<int> rightVec(vec);

    ShellsortSeq(vec.data(), size);
    std::sort(rightVec.begin(), rightVec.end());

    EXPECT_EQ(vec, rightVec);
}

TEST(ShellBatcher_Sequential, Test6_SortedArray300Elements) {
    int size = 300;
    std::vector<int> vec = GetSortedVec(size);
    std::vector<int> rightVec(vec);

    ShellsortSeq(vec.data(), size);

    EXPECT_EQ(vec, rightVec);
}

TEST(ShellBatcher_Sequential, Test7_ReversedArray300Elements) {
    int size = 300;
    std::vector<int> vec = GetReversedVec(size);
    std::vector<int> rightVec(vec);

    ShellsortSeq(vec.data(), size);
    std::reverse(rightVec.begin(), rightVec.end());

    EXPECT_EQ(vec, rightVec);
}

/*  TEST(ShellBatcher_Sequential, Test8_RandomArray999999Elements) {
    int size = 999999;
    std::vector<int> vec = GetRandomVec(size);
    std::vector<int> rightVec(vec);

    ShellsortSeq(vec.data(), size);
    std::sort(rightVec.begin(), rightVec.end());

    EXPECT_EQ(vec, rightVec);
} */
