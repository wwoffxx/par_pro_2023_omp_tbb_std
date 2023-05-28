// Copyright 2023 Bezrukov Aleksandr
#include "./radix_batcher.h"

template <class T>
bool TestRandSortedVec(int len, int deg, T min, T max) {
    std::vector<T> vec(len);
    fillArrRandomly(vec.data(), len, min, max);
    std::vector<T> checkVector(vec);

    RadixBatcherSort<T>(&vec, deg);
    RadixSortSeq<T>(&checkVector, 0, len);

    return areVecsEqual(checkVector, vec);
}

bool TestStrictDescendingVec(int len, int deg) {
    std::vector<uint32_t> vec(len);
    fillArrStrictDescending<uint32_t>(vec.data(), len, len);
    std::vector<uint32_t> checkVector(vec);

    RadixBatcherSort<uint32_t>(&vec, deg);
    RadixSortSeq<uint32_t>(&checkVector, 0, len);

    return areVecsEqual(checkVector, vec);
}

TEST(RadixBatcherOMPChecks, Test1) {
    EXPECT_TRUE(TestStrictDescendingVec(13, 2));
}

TEST(RadixBatcherOMPChecks, Test2) {
    EXPECT_TRUE(TestStrictDescendingVec(14, 2));
}

TEST(RadixBatcherOMPChecks, Test3) {
    uint32_t len = getRandValue<uint32_t>(100, 500);
    EXPECT_TRUE(TestRandSortedVec<uint32_t>(len, 1, 0, ~0));
}

TEST(RadixBatcherOMPChecks, Test4) {
    uint32_t len = getRandValue<uint32_t>(100, 500);
    EXPECT_TRUE(TestRandSortedVec<uint32_t>(len, 2, 0, ~0));
}

TEST(RadixBatcherOMPChecks, Test5) {
    uint32_t len = getRandValue<uint32_t>(100, 500);
    EXPECT_TRUE(TestRandSortedVec<uint32_t>(len, 3, 0, ~0));
}

TEST(RadixBatcherOMPChecks, Test6) {
    uint16_t len = getRandValue<uint16_t>(100, 500);
    EXPECT_TRUE(TestRandSortedVec<uint16_t>(len, 2, 0, ~0));
}

/*
bool TestEfficiency(int len, const int deg) {
    std::vector<uint32_t> vec(len);
    fillArrRandomly<uint32_t>(vec.data(), len, 0, ~0);
    std::vector<uint32_t> checkVector(vec);

    auto t1p = omp_get_wtime();
    RadixBatcherSort<uint32_t>(&vec, deg);
    auto t2p = omp_get_wtime();

    std::cout << "Par time: " << (t2p - t1p) << "\n";

    auto t1s = omp_get_wtime();
    RadixSortSeq<uint32_t>(&checkVector, 0, len);
    auto t2s = omp_get_wtime();

    std::cout << "Seq time: " << (t2s - t1s) << "\n";

    return areVecsEqual(checkVector, vec);
}

// 1 000 000 elements (4 threads)
TEST(RadixBatcherOMPEfficiencyChecks, Test7) {
    EXPECT_TRUE(TestEfficiency(1000000, 2));
}

// 100 000 000 elements (8 threads)
TEST(RadixBatcherOMPEfficiencyChecks, Test8) {
    EXPECT_TRUE(TestEfficiency(100000000, 3));
}

// 100 000 000 elements (16 threads)
TEST(RadixBatcherOMPEfficiencyChecks, Test9) {
    EXPECT_TRUE(TestEfficiency(100000000, 4));
} */

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
