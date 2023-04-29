// Copyright 2023 Bushmakin Maksim
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shellbatcher.h"

TEST(ShellBatcherSeq, Test_1_EmptyArray) {
    std::size_t vecLength = 0;
    std::vector<int> emptyVec(vecLength);

    shellsortSequential(emptyVec.data(), vecLength);

    EXPECT_EQ(emptyVec.size(), 0);
}

TEST(ShellBatcherSeq, Test_2_OneElementArray) {
    std::size_t vecLength = 1;
    std::vector<int> oneElementVec({ 10 });

    shellsortSequential(oneElementVec.data(), vecLength);

    EXPECT_EQ(oneElementVec.size(), 1);
    EXPECT_EQ(oneElementVec[0], 10);
}

TEST(ShellBatcherSeq, Test_3_RandomVec_10elements) {
    std::size_t vecLength = 10;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortSequential(vec.data(), vecLength);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
}

TEST(ShellBatcherSeq, Test_4_RandomVec_100elements) {
    std::size_t vecLength = 100;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortSequential(vec.data(), vecLength);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
}

TEST(ShellBatcherSeq, Test_5_RandomVec_500elements) {
    std::size_t vecLength = 500;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortSequential(vec.data(), vecLength);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
}

/* TEST(ShellBatcherSeq, Test_6_RandomVec_1000000elements) {
    std::size_t vecLength = 1000000;
    std::vector<int> vec = getRandomIntVec(vecLength);
    std::vector<int> vecCorrect(vec);

    shellsortSequential(vec.data(), vecLength);
    std::sort(vecCorrect.begin(), vecCorrect.end());

    EXPECT_EQ(vec, vecCorrect);
} */
